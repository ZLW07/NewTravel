//
// Created by wei on 2022/5/21.
//

#ifndef NEWTRAVEL_ROBOT_BODY_LOAD_H
#define NEWTRAVEL_ROBOT_BODY_LOAD_H

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

class RobotBody : public QOpenGLWidget, public QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    RobotBody(QWidget *parent = nullptr);
    ~RobotBody();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

public:
    void loadAscllStl(const QString& filename, int ratio, JointParameters &oJointPara); //文件名和放大系数
    void SetDrawParameters(JointParameters &oJointPara);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void InitialTranslate();
    void SetRobotRotation(int iJointIndex);

public  Q_SLOTS:
    void SetRotationAngleOfJoint_0(int value);
    void SetRotationAngleOfJoint_1(int value);
    void SetRotationAngleOfJoint_2(int value);
    void SetRotationAngleOfJoint_3(int value);
    void SetRotationAngleOfJoint_4(int value);
    void SetRotationAngleOfJoint_5(int value);

private:
    JointParameters m_aJointModel[7];

    QVector<float> Position;
    QVector<float> Normal;                //读文件时的俩个临时变量顶点位置，法向量
    QOpenGLShaderProgram shaderprogram;

    QMatrix4x4 view;
    QMatrix4x4 projection;

    QVector2D mousePos;
    QVector2D mousePosForTranslationView;
    QQuaternion rotation;
    QMatrix4x4 Rot;
    QMatrix4x4 m_matJointTrans[7];
    QMatrix4x4 m_matJointRot[7];
    float m_fRotDegree[6];
    std::map<int, QVector3D> m_mapRotVector;
    QVector3D m_v3dCamera;
    qreal  alpha;
    qreal  theta;
    double m_dEyeToModelDistance;

};
#endif // NEWTRAVEL_ROBOT_BODY_LOAD_H
