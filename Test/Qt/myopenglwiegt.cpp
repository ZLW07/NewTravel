//
// Created by wei on 2022/5/21.
//

#include "myopenglwiegt.h"
#include <QFile>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QStringList>
#include <QWheelEvent>
#include <QtMath>

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent),  xtrans(0), ytrans(0), ztrans(0.0)
{
    QSurfaceFormat format;
    format.setAlphaBufferSize(24); //设置alpha缓冲大小
    format.setVersion(3, 3);       //设置版本号
    format.setSamples(10);         //设置重采样次数，用于反走样

    this->setFormat(format);
//    loadAscllStl("../../Data/RobotModel/TX2-60L HORIZONTAL BASE.STL", 1, m_aJointModel[0]);
//    loadAscllStl("../../Data/RobotModel/TX2-60L SHOULDER.STL", 1,m_aJointModel[1]);
//    loadAscllStl("../../Data/RobotModel/TX2-60L ARM.STL", 1,m_aJointModel[2]);
//    loadAscllStl("../../Data/RobotModel/TX2-60L ELBOW.STL", 1,m_aJointModel[3]);
//    loadAscllStl("../../Data/RobotModel/TX2-60L FOREARM.STL", 1,m_aJointModel[4]);
//    loadAscllStl("../../Data/RobotModel/TX2-60L WRIST.STL", 1,m_aJointModel[5]);
//
    loadAscllStl("../../Data/RobotModel/1.STL", 1, m_aJointModel[0]);
    loadAscllStl("../../Data/RobotModel/2.STL", 1, m_aJointModel[1]);
    loadAscllStl("../../Data/RobotModel/3.STL", 1, m_aJointModel[2]);
    loadAscllStl("../../Data/RobotModel/4.STL", 1, m_aJointModel[3]);
    loadAscllStl("../../Data/RobotModel/5.STL", 1, m_aJointModel[4]);
    loadAscllStl("../../Data/RobotModel/6.STL", 1, m_aJointModel[5]);
    loadAscllStl("../../Data/RobotModel/7.STL", 1, m_aJointModel[6]);

    QVector3D qRotVector(0,1,0);
    m_mapRotVector[0] = qRotVector;
    qRotVector={0,0,1};
    m_mapRotVector[1] = qRotVector;
    qRotVector={0,0,1};
    m_mapRotVector[2] = qRotVector;
    qRotVector={0,0,1};
    m_mapRotVector[3] = qRotVector;
    qRotVector={0,0,1};
    m_mapRotVector[4] = qRotVector;
    qRotVector = {0, 0, 1};
    m_mapRotVector[5] = qRotVector;

    for (int ii = 0; ii < 6; ii++)
    {
        m_fRotDegree[ii] = 0.0;
    }


    std::cout << sizeof(m_aJointModel)/ sizeof(JointParameters) << std::endl;
}

Widget::~Widget()
{
    makeCurrent();
}

void Widget:: loadAscllStl(const QString& filename,int ratio,JointParameters &oJointPara)
{
    ZLOG << "load text file ";

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ZLOG << "Open stl_file failed.";
    }
    while (!file.atEnd())
    {
        QString line = file.readLine().trimmed();                                                 // trimmed去除了开头和结尾的空白字符串
        QStringList words = line.split(' ', QString::SkipEmptyParts);

        if (words[0] == "facet")
        {
            Normal = {ratio * words[2].toFloat(), ratio * words[3].toFloat(), ratio * words[4].toFloat()};
        }
        else if (words[0] == "vertex")
        {
            Position = {ratio * words[1].toFloat(), ratio * words[2].toFloat(), ratio * words[3].toFloat()};
            oJointPara.vecJoint.append(Position);
            oJointPara.vecJoint.append(Normal);
        }
        else
        {
            continue;
        }
    }
    ZLOG << "write vertice_temp success!";
    file.close();
    oJointPara.iNumberOfTriangle = oJointPara.vecJoint.capacity() / sizeof(float);
}

void Widget::SetDrawParameters(JointParameters &oJointPara)
{
    oJointPara.vaoJoint.create();                     // 创建一个VAO对象，OpenGL会给它（顶点数组缓存对象）分配一个id
    oJointPara.vaoJoint.bind();                         //将RC中的当前顶点数组缓存对象Id设置为VAO的id
    oJointPara.vboJoint.create();
    oJointPara.vboJoint.bind();
    oJointPara.vboJoint.allocate(oJointPara.vecJoint.data(),
                 sizeof(float) * oJointPara.vecJoint.size());                                         //将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
    shaderprogram.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, sizeof(GLfloat) * 6);
    shaderprogram.enableAttributeArray("aPos");
    shaderprogram.setAttributeBuffer("aNormal", GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 6);
    shaderprogram.enableAttributeArray("aNormal");
    this->glEnable(GL_DEPTH_TEST);
    oJointPara.vaoJoint.release(); //释放
    oJointPara.vboJoint.release();
}

