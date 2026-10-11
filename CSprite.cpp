#include "CSprite.h"
#include <cmath>

// --- Funciones de dibujo ---
void dibujarCilindro(float radio, float altura, int slices) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_FILL);
    glPushMatrix();
    glTranslatef(0, 0, -altura/2.0f);
    gluCylinder(quad, radio, radio, altura, slices, 1);
    gluDisk(quad, 0, radio, slices, 1);  // base inferior
    glTranslatef(0, 0, altura);
    gluDisk(quad, 0, radio, slices, 1);  // base superior
    glPopMatrix();
    gluDeleteQuadric(quad);
}

void dibujarCubo(float w, float h, float d) {
    glPushMatrix();
    glScalef(w, h, d);
    glBegin(GL_QUADS);
        // Frente
        glVertex3f(-0.5f,-0.5f,0.5f); glVertex3f(0.5f,-0.5f,0.5f);
        glVertex3f(0.5f,0.5f,0.5f);  glVertex3f(-0.5f,0.5f,0.5f);
        // Atrás
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(0.5f,-0.5f,-0.5f);
        glVertex3f(0.5f,0.5f,-0.5f);  glVertex3f(-0.5f,0.5f,-0.5f);
        // Izquierda
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(-0.5f,-0.5f,0.5f);
        glVertex3f(-0.5f,0.5f,0.5f);  glVertex3f(-0.5f,0.5f,-0.5f);
        // Derecha
        glVertex3f(0.5f,-0.5f,-0.5f);  glVertex3f(0.5f,-0.5f,0.5f);
        glVertex3f(0.5f,0.5f,0.5f);   glVertex3f(0.5f,0.5f,-0.5f);
        // Arriba
        glVertex3f(-0.5f,0.5f,-0.5f);  glVertex3f(-0.5f,0.5f,0.5f);
        glVertex3f(0.5f,0.5f,0.5f);    glVertex3f(0.5f,0.5f,-0.5f);
        // Abajo
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(-0.5f,-0.5f,0.5f);
        glVertex3f(0.5f,-0.5f,0.5f);   glVertex3f(0.5f,-0.5f,-0.5f);
    glEnd();
    glPopMatrix();
}



    // Dibuja un círculo plano centrado en el origen en el plano XY
    void dibujarCirculo(float radio, int slices) {
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0f, 0.0f, 0.0f); // centro
            for(int i=0; i<=slices; ++i) {
               float angle = 2.0f * M_PI * i / slices;
               float x = cos(angle) * radio;
               float y = sin(angle) * radio;
               glVertex3f(x, y, 0.0f);
            }
        glEnd();
    }



// Dibuja una línea amarilla con sombra negra desplazada
void dibujarLineaConSombra(float x1, float y1, float z1,
                           float x2, float y2, float z2,
                           float grosorLinea = 2.0f,
                           float grosorSombra = 5.0f,
                           float offset = 0.01f)
{
    // --- Dibujar sombra (ligeramente detrás y desplazada) ---
    glLineWidth(grosorSombra);
    glColor3f(0.0f, 0.0f, 0.0f); // negro
    glBegin(GL_LINES);
        glVertex3f(x1 + offset, y1 - offset, z1 - offset);
        glVertex3f(x2 + offset, y2 - offset, z2 - offset);
    glEnd();

    // --- Dibujar línea principal (amarilla, encima) ---
    glLineWidth(grosorLinea);
    glColor3f(1.0f, 1.0f, 0.0f); // amarillo
    glBegin(GL_LINES);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z2);
    glEnd();

    // Reset
    glLineWidth(1.0f);
}



// --- Constructor ---
CSprite::CSprite(float px, float py, float pz)
    : x(px), y(py), z(pz),
      sx(1), sy(1), sz(1),
      rx(0), ry(0), rz(0),
      ry_torre(0), rx_canon(0),
      vx(0), vy(0), vz(0),
      vrx(0), vry(0), vrz(0),
      r(0.2f), g(0.5f), b(0.2f), a(1.0f) {}

