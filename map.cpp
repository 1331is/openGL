#include "map.h"
#include <cstdlib>
#include <ctime>
Map::Map(int rows, int cols) : rows(rows), cols(cols), grid(rows, std::vector<CellType>(cols, CellType::Empty)) {}

void Map::setCell(int row, int col, CellType type) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        grid[row][col] = type;
    }
}

CellType Map::getCell(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return grid[row][col];
    }
    return CellType::Empty; // Если выход за границы
}

void Map::draw(float cellSize) {
    initializeOpenGLFunctions();
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            CellType cell = grid[row][col];
            if (cell == CellType::Empty) continue;

            glPushMatrix();
            glTranslatef(col * cellSize, row * cellSize, 0);

            if (cell == CellType::Wall) {
                glColor3f(0.2f, 0.2f, 0.2f); // Цвет неразрушимой стены
            } else if (cell == CellType::BreakableWall) {
                glColor3f(0.7f, 0.5f, 0.3f); // Цвет разрушимой стены
            }

            glBegin(GL_QUADS);
            glVertex2f(0, 0);
            glVertex2f(cellSize, 0);
            glVertex2f(cellSize, cellSize);
            glVertex2f(0, cellSize);
            glEnd();

            glPopMatrix();
        }
    }
}

void initializeMap(Map* map) {
    int rows = map->getRows();
    int cols = map->getCols();

    // Устанавливаем неразрушимые стены по краям карты
    for (int col = 0; col < cols; ++col) {
        map->setCell(0, col, CellType::Wall);         // Верхняя граница
        map->setCell(rows - 1, col, CellType::Wall); // Нижняя граница
    }
    for (int row = 0; row < rows; ++row) {
        map->setCell(row, 0, CellType::Wall);         // Левая граница
        map->setCell(row, cols - 1, CellType::Wall); // Правая граница
    }

    // Добавляем случайные разрушимые стены
    std::srand(std::time(nullptr)); // Инициализируем генератор случайных чисел
    int numBreakableWalls = 20; // Количество разрушимых стен
    for (int i = 0; i < numBreakableWalls; ++i) {
        int randomRow = std::rand() % (rows - 2) + 1; // Ряды внутри карты
        int randomCol = std::rand() % (cols - 2) + 1; // Столбцы внутри карты

        // Устанавливаем разрушимую стену, если ячейка пустая
        if (map->getCell(randomRow, randomCol) == CellType::Empty) {
            map->setCell(randomRow, randomCol, CellType::BreakableWall);
        }
    }
}
