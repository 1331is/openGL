#include "glview.h"
#include "map.h"
#include "./ui_glview.h"
glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("Bomber Man");
    setGeometry(100, 100, 1280, 720);
    tmr.start(100);
    setFocusPolicy(Qt::StrongFocus);
    float cellSize = 50; // Размер одной ячейки
    int rows = height() / cellSize; // Число строк
    int cols = width() / cellSize;  // Число столбцов
    map = new Map(rows, cols);
    initializeMap(map);
    player = new Player(100.0f, 100.0f, 50.0f, 5.0f);

}

glView::~glView()
{
    delete player; // Освобождаем память
}

void glView::initializeGL() //создание окна
{
    initializeOpenGLFunctions(); // Добавлено: инициализация OpenGL-функций
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void glView::resizeGL(int w, int h) //изменение окна
{
    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
}
void glView::paintGL() // при любом событии
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    Q_ASSERT(QOpenGLContext::currentContext() != nullptr);
    if (map) {
        map->draw(50); // Размер одной ячейки 50x50
    }
    if (player != nullptr) {
        player->draw();
    }
}
void glView::keyPressEvent(QKeyEvent *event)
{
    if (!player) return;

    switch (event->key()) {
    case Qt::Key_W:
        player->move(0, -1);
        break;
    case Qt::Key_S:
        player->move(0, 1);
        break;
    case Qt::Key_A:
        player->move(-1, 0);
        break;
    case Qt::Key_D:
        player->move(1, 0);
        break;
    default:
        QOpenGLWidget::keyPressEvent(event);
    }

    update();
}
void glView::mousePressEvent(QMouseEvent * mo){
    mPos = mo->pos();
}
void glView::mouseReleaseEvent(QMouseEvent * mo){
    /*
    xPrevRot += xRot; // Сохраняем углы вращения
    yPrevRot += yRot; // Сохраняем углы вращения
    mPos = mo->pos();
    xRot = 0; // Сбрасываем текущие углы вращения
    yRot = 0;
*/
}
void glView::mouseMoveEvent(QMouseEvent * mo){
    xRot += 1 / M_PI*(mo->pos().y() - mPos.y());
    yRot += 1 / M_PI*(mo->pos().x() - mPos.x());
    mPos = mo->pos();
    update();
}
void glView::drawCube(float a)
{
    float ver_cub[] = {
        -a, -a, a,  a, -a, a,   a, a, a,    -a,a,a, // передняя
        a, -a, -a,  -a, -a,-a,  -a, a, -a,  a, a, -a,   // задняя
        -a, -a, -a, -a, -a, a,  -a, a, a,   -a, a, -a,  // левая
        a, -a,a,    a, -a, -a,  a, a, -a,   a, a, a,    // правая
        -a, -a, a,  a, -a, a,   a, -a, -a,  -a, -a, -a, // нижняя
        -a, a, a,   a, a, a,    a, a, -a,   -a, a, -a   // верхняя
    };
    float color_arr[] = {
        1, 0, 0,    1, 0, 0,    1, 0, 0,    1, 0, 0,
        0, 0, 1,    0, 0, 1,    0, 0, 1,    0, 0, 1,
        1, 1, 0,    1, 1, 0,    1, 1, 0,    1, 1, 0,
        0, 1, 1,    0, 1, 1,    0, 1, 1,    0, 1, 1,
        1, 0, 1,    1, 0, 1,    1, 0, 1,    1, 0, 1,
        1, 0.5, 0.5,    1, 0.5, 0.5,    1, 0.5, 0.5,    1, 0.5, 0.5
    };
    glVertexPointer(3, GL_FLOAT, 0, &ver_cub);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, &color_arr);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

}

