#include "VentanaGris3D.h"
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

VentanaGris3D::VentanaGris3D() : window(nullptr), glContext(nullptr), width(800), height(600) {}

VentanaGris3D::~VentanaGris3D() { cerrar(); }

bool VentanaGris3D::iniciar(const char* titulo, int w, int h) {
    width = w;
    height = h;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
        return false;
    }

   // OpenGL 2.1 + compatibilidad
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);


    window = SDL_CreateWindow(titulo, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error crear ventana: " << SDL_GetError() << std::endl;
        return false;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "Error crear contexto OpenGL: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GL_SetSwapInterval(1); // vsync

    // Configuración básica OpenGL
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    return true;
}

void VentanaGris3D::limpiar() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // fondo gris
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void VentanaGris3D::presentar() {
    SDL_GL_SwapWindow(window);
}

void VentanaGris3D::cerrar() {
    if (glContext) {
        SDL_GL_DeleteContext(glContext);
        glContext = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}










