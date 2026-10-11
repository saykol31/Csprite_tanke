#include "Tilemap.h"
#include "TileUtils.h"  // Para drawTile y createWall
#include <vector>

// Tilemap puede ser responsable de gestionar colecciones de tiles
// Aquí solo dejamos funciones de Tilemap si quieres expandir en el futuro

Tilemap::Tilemap() {}

void Tilemap::addWall(const std::vector<Tile>& wall) {
    for (const auto& t : wall) {
        tiles.push_back(t);
    }
}

void Tilemap::draw() const {
    for (const auto& t : tiles) {
        drawTile(t, glm::vec3(0.7f, 0.2f, 0.2f)); // Color por defecto
    }
}

std::vector<Tile>& Tilemap::getTiles() {
    return tiles;
}