void Widget::initializeGL()
{
    this->initializeOpenGLFunctions(); //初始化opengl函数
    shaderprogram.create();            //生成着色器程序
    if (!shaderprogram.addShaderFromSourceFile(QOpenGLShader::Vertex, "../../Test/Qt/stl.vert"))
    {
        ZLOG << "failed load ../../Test/Qt/stl.vert";         //如果编译出错,打印报错信息
    }
    if (!shaderprogram.addShaderFromSourceFile(QOpenGLShader::Fragment, "../../Test/Qt/stl.frag"))
    {
        ZLOG << "failed load ../../Test/Qt/stl.frag"; //如果编译出错,打印报错信息
    }
    //将添加到此程序的着色器与addshader链接在一起
    if (!shaderprogram.link())
    {
        ZLOG << "ERROR: link error"; //如果链接出错,打印报错信息
    }

    for (auto & ii : m_aJointModel)
    {
        SetDrawParameters(ii);
    }


//    for (int ii = 0; ii < 4; ii++)
//    {
//        SetDrawParameters(m_aJointModel[ii]);
//    }

    view.setToIdentity();
    view.lookAt(QVector3D(0.0f, 0.0f, 3.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));
    // shaderprogram.setUniformValue("view", view);
}
void Widget::resizeGL(int w, int h)
{
    this->glViewport(0, 0, w, h);
    projection.setToIdentity();
    projection.perspective(60.0f, (GLfloat)w / (GLfloat)h, 0.001f, 100.0f);
    // shaderprogram.setUniformValue("projection", projection);
}

void Widget::paintGL()
{
    this->glClearColor(0.9f, 0.94f, 1.0f, 1.0f);               //设置清屏颜色
    this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色缓冲区

    shaderprogram.bind();
    //将此着色器程序绑定到活动的qopenglcontext，并使其成为当前着色器程序。任何先前绑定的着色器程序都将被释放
    //成功绑定返回ture,反之，返回false.
    {
        QVector3D lightColor(1.0f, 1.0f, 1.0f);
        QVector3D objectColor(1.0f, 0.5f, 0.31f);
        QVector3D lightPos(-20.0f, 0.0f, 20.0f);

        shaderprogram.setUniformValue("objectColor", objectColor);
        shaderprogram.setUniformValue("lightColor", lightColor);
        shaderprogram.setUniformValue("lightPos", lightPos);
        model.setToIdentity();
        model.translate(xtrans, ytrans, ztrans);
        model.rotate(rotation);
        Rot.setToIdentity();
        Rot.rotate(-90, 1, 0,0);
        Rot.rotate(45, 0, 0,1);
        shaderprogram.setUniformValue("Rot",Rot);
        shaderprogram.setUniformValue("view", view);
        shaderprogram.setUniformValue("projection", projection);
        shaderprogram.setUniformValue("model", model);
        InitialTranslate();
        for (int ii = 0; ii < 7; ii++)
        {
            SetRobotRotation(ii);
            shaderprogram.setUniformValue("baseTrans", m_matJointTrans[ii]);
            m_aJointModel[ii].vaoJoint.bind();
            this->glDrawArrays(GL_TRIANGLES, 0, m_aJointModel[ii].iNumberOfTriangle);
        }
    }
}

void Widget::InitialTranslate()
{
    m_matJointTrans[0].setToIdentity();
    m_matJointTrans[1].setToIdentity();
    m_matJointTrans[1].translate(0,0,0.375);
    m_matJointTrans[1].rotate(-90, 1, 0, 0);
    m_matJointTrans[2].setToIdentity();
    m_matJointTrans[3].setToIdentity();
    m_matJointTrans[3].translate(0, -0.4, 0.02);
    m_matJointTrans[4].setToIdentity();
    m_matJointTrans[4].rotate(90,1,0,0);
    m_matJointTrans[5].setToIdentity();
    m_matJointTrans[5].translate(0, 0, 0.45);
    m_matJointTrans[5].rotate(-90,1,0,0);
    m_matJointTrans[6].setToIdentity();
    m_matJointTrans[6].translate(0, -0.07, 0.0);
    m_matJointTrans[6].rotate(90,1,0,0);
}

void Widget::SetRobotRotation(int iJointIndex)
{
    m_matJointRot[iJointIndex].setToIdentity();
    if (iJointIndex >= 1)
    {
        m_matJointRot[iJointIndex].rotate(m_fRotDegree[iJointIndex - 1],m_mapRotVector[iJointIndex - 1]);
        m_matJointTrans[iJointIndex] = m_matJointTrans[iJointIndex -1]  * m_matJointTrans[iJointIndex] * m_matJointRot[iJointIndex];
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    mousePos = QVector2D(event->pos());
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        QVector2D newPos = (QVector2D)event->pos();
        QVector2D diff = newPos - mousePos;
        qreal angle = (diff.length()) / 3.6;
        // Rotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
        mousePos = newPos;
        this->update();
    }
    event->accept();
}

void Widget::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 8;

    if (numDegrees.y() > 0)
    {
        ztrans += 0.25f;
    }
    else if (numDegrees.y() < 0)
    {
        ztrans -= 0.25f;
    }
    this->update();
    event->accept();
}

void Widget::SetRotationAngleOfJoint_0(int value)
{
    InitialTranslate();
    m_fRotDegree[0] = (float)value ;
    SetRobotRotation(0);
    update();
}

void Widget::SetRotationAngleOfJoint_1(int value)
{
    InitialTranslate();
    m_fRotDegree[1] = (float)value ;
    SetRobotRotation(1);
    update();
}

void Widget::SetRotationAngleOfJoint_2(int value)
{
    InitialTranslate();
    m_fRotDegree[2] = (float)value ;
    SetRobotRotation(2);
    update();
}

void Widget::SetRotationAngleOfJoint_3(int value)
{
    InitialTranslate();
    m_fRotDegree[3] = (float)value ;
    SetRobotRotation(3);
    update();
}

void Widget::SetRotationAngleOfJoint_4(int value)
{
    InitialTranslate();
    m_fRotDegree[4] = (float)value ;
    SetRobotRotation(4);
    update();
}

void Widget::SetRotationAngleOfJoint_5(int value)
{
    InitialTranslate();
    m_fRotDegree[5] = (float)value ;
    SetRobotRotation(5);
    update();
}

