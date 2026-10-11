#include "Camera.h"
#include <GL/gl.h>
#include <GL/glu.h>

Camera::Camera() : currentMode(0) {}

void Camera::setMode(int mode) {
    currentMode = mode;
}

void Camera::applyView(const CSprite& tanque) {
    float tx = tanque.getX();
    float ty = tanque.getY();
    float tz = tanque.getZ();

    glLoadIdentity();

    switch(currentMode) {
        case Cenital:
            gluLookAt(tx, ty + 15.0f, tz, tx, ty, tz, 0.0f, 0.0f, -1.0f);
            break;
        case TerceraPersona: {
            float distancia = 10.0f;
            float altura = 5.0f;
            gluLookAt(tx, ty + altura, tz + distancia, tx, ty, tz, 0.0f, 1.0f, 0.0f);
            break;
        }
        case LateralDerecho:
            gluLookAt(tx + 10.0f, ty + 5.0f, tz, tx, ty, tz, 0.0f, 1.0f, 0.0f);
            break;
        case Frontal:
            gluLookAt(tx, ty + 5.0f, tz - 10.0f, tx, ty, tz, 0.0f, 1.0f, 0.0f);
            break;
        case GruaFija:
            gluLookAt(20.0f, 15.0f, 20.0f, tx, ty, tz, 0.0f, 1.0f, 0.0f);
            break;
    }
}
