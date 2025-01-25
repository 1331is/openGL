#include "player.h"
#include <GL/gl.h>

// Конструктор с инициализацией OpenGL-функций
Player::Player(float startX, float startY, float playerSize, float playerSpeed)
    : x(startX), y(startY), size(playerSize), speed(playerSpeed)
{}

void Player::draw()
{
    initializeOpenGLFunctions(); // Добавлено: инициализация OpenGL-функций
    float ver_sqrt[] = {
        x, y,
        x + size, y,
        x + size, y + size,
        x, y + size
    };
    float color_arr[] = {
        1.0, 0.0, 0.0,         // Красный (нижний левый)
        0.0, 1.0, 0.0,         // Зелёный (нижний правый)
        0.0, 0.0, 1.0,         // Синий (верхний правый)
        1.0, 1.0, 0.0          // Жёлтый (верхний левый)
    };

    glVertexPointer(2, GL_FLOAT, 0, ver_sqrt); // 2D координаты
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, color_arr); // RGB цвета
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
void Player::move(float dx, float dy)
{
    x += dx * speed;
    y += dy * speed;
}

float Player::getX() const { return x; }
float Player::getY() const { return y; }
