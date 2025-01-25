#include "glview.h"
#include "./ui_glview.h"
glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("Bomber Man");
    setGeometry(400, 200, 800, 600);
    tmr.start(100);
    player = new Player(100.0f, 100.0f, 50.0f, 5.0f);
}

glView::~glView()
{
    delete player; // Освобождаем память
}

void glView::initializeGL() //создание окна
{
    glEnable(GL_DEPTH_TEST);
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
    glClearColor(0,1,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (player) {
        player->draw(); // Отрисовка игрока
    }
}
void glView::keyPressEvent(QKeyEvent *event)
{
    if (!player) return;

    switch (event->key()) {
    case Qt::Key_W:
        player->move(0, -1); // Вверх
        break;
    case Qt::Key_S:
        player->move(0, 1); // Вниз
        break;
    case Qt::Key_A:
        player->move(-1, 0); // Влево
        break;
    case Qt::Key_D:
        player->move(1, 0); // Вправо
        break;
    default:
        QOpenGLWidget::keyPressEvent(event);
    }

    update(); // Перерисовать окно
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

