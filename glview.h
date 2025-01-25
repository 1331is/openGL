#ifndef GLVIEW_H
#define GLVIEW_H
#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include "player.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class glView;
}
QT_END_NAMESPACE

class glView : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
private:
    float xRot, yRot, zRot, xPrevRot, yPrevRot;
    QPoint mPos;
    QTimer tmr;
    Player *player;
    void drawCube(float a);
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent *) override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

public:
    glView(QWidget *parent = nullptr);
    ~glView();

private:
    Ui::glView *ui;
public slots:
};
#endif // GLVIEW_H
