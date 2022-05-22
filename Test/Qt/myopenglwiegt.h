//
// Created by wei on 2022/5/21.
//

#ifndef NEWTRAVEL_MYOPENGLWIEGT_H
#define NEWTRAVEL_MYOPENGLWIEGT_H

#include "Model/model_data.h"

#include<QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include  <QOpenGLShaderProgram>

//多继承，自定义的MyopenGLWiegt类同时继承自QOpenGLWidget和QOpenGLFunctions
//这样就可以在类中直接使用QOpenGLFunctions中的OpenGL函数，而不需要创建QOpenGLFuctions对象
//这里声明了一个QOpenGLShaderProgram对象指针，作为着色器程序
class MyopenGLWiegt:public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit MyopenGLWiegt(QWidget *parent = 0);
protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width,int height) override;

    void keyPressEvent(QKeyEvent *event);           //处理键盘按下事件

private:
    GLuint m_glVBO;
    GLuint m_VAO;
    GLuint  m_EBO;
    QOpenGLFunctions_3_3_Core *m_Core;
    QOpenGLShaderProgram  m_oShaderProgram;

    bool fullscreen;
    GLfloat m_rtri;                                 //控制三角形的角度
    GLfloat m_rquad;                                //控制四边形的角度
    ModelDataBase m_oModelData;
};

#endif // NEWTRAVEL_MYOPENGLWIEGT_H
