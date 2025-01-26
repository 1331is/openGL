#ifndef MAP_H
#define MAP_H

#include <vector>
#include <QOpenGLFunctions>

enum class CellType {
    Empty,       // Пустая ячейка
    Wall,        // Неразрушимая стена
    BreakableWall // Разрушимая стена
};

class Map : public QOpenGLFunctions {
public:
    Map(int rows, int cols); // Создание карты с размером rows x cols
    void setCell(int row, int col, CellType type); // Установить тип ячейки
    CellType getCell(int row, int col) const; // Получить тип ячейки
    void draw(float cellSize); // Отрисовка карты
    int getRows() const { return rows; }
    int getCols() const { return cols; }
private:
    int rows, cols; // Размеры карты
    std::vector<std::vector<CellType>> grid; // Сетка карты
};
void initializeMap(Map* map); // Объявление функции для инициализации карты

#endif // MAP_H
