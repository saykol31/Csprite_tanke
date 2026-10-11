#ifndef TILEUTILS_H
#define TILEUTILS_H

#include "Tile.h"
#include <glm/glm.hpp>
#include <vector>

// Declaraciones
void drawTile(const Tile &tile, glm::vec3 color);
std::vector<Tile> createWall(int numTiles, glm::vec3 startPos, glm::vec2 size);

#endif // TILEUTILS_H
