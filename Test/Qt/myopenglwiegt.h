//
// Created by wei on 2022/5/21.
//

#ifndef NEWTRAVEL_MYOPENGLWIEGT_H
#define NEWTRAVEL_MYOPENGLWIEGT_H

#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QStringList>
#include <QTime>
#include <QTimer>
#include <QVector2D>
#include <QVector>

#include "Log/log.h"

struct JointParameters
{
    QVector<float> vecJoint;                                 // joint position
    QOpenGLVertexArrayObject vaoJoint;       //声明VAO顶点数组对象
    QOpenGLBuffer vboJoint;                                //声明VBO数组缓冲对象
    GLsizei iNumberOfTriangle;
};

class Widget : public QOpenGLWidget, public QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

public:
    void loadAscllStl(QString filename, int ratio, JointParameters &oJointPara); //文件名和放大系数
    void SetDrawParameters(JointParameters &oJointPara);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    JointParameters m_aJointModel[6];

    QVector<float> Position;
    QVector<float> Normal; //读文件时的俩个临时变量顶点位置，法向量
    QOpenGLShaderProgram shaderprogram;

    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    GLfloat xtrans, ytrans, ztrans; // translation on x,y,z-axis
    QVector2D mousePos;
    QQuaternion rotation;
};
#endif // NEWTRAVEL_MYOPENGLWIEGT_H
