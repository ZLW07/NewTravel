#include"GL/glew.h"
#include"GL/glut.h"

#include"GLMainWidget.h"
#include"RoamingScenceManager.h"

#include<QMouseEvent>
#include<QWheelEvent>
#include<QDebug>

GLMainWidget::GLMainWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    m_oLoadModel.loadAscllStl("../../Data/RobotModel/1.STL", 1, m_oJointModel);
    this->setFocusPolicy(Qt::StrongFocus);
    manager=new RoamingScenceManager();
}

GLMainWidget::~GLMainWidget()
{
    delete manager;
}



void GLMainWidget::initializeGL()
{
    manager->init();
}

void GLMainWidget::resizeGL(int w, int h)
{
    glViewport(0,-(w-h)/2,w,w);
}

void GLMainWidget::paintGL()
{
    manager->render();
    for (int i = 0; i < m_oJointModel.vecJoint.size(); )
    {
        glBegin(GL_TRIANGLES);
        glVertex3f( m_oJointModel.vecJoint.at(i) * 500 , m_oJointModel.vecJoint.at(i + 1)* 500  , m_oJointModel.vecJoint.at(i + 2)* 500 );
        glVertex3f( m_oJointModel.vecJoint.at(i + 3) * 500 , m_oJointModel.vecJoint.at(i + 4) * 500 , m_oJointModel.vecJoint.at(i + 5)* 500 );
        glVertex3f( m_oJointModel.vecJoint.at(i + 6) * 500 , m_oJointModel.vecJoint.at(i + 7) * 500 , m_oJointModel.vecJoint.at(i + 8)* 500 );
        glEnd();
        i = i + 9;
    }
}

void GLMainWidget::mousePressEvent(QMouseEvent *e)
{
    manager->getInitPos(e->x(),e->y());
}

void GLMainWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons()&Qt::MiddleButton)
    {
        if(e->modifiers()==Qt::CTRL)
        {
            manager->executeTranslateOperation(e->x(),e->y());
        }
        else
        {
            manager->executeRotateOperation(e->x(),e->y());
        }
    }
    update();
}

void GLMainWidget::wheelEvent(QWheelEvent *e)
{
    if(e->delta()>=0)
    {
        manager->executeScaleOperation(-0.1);
    }else
    {
        manager->executeScaleOperation(0.1);
    }
    update();
}
