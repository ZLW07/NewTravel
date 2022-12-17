//
// Created by wei on 2022/12/17.
//

#ifndef NEWTRAVEL_LOAD_ROBOT_H
#define NEWTRAVEL_LOAD_ROBOT_H
#include <QVector>
#include <QOpenGLWidget>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

struct JointParameters
{
    QVector<float> vecJoint;                                 // joint position
    QOpenGLVertexArrayObject vaoJoint;        //声明VAO顶点数组对象
    QOpenGLBuffer vboJoint;                                //声明VBO数组缓冲对象
    GLsizei iNumberOfTriangle;
};

class LoadModel
{
public:
    void loadAscllStl(const QString& filename, int ratio, JointParameters &oJointPara);
    QVector<float> Position;
    QVector<float> Normal;
};

#endif // NEWTRAVEL_LOAD_ROBOT_H
