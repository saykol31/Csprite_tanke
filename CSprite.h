#ifndef CSPRITE_H
#define CSPRITE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

// Funciones de dibujo
void dibujarCilindro(float radio, float altura, int slices);
void dibujarCubo(float w, float h, float d);

class CSprite {
public:
    // Posición del tanque
    float x, y, z;

    // Escala
    float sx, sy, sz;

    // Rotación del cuerpo
    float rx, ry, rz;

    // Rotación torre y cañón
    float ry_torre;   // gira torre horizontal
    float rx_canon;   // eleva cañón

    // Color
    float r, g, b, a;

    // Velocidades de animación
    float vx, vy, vz;
    float vrx, vry, vrz;

        // Getters de posición
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }

    // Getters de orientación
    float getRotationY() const { return ry; }
    float getTorreRotationY() const { return ry_torre; }
    float getCanonRotationX() const { return rx_canon; }


    // Constructor
    CSprite(float px=0, float py=0, float pz=0);

    // Métodos
    void handleInput(const Uint8* keyState); // captura teclas
    void update(float dt);                   // actualiza posición/rotación
    void draw();                             // dibuja tanque 3D
};

#endif
