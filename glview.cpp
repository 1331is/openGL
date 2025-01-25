#include "glview.h"
#include "./ui_glview.h"
glView::glView(QWidget *parent)
    : QOpenGLWidget(parent)
{
    setWindowTitle("Bomber Man");
    setGeometry(400, 200, 800, 600);
    tmr.start(100);
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
    //glOrtho(-1,1,-1,1,1,2);
    glFrustum(-1,1,-1,1,1,3);
}
void glView::paintGL() // при любом событии
{
    glClearColor(0,1,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0,0,-2);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    drawCube(0.5);
}
void glView::mousePressEvent(QMouseEvent * mo){
    mPos = mo->pos();
}
void glView::mouseMoveEvent(QMouseEvent * mo){
    xRot = 1 / M_PI*(mo->pos().y() - mPos.y());
    yRot = 1 / M_PI*(mo->pos().x() - mPos.x());
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

