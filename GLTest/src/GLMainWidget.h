#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include "load_robot.h"
class RoamingScenceManager;
class GLMainWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLMainWidget(QWidget *parent = 0);
    ~GLMainWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent*e);
    void mouseMoveEvent(QMouseEvent*e);
    void wheelEvent(QWheelEvent *e);

private:
    RoamingScenceManager*manager;
    LoadModel m_oLoadModel;
    JointParameters m_oJointModel;
};

#endif // GLWIDGET_H