// --- Captura teclas ---
void CSprite::handleInput(const Uint8* keyState) {
    float speed = 2.0f;      // velocidad de movimiento
    float rotSpeed = 20.0f;  // grados por segundo (se multiplica por dt en update)

    // Reiniciar velocidades
    vx = vz = vrz = vrx = vry = 0.0f;

    // Movimiento cuerpo (flechas)
    if(keyState[SDL_SCANCODE_UP])    { vx = sin(ry*M_PI/180.0f)*speed;  vz = -cos(ry*M_PI/180.0f)*speed; }
    if(keyState[SDL_SCANCODE_DOWN])  { vx = -sin(ry*M_PI/180.0f)*speed; vz = cos(ry*M_PI/180.0f)*speed; }
    if(keyState[SDL_SCANCODE_LEFT])  vrz = -rotSpeed;
    if(keyState[SDL_SCANCODE_RIGHT]) vrz = rotSpeed;

    // Torre y cañón (WASD)


    // Subir/bajar cañón (eje X del cañón)
    if (keyState[SDL_SCANCODE_W]) vrx =  rotSpeed;  // cañón arriba
    if (keyState[SDL_SCANCODE_S]) vrx = -rotSpeed;  // cañón abajo

    // Girar torre (eje Y de la torre)
    if (keyState[SDL_SCANCODE_A]) vry = -rotSpeed;  // torre izquierda
    if (keyState[SDL_SCANCODE_D]) vry =  rotSpeed;  // torre derecha
    // Espacio: disparo -> agregar lógica si quieres
}

// --- Actualiza posición y rotaciones ---
void CSprite::update(float dt) {
    x += vx * dt;
    z += vz * dt;
    ry += vrz * dt;

    // torre/cañón
    rx_canon += vrx * dt;
    ry_torre  += vry * dt;

    // Limites del cañón: -25° (abajo) a +70° (arriba)
    if (rx_canon > 60.0f)  rx_canon = 60.0f;
    if (rx_canon < -12.0f) rx_canon = -12.0f;
}

// --- Dibujar tanque ---
// --- Dibujar tanque con ruedas ---
void CSprite::draw() {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rx, 1,0,0);
    glRotatef(ry, 0,1,0);
    glRotatef(rz, 0,0,1);
    glScalef(sx, sy, sz);

    // mudflap como prisma con triángulo
glColor4f(0.3f, 0.3f, 0.3f, 1.0f); // gris oscuro

    // declarar fuera del bucle de lados, antes de glPushMatrix
float mudflapFrontZ = -0.45f;
float mudflapBackZ  = mudflapFrontZ + 4*0.55f;
float mudflapTipOffsetZ = 0.1f;
float thickness = 0.3f; // grosor

    //  lado derecho
glPushMatrix();
    glTranslatef(0.8f - 0.02f, 0.0f, -0.6f); // mueve al lateral izquierdo


    // Cara interna
    glBegin(GL_QUADS);
        glVertex3f(0.0f, -0.15f, mudflapFrontZ);
        glVertex3f(0.0f,  0.1f, mudflapFrontZ);
        glVertex3f(0.0f,  0.1f, mudflapBackZ);
        glVertex3f(0.0f, -0.15f, mudflapBackZ);
    glEnd();



    // Cara superior
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.1f, mudflapFrontZ);
        glVertex3f(thickness, 0.1f, mudflapFrontZ);
        glVertex3f(thickness, 0.1f, mudflapBackZ);
        glVertex3f(0.0f, 0.1f, mudflapBackZ);
    glEnd();

    // Triángulos frontal y trasero
    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f,  0.1f, mudflapFrontZ);
        glVertex3f(0.0f, -0.15f, mudflapFrontZ);
        glVertex3f(thickness*0.25f, 0.0f, mudflapFrontZ - mudflapTipOffsetZ);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f,  0.1f, mudflapBackZ);
        glVertex3f(0.0f, -0.15f, mudflapBackZ);
        glVertex3f(thickness*0.25f, 0.0f, mudflapBackZ + mudflapTipOffsetZ);
    glEnd();
