#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include <vector>
#include <glm/glm.hpp>

class Tilemap {
private:
    std::vector<Tile> tiles;

public:
    Tilemap();

    void addWall(const std::vector<Tile>& wall);
    void draw() const;
    std::vector<Tile>& getTiles();
};

#endif
