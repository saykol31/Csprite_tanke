#include "TileUtils.h"
#include <GL/gl.h> // o SDL2/OpenGL según tu setup

void drawTile(const Tile &tile, glm::vec3 color) {
    if (!tile.active) return;
    glColor3f(color.r, color.g, color.b);
    glPushMatrix();
    glTranslatef(tile.position.x, tile.position.y, tile.position.z);
    glScalef(tile.size.x, tile.size.y, 1.0f);
    // Dibujar quad simple
    glBegin(GL_QUADS);
        glVertex3f(-0.5f, 0.0f, -0.5f);
        glVertex3f( 0.5f, 0.0f, -0.5f);
        glVertex3f( 0.5f, 0.0f,  0.5f);
        glVertex3f(-0.5f, 0.0f,  0.5f);
    glEnd();
    glPopMatrix();
}

std::vector<Tile> createWall(int numTiles, glm::vec3 startPos, glm::vec2 size) {
    std::vector<Tile> wall;
    for (int i = 0; i < numTiles; i++) {
        Tile t(startPos + glm::vec3(i*size.x, 0.0f, 0.0f), size);
        t.active = true;
        wall.push_back(t);
    }
    return wall;
}