glPopMatrix();


     //   lado Izquierdo

glPushMatrix();
    // Mueve el mudflap al lateral derecho
    glTranslatef(-(0.8f ), 0.0f, -0.6f); // x negativo para el lado derecho

    // --- Cara interna (pegada al tanque) ---
    glBegin(GL_QUADS);
        glVertex3f(0.0f, -0.15f, mudflapFrontZ);
        glVertex3f(0.0f,  0.1f, mudflapFrontZ);
        glVertex3f(0.0f,  0.1f, mudflapBackZ);
        glVertex3f(0.0f, -0.15f, mudflapBackZ);
    glEnd();



    // --- Cara superior ---
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.1f, mudflapFrontZ);
        glVertex3f(-thickness, 0.1f, mudflapFrontZ);
        glVertex3f(-thickness, 0.1f, mudflapBackZ);
        glVertex3f(0.0f, 0.1f, mudflapBackZ);
    glEnd();



    // --- Triángulo frontal ---
    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f,  0.1f, mudflapFrontZ);
        glVertex3f(0.0f, -0.15f, mudflapFrontZ);
        glVertex3f(-thickness*0.25f, 0.0f, mudflapFrontZ - mudflapTipOffsetZ);
    glEnd();

    // --- Triángulo trasero ---
    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f,  0.1f, mudflapBackZ);
        glVertex3f(0.0f, -0.15f, mudflapBackZ);
        glVertex3f(-thickness*0.25f, 0.0f, mudflapBackZ + mudflapTipOffsetZ);
    glEnd();

glPopMatrix();


    glColor4f(r,g,b,a);


    // --- Cuerpo con prisma frontal ---
glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.8f); // posición del tanque
    glScalef(1.5f, 0.5f, 3.0f);     // escalado general

    glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //amarillo

    glColor4f(r, g, b, a);          // color del cuerpo

    // --- Cubo principal (cuerpo trasero) ---
    glBegin(GL_QUADS);

        // --- Cara frontal ---
        glVertex3f(-0.5f, -0.5f, 0.2f); // abajo izquierda
        glVertex3f( 0.5f, -0.5f, 0.2f); // abajo derecha
        glVertex3f( 0.5f,  0.5f, 0.2f); // arriba derecha
        glVertex3f(-0.5f,  0.5f, 0.2f); // arriba izquierda

        // Parte trasera plana
        glVertex3f(-0.5f, -0.5f, -0.5f); glVertex3f(0.5f, -0.5f, -0.5f);
        glVertex3f(0.5f, 0.5f, -0.5f);  glVertex3f(-0.5f, 0.5f, -0.5f);

        // Laterales
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(-0.5f,-0.5f,0.2f);
        glVertex3f(-0.5f,0.5f,0.2f);  glVertex3f(-0.5f,0.5f,-0.5f);

        glVertex3f(0.5f,-0.5f,-0.5f);  glVertex3f(0.5f,-0.5f,0.2f);
        glVertex3f(0.5f,0.5f,0.2f);   glVertex3f(0.5f,0.5f,-0.5f);

        // Superior plano
        glVertex3f(-0.5f,0.5f,-0.5f);  glVertex3f(-0.5f,0.5f,0.2f);
        glVertex3f(0.5f,0.5f,0.2f);    glVertex3f(0.5f,0.5f,-0.5f);

        // Inferior plano
        glVertex3f(-0.5f,-0.5f,-0.5f); glVertex3f(-0.5f,-0.5f,0.2f);
        glVertex3f(0.5f,-0.5f,0.2f);   glVertex3f(0.5f,-0.5f,-0.5f);
    glEnd();



 glPushMatrix();
    // Posicionar el prisma al frente del cuerpo
    glTranslatef(0.0f, 0.0f, -0.5f);

    // Rotaciones
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  // punta hacia abajo
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);   // alineado con el tanque

    //  Rotar 90° sobre Y a la derecha
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

  glBegin(GL_QUADS);

    // --- Cara trasera (plana, pegada al cuerpo) ---

    glVertex3f(-0.5f,  0.2f, -0.5f);
    glVertex3f( 0.5f,  0.2f, -0.5f);
    glVertex3f( 0.5f, -0.2f, -0.5f);
    glVertex3f(-0.5f, -0.2f, -0.5f);

    // --- Cara superior (más corta) ---

    glVertex3f(-0.5f,  0.05f,  0.5f); // A (izq - frente)
    glVertex3f( 0.5f,  0.05f,  0.5f); // B (der - frente)
    glVertex3f( 0.5f,  0.05f, -0.5f); // C (der - fondo)
    glVertex3f(-0.5f,  0.05f, -0.5f); // D (izq - fondo)

    // --- Cara inferior (plana, fondo) ---

    glVertex3f(-0.5f, -0.05f,  0.5f); // A (izq - frente)
    glVertex3f( 0.5f, -0.05f,  0.5f); // B (der - frente)
    glVertex3f( 0.5f, -0.2f, -0.5f); // C (der - fondo)
    glVertex3f(-0.5f, -0.2f, -0.5f); // D (izq - fondo)

    // --- Lateral izquierdo ---

    glVertex3f(-0.5f,  0.05f,  0.5f); // frente - arriba
    glVertex3f(-0.5f, -0.05f,  0.5f); // frente - abajo
    glVertex3f(-0.5f, -0.2f, -0.5f); // fondo - abajo
    glVertex3f(-0.5f,  0.05f, -0.5f); // fondo - arriba

    // --- Lateral derecho ---
    glVertex3f(0.5f,  0.05f,  0.5f);  // frente - arriba
    glVertex3f(0.5f, -0.05f,  0.5f);  // frente - abajo
    glVertex3f(0.5f, -0.2f, -0.5f);   // fondo - abajo
    glVertex3f(0.5f,  0.05f, -0.5f);  // fondo - arriba

    // --- Cara frontal inclinada ---

    glVertex3f(-0.5f,  0.05f,  0.5f);  // A (izq - arriba)
    glVertex3f( 0.5f,  0.05f,  0.5f);  // B (der - arriba)
    glVertex3f( 0.5f, -0.05f,  0.5f);  // C (der - abajo, coincide con inferior)
    glVertex3f(-0.5f, -0.05f,  0.5f);  // D (izq - abajo, coincide con inferior)

  glEnd();

 glPopMatrix();

glPopMatrix();



// --- Tronco de madera trasero ---
glPushMatrix();
    // Mover al final del cuerpo, ligeramente elevado
    glTranslatef(-1.0f, 0.20f, 1.4f); // ajustar Z según la posición trasera
    glRotatef(90.0f, 0,1,0);           // girar para eje horizontal (X)

    glColor4f(0.70f, 0.65f, 0.55f, 1.0f); // madera clara envejecida


    float troncoRadius = 0.1f;    // grosor del tronco
    float troncoLength = 2.0f;    // longitud del tronco

    GLUquadric* quadTronco = gluNewQuadric();
    gluQuadricDrawStyle(quadTronco, GLU_FILL);

    // Cilindro principal
    gluCylinder(quadTronco, troncoRadius, troncoRadius, troncoLength, 16, 1);

    // Tapas circulares
    glPushMatrix();
        dibujarCirculo(troncoRadius, 16); // tapa inicio
    glPopMatrix();

    glTranslatef(0.0f, 0.0f, troncoLength);
    glPushMatrix();
        dibujarCirculo(troncoRadius, 16); // tapa final
    glPopMatrix();

    gluDeleteQuadric(quadTronco);
glPopMatrix();



// --- Tanques de agua laterales (paralelos a los mudflaps) ---
float tanqueRadius = 0.18f;       // grosor del tanque
float tanqueLength = 1.5*0.55f;     // mitad de la longitud total de los mudflaps
float tanqueOffsetY = 0.20f;      // altura alineada con la madera
float tanqueOffsetX = 0.8f - 0.02f; // lateral paralelo a mudflaps
float tanqueOffsetZ = 0.45f;     // inicio al nivel del primer mudflap

