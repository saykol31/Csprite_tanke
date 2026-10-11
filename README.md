# Csprite_tanke — Simulador de tanque procedural

Simulador de tanque 3D dibujado **100% por código** con OpenGL inmediato
(sin modelos externos): cuerpo, torre con escotilla, cañón en dos secciones,
8 ruedas, guardabarros, tronco de madera, tanques laterales y rejillas de
ventilación. Proyecto de mis años de aprendizaje — empecé por la ventana
gris en vez del `main`, y el tanque creció alrededor.

## Características

- Tanque procedural completo: carrocería, torre giratoria, cañón elevable
- 5 modos de cámara (cenital, tercera persona, lateral, frontal, grúa fija)
- Escenario con muros de tiles
- Controles de teclado en tiempo real

## Controles

| Tecla | Acción |
|---|---|
| ↑ ↓ | Avanzar / retroceder |
| ← → | Girar el cuerpo |
| W / S | Elevar / bajar el cañón |
| A / D | Girar la torre |
| X | Cambiar de cámara |

## Requisitos

- CMake ≥ 3.15, compilador C++17
- SDL2, GLEW, OpenGL, GLM

## Compilar y ejecutar

```bash
cmake -S . -B build
cmake --build build
./bin/VentanaGris3D
