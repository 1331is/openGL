#ifndef PLAYER_H
#define PLAYER_H

#include <QOpenGLFunctions>

class Player : public QOpenGLFunctions
{
private:
    float x, y;    // Координаты игрока
    float size;    // Размер квадрата
    float speed;   // Скорость перемещения

public:
    Player(float startX, float startY, float playerSize, float playerSpeed);
    void draw();               // Отрисовка игрока
    void move(float dx, float dy);  // Перемещение игрока
    float getX() const;        // Получить координату X
    float getY() const;        // Получить координату Y
};

#endif // PLAYER_H