GLUquadric* quadTanque = gluNewQuadric();
gluQuadricDrawStyle(quadTanque, GLU_FILL);

glColor4f(0.7f, 0.7f, 0.75f, 1.0f); // gris claro envejecido

for(int side = -1; side <= 1; side += 2) { // -1: izquierda, 1: derecha
    glPushMatrix();
        glTranslatef(side * tanqueOffsetX, tanqueOffsetY, tanqueOffsetZ); // lateral y altura
        glRotatef(90.0f, 0, 0, 1); // cilindro paralelo a mudflap (eje Z)

        // Cilindro del tanque
        gluCylinder(quadTanque, tanqueRadius, tanqueRadius, tanqueLength, 16, 1);

        // Tapas circulares
        glPushMatrix();
            dibujarCirculo(tanqueRadius, 16); // tapa frontal
        glPopMatrix();

        glTranslatef(0.0f, 0.0f, tanqueLength);
        glPushMatrix();
            dibujarCirculo(tanqueRadius, 16); // tapa trasera
        glPopMatrix();

    glPopMatrix();
}

gluDeleteQuadric(quadTanque);



// --- Rejillas de ventilación (radiadores) al lado de cada tanque ---
float rejillaWidth  = 0.30f;  // ancho de la rejilla
float rejillaHeight = 0.5f;  // alto de la rejilla
float rejillaOffset = 0.45f;  // separación desde el tanque hacia afuera
int numLíneas = 6;           // cuántas líneas horizontales

