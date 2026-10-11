#pragma once
#include "CSprite.h"
#include <SDL2/SDL_opengl.h>


class Camera {
public:
    Camera();
    void setMode(int mode);
    int getMode() const { return currentMode; }   // getter necesario
    void applyView(const CSprite& tanque);

private:
    int currentMode;
    enum CameraMode { Cenital = 0, TerceraPersona, LateralDerecho, Frontal, GruaFija };
};
