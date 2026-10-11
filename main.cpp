#include "VentanaGris3D.h"
#include "CSprite.h"
#include "Tile.h"
#include "TileUtils.h"
#include "Camera.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

int main() {
    // Crear ventana
    VentanaGris3D ventana;
    if (!ventana.iniciar("Demo Tanque con Tiles y Cámaras", 800, 600)) {
        std::cerr << "No se pudo iniciar la ventana." << std::endl;
        return -1;
    }

    // Crear tanque
    CSprite tanque;

    // Crear pared de tiles
    std::vector<Tile> wall = createWall(10, glm::vec3(-5.0f,0.0f,-20.0f), glm::vec2(2.0f,2.0f));

    Camera camera;

    bool salir = false;
    SDL_Event e;
    float dt = 0.03f;

    // Configurar proyección en perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        45.0f,
        float(ventana.getWidth()) / ventana.getHeight(),
        0.1f,
        100.0f
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!salir) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                salir = true;

           if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_x) {
               int nextMode = (camera.getMode() + 1) % 5;  // <-- usar getMode() de Camera
               camera.setMode(nextMode);
           }

        }

        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        tanque.handleInput(keyState);
        tanque.update(dt);

        ventana.limpiar();

        // Aplicar cámara
        camera.applyView(tanque);

        // Dibujar pared de tiles
        for (auto &t : wall)
            drawTile(t, glm::vec3(0.7f, 0.2f, 0.2f));

        // Dibujar tanque
        tanque.draw();

        ventana.presentar();
    }

    ventana.cerrar();
    return 0;
}


