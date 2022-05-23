//
// Created by wei on 2022/5/21.
//

#ifndef NEWTRAVEL_MYOPENGLWIEGT_H
#define NEWTRAVEL_MYOPENGLWIEGT_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QVector>
#include <QStringList>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QTimer>
#include <QTime>
#include <QMatrix4x4>
#include <QMatrix3x3>
#include <QQuaternion>
#include <QVector2D>

#include "Log/log.h"

class Widget : public QOpenGLWidget,public QOpenGLExtraFunctions
{
Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w,int h) override;
    QVector<float> loadAscllStl(QString filename,int ratio);//文件名和放大系数
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);


private:
    QVector<float> vertices;
    QVector<float> Position;
    QVector<float> Normal;//读文件时的俩个临时变量顶点位置，法向量
    QOpenGLShaderProgram shaderprogram;
    QOpenGLVertexArrayObject VAO;//声明VAO顶点数组对象
    QOpenGLBuffer VBO;//声明VBO数组缓冲对象

    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    GLfloat xtrans, ytrans, ztrans; // translation on x,y,z-axis
    QVector2D mousePos;
    QQuaternion rotation;
};
#endif // NEWTRAVEL_MYOPENGLWIEGT_H
