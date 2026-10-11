#ifndef VENTANA_GRIS_3D_H
#define VENTANA_GRIS_3D_H

#include <SDL2/SDL.h>

class VentanaGris3D {
private:
    SDL_Window* window;
    SDL_GLContext glContext;
    int width, height;

public:
    VentanaGris3D();
    ~VentanaGris3D();

    bool iniciar(const char* titulo, int w, int h);
    void limpiar();    // Limpia el buffer de color y profundidad
    void presentar();  // Swap buffers
    SDL_Window* getWindow() { return window; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    void cerrar();
};

#endif
