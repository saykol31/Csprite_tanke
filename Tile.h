#ifndef TILE_H
#define TILE_H

#include <glm/glm.hpp>

struct Tile {
    glm::vec3 position;
    glm::vec2 size;
    bool active = true;   // ✅ nuevo campo

    // Constructor por defecto
    Tile()
        : position(0.0f), size(1.0f), active(true) {}

    // Constructor con parámetros
    Tile(const glm::vec3& pos, const glm::vec2& sz, bool act = true)
        : position(pos), size(sz), active(act) {}
};

#endif // TILE_H
