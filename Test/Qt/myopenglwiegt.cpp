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
    loadAscllStl("../../Data/RobotModel/TX2-60L HORIZONTAL BASE.STL", 1, m_aJointModel[0]);
    loadAscllStl("../../Data/RobotModel/TX2-60L SHOULDER.STL", 1,m_aJointModel[1]);
    loadAscllStl("../../Data/RobotModel/TX2-60L ARM.STL", 1,m_aJointModel[2]);
    loadAscllStl("../../Data/RobotModel/TX2-60L ELBOW.STL", 1,m_aJointModel[3]);
    loadAscllStl("../../Data/RobotModel/TX2-60L FOREARM.STL", 1,m_aJointModel[4]);
    loadAscllStl("../../Data/RobotModel/TX2-60L WRIST.STL", 1,m_aJointModel[5]);

//    loadAscllStl("../../Data/RobotModel/TX2-60L_Joint_0.STL", 1,m_aJointModel[0]);
//    loadAscllStl("../../Data/RobotModel/TX2-60L_Joint_1.STL", 1,m_aJointModel[1]);
//    loadAscllStl("../../Data/RobotModel/TX2-60L_Joint_2.STL", 1,m_aJointModel[2]);
//    loadAscllStl("../../Data/RobotModel/TX2-60L_Joint_3.STL", 1,m_aJointModel[3]);
//    loadAscllStl("../../Data/RobotModel/TX2-60L_Joint_4.STL", 1,m_aJointModel[4]);
//    loadAscllStl("../../Data/RobotModel/TX2-60L_Joint_5.STL", 1,m_aJointModel[5]);

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
        QVector3D lightPos(0.0f, 0.0f, 50.0f);

        shaderprogram.setUniformValue("objectColor", objectColor);
        shaderprogram.setUniformValue("lightColor", lightColor);
        shaderprogram.setUniformValue("lightPos", lightPos);

        model.setToIdentity();
        model.translate(xtrans, ytrans, ztrans);
        model.rotate(rotation);
        shaderprogram.setUniformValue("view", view);
        shaderprogram.setUniformValue("projection", projection);
        shaderprogram.setUniformValue("model", model);

        for (auto & ii : m_aJointModel)
        {
            ii.vaoJoint.bind();
            this->glDrawArrays(GL_TRIANGLES, 0, ii.iNumberOfTriangle);
        }

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