for (int side = -1; side <= 1; side += 2) { // -1 izquierda, 1 derecha

   // glColor4f(1.0f, 1.0f, 0.0f, 1.0f); //amarillo
    glPushMatrix();
        // posicionar la rejilla justo al lado de cada tanque
        glTranslatef(side * (tanqueOffsetX - rejillaOffset*1.2f),
             tanqueOffsetY*1.5f,
             tanqueOffsetZ + tanqueLength*0.5f);

        // rotar
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        //glRotatef(0.0f, 0.0f, 1.0f, 0.0f);


        // dibujar líneas horizontales
        for (int i = 0; i < numLíneas; i++) {
            float yLine = -rejillaHeight/2.0f + i * (rejillaHeight / (numLíneas-1));
            dibujarLineaConSombra(-rejillaWidth/2.0f, yLine, 0.0f,
                                   rejillaWidth/2.0f,  yLine, 0.0f,
                                   2.0f, 5.0f);
        }
    glPopMatrix();
}




   // --- Torre (esfera + cilindro base) ---
  glPushMatrix();
        glTranslatef(0.0f,0.25f,0.0f); // elevar torre
        glRotatef(ry_torre,0,1,0);     // rotación torre



        // ---- Base cilíndrica + dome ----
 glPushMatrix();
        // GLU dibuja el cilindro a lo largo de +Z, lo rotamos para que sea vertical (Y)
        glRotatef(-90, 1, 0, 0);

        // Color  (RGB aproximado)
        glColor4f(0.8f, 0.6f, 0.4f, 1.0f); // marrón claro


        const float baseR = 0.5f;
        const float baseH = 0.15f;



        // base cilíndrica
        gluCylinder(gluNewQuadric(), baseR, baseR, baseH, 32, 1);// Cilindro  altura 0.4f
         // tapa superior
        glTranslatef(0, 0, baseH); // ajustar posición sobre el cilindro
        gluDisk(gluNewQuadric(), 0, baseR, 32, 1);


        // dome (semiesfera “aplastada”)
        glTranslatef(0, 0, 0.05f);     // sube o baja el centro de la semiesfera 0.2f alto 0.25 f bajo
        glScalef(1.0f, 1.0f, 0.5f);    //  Z=0.5 => mitad de altura-> semiesfera
        gluSphere(gluNewQuadric(), baseR, 32, 16); //  Semiesfera, el radio 0.5f determina el tamaño del “dome”

        // --- Escotilla levantada ---
    glPushMatrix();
        glColor4f(0.3f, 0.3f, 0.3f, 1.0f); // gris oscuro (igual que mudflaps)

        // Posicionar semicirculo sobre la esquina derecha del dome
        glTranslatef(0.25f, 0.0f, 0.45f); // ajustar X,Y,Z según esquina frontal derecha
        glRotatef(-25.0f, 1, 0, 0);        // inclinar hacia adelante
        glRotatef(0.0f, 0, 1, 0);          // opcional, ajustar orientación lateral

        // Dibujar semicírculo plano
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0f, 0.0f, 0.0f); // centro semicirculo
            const int slices = 16;
            for(int i = 0; i <= slices; ++i){
                float angle = M_PI * i / slices; // solo semicirculo
                float x = 0.2f * cos(angle);     // radio 0.2f
                float y = 0.0f;
                float z = 0.2f * sin(angle);
                glVertex3f(x, y, z);
            }
        glEnd();
    glPopMatrix();

       // --- Salida de la escotilla (rectángulo debajo del semicírculo) ---
  glPushMatrix();
    glColor4f(0.3f, 0.3f, 0.3f, 1.0f); // mismo gris oscuro

    // Posicionar justo debajo del semicírculo
    glTranslatef(0.25f, 0.30f, 0.45f); // ajusta Z para que quede bajo la escotilla
    glRotatef(0.0f, 0, 0, 1);         // no giramos, queda perpendicular al eje Z

    float rectWidth  = 0.4f;  // ancho del rectángulo
    float rectHeight = 0.4f;  // altura que sobresale hacia abajo
    float rectDepth  = 0.4f; // grosor del rectángulo (proyección hacia dentro)

    // Dibujar el rectángulo como cubo aplanado
    glBegin(GL_QUADS);
        // Frente
        glVertex3f(-rectWidth/2, 0.0f, 0.0f);
        glVertex3f( rectWidth/2, 0.0f, 0.0f);
        glVertex3f( rectWidth/2, -rectHeight, 0.0f);
        glVertex3f(-rectWidth/2, -rectHeight, 0.0f);

        // Atrás (profundidad)
        glVertex3f(-rectWidth/2, 0.0f, -rectDepth);
        glVertex3f( rectWidth/2, 0.0f, -rectDepth);
        glVertex3f( rectWidth/2, -rectHeight, -rectDepth);
        glVertex3f(-rectWidth/2, -rectHeight, -rectDepth);

        // Lados
        glVertex3f(-rectWidth/2, 0.0f, 0.0f);
        glVertex3f(-rectWidth/2, -rectHeight, 0.0f);
        glVertex3f(-rectWidth/2, -rectHeight, -rectDepth);
        glVertex3f(-rectWidth/2, 0.0f, -rectDepth);

        glVertex3f(rectWidth/2, 0.0f, 0.0f);
        glVertex3f(rectWidth/2, -rectHeight, 0.0f);
        glVertex3f(rectWidth/2, -rectHeight, -rectDepth);
        glVertex3f(rectWidth/2, 0.0f, -rectDepth);

        // Superior
        glVertex3f(-rectWidth/2, 0.0f, 0.0f);
        glVertex3f(rectWidth/2, 0.0f, 0.0f);
        glVertex3f(rectWidth/2, 0.0f, -rectDepth);
        glVertex3f(-rectWidth/2, 0.0f, -rectDepth);

        // Inferior
        glVertex3f(-rectWidth/2, -rectHeight, 0.0f);
        glVertex3f(rectWidth/2, -rectHeight, 0.0f);
        glVertex3f(rectWidth/2, -rectHeight, -rectDepth);
        glVertex3f(-rectWidth/2, -rectHeight, -rectDepth);
    glEnd();
  glPopMatrix();

 glPopMatrix();

    // ---- Cañón (dentro del grupo de la torre) ----
    glPushMatrix();
        glTranslatef(0.0f, 0.25f, 0.0f);   //  Posición inicial del cañón
        glRotatef(rx_canon,1,0,0);        //  Elevación del cañón
        //glRotatef(ry_torre,0,1,0);        //  Rotación horizontal (torre)
        glRotatef(-180.0f,1,0,0);             //  Gira ejes para que el cilindro apunte hacia Z+ -90 -Z 90

        // Color marrón (RGB aproximado)
        glColor4f(0.55f, 0.27f, 0.07f, 1.0f);

        // Sección proximal (gruesa y corta)
        GLUquadric* quadCanon = gluNewQuadric();
        gluQuadricDrawStyle(quadCanon,GLU_FILL);



        // proximal
        gluCylinder(quadCanon,0.15f,0.15f,0.8f,16,1);
        glTranslatef(0,0,0.8f); // fin de proximal

        // --- tapa del cañón ---
        glPushMatrix();
           glColor4f(0.0f, 0.0f, 0.0f, 1.0f);       // negro
           glTranslatef(0.0f, 0.0f, 0.0f);         // ya estamos al final del cilindro distal
           dibujarCirculo(0.15f, 16);              // radio igual al del distal
        glPopMatrix();

        // Color marrón (RGB aproximado)
        glColor4f(0.55f, 0.27f, 0.07f, 1.0f);


        // distal
        gluCylinder(quadCanon,0.08f,0.08f,1.6f,16,1);
        glTranslatef(0, 0, 1.6f);  // fin de distal

        // --- Boca del cañón ---
        glPushMatrix();
           glColor4f(0.0f, 0.0f, 0.0f, 1.0f);       // negro
           glTranslatef(0.0f, 0.0f, 0.0f);         // ya estamos al final del cilindro distal
           dibujarCirculo(0.08f, 16);              // radio igual al del distal
        glPopMatrix();

        gluDeleteQuadric(quadCanon);
    glPopMatrix();

  glPopMatrix();

    // --- Ruedas ---


    glColor4f(0.1f,0.1f,0.1f,1.0f); // color negro ruedas
    glTranslatef(0.0f, 0.0f, -0.3f);   // ⬅️ mueve el cuerpo hacia atrás (Z-)
    float wheelRadius = 0.2f;       //  tamano de ruedas
    float wheelWidth  = 0.3f;       //  grosor de ruedas
    float wheelOffsetY = -0.25f;     // debajo del cuerpo
    float wheelOffsetX = 0.9f;       // hacia los lados
    float wheelSpacingZ = 0.55f;     // separación entre ruedas, mayor numero aumenta separacion, menor disminuye


    glPushMatrix();   // <- push para todo el bloque de ruedas
        glTranslatef(0.0f, 0.0f, 0.0f);   //  pocision de las ruedas
        for(int side=-1; side<=1; side+=2){     // -1: izquierda, 1: derecha
            for(int i=0;i<4;i++){
                float zPos = -0.45f + i*wheelSpacingZ;
                glPushMatrix();
                     glTranslatef(side*wheelOffsetX, wheelOffsetY, zPos);

                     // Orientar cilindro
                     glColor4f(0.1f,0.1f,0.1f,1.0f); // negro
                     glRotatef(90,0,1,0); // cilindro horizontal
                     dibujarCilindro(wheelRadius, wheelWidth,16);

                     // --- Disco blanco cara frontal  ---
                     glPushMatrix();
                        glTranslatef(0.0f, 0.0f, wheelWidth*0.6f); // frente de la rueda
                        glColor4f(1.0f,1.0f,1.0f,1.0f);       // blanco
                        dibujarCirculo(wheelRadius * 0.3f, 16);
                     glPopMatrix();

                     // Disco blanco cara trasera
                     glPushMatrix();
                     glTranslatef(0.0f, 0.0f, -wheelWidth*0.6f);   // fondo de la rueda
                     glColor4f(1.0f,1.0f,1.0f,1.0f);  // blanco
                     dibujarCirculo(wheelRadius * 0.3f, 16);
                     glPopMatrix();


                glPopMatrix();
            }
        }
    glPopMatrix();   // <- pop del bloque ruedas

glPopMatrix(); // <- pop final del draw

}

