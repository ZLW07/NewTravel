//
// Created by wei on 2022/5/21.
//

#include "myopenglwiegt.h"
#include <QDebug>
#include <QFile>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QStringList>
#include <QWheelEvent>
#include <QtMath>

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent), VBO(QOpenGLBuffer::VertexBuffer), xtrans(0), ytrans(0), ztrans(0.0),m_bContrlFlag(false)
{
    QSurfaceFormat format;
    format.setAlphaBufferSize(24); //设置alpha缓冲大小
    format.setVersion(3, 3);       //设置版本号
    format.setSamples(10);         //设置重采样次数，用于反走样

    this->setFormat(format);

    vertices = loadAscllStl("../../Data/RobotModel/TX2-60L FOREARM.STL", 1);
}

Widget::~Widget()
{
    makeCurrent();
}

QVector<float> Widget::loadAscllStl(QString filename, int ratio)
{
    QVector<float> vertices_temp;
    ZLOG << "load text file ";

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ZLOG << "Open stl_file failed.";
    }
    while (!file.atEnd())
    {
        QString line = file.readLine().trimmed(); // trimmed去除了开头和结尾的空白字符串
        QStringList words = line.split(' ', QString::SkipEmptyParts);

        if (words[0] == "facet")
        {
            Normal = {ratio * words[2].toFloat(), ratio * words[3].toFloat(), ratio * words[4].toFloat()};
        }
        else if (words[0] == "vertex")
        {
            Position = {ratio * words[1].toFloat(), ratio * words[2].toFloat(), ratio * words[3].toFloat()};
            vertices_temp.append(Position);
            vertices_temp.append(Normal);
        }
        else
        {
            continue;
        }
    }

    ZLOG << "write vertice_temp success!";
    file.close();
    return vertices_temp;
}

void Widget::initializeGL()
{
    this->initializeOpenGLFunctions(); //初始化opengl函数
    shaderprogram.create();            //生成着色器程序
    if (!shaderprogram.addShaderFromSourceFile(QOpenGLShader::Vertex, "../../Test/Qt/stl.vert"))
    {
        ZLOG << "failed load ../../Test/Qt/stl.vert"; //如果编译出错,打印报错信息
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
    //    QOpenGLVertexArrayObject::Binder{&VAO};

    VAO.create(); // 创建一个VAO对象，OpenGL会给它（顶点数组缓存对象）分配一个id
    VAO.bind();   //将RC中的当前顶点数组缓存对象Id设置为VAO的id
    VBO.create();
    VBO.bind();
    VBO.allocate(vertices.data(),
        sizeof(float) * vertices.size()); //将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度

    shaderprogram.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, sizeof(GLfloat) * 6);
    shaderprogram.enableAttributeArray("aPos");
    shaderprogram.setAttributeBuffer("aNormal", GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 6);
    shaderprogram.enableAttributeArray("aNormal");
    this->glEnable(GL_DEPTH_TEST);
    VAO.release(); //释放
    VBO.release();

    view.setToIdentity();
    view.lookAt(QVector3D(0.0f, 0.0f, 3.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f));
    //    view.setToIdentity();
    //    view.lookAt(QVector3D(v3dMoveLength[0], 0.0f, 3.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f,
    //    0.0f));
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
    this->glClearColor(0.9f, 0.94f, 1.0f, 1.0f);              //设置清屏颜色
    this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色缓冲区

    shaderprogram.bind();
    //将此着色器程序绑定到活动的qopenglcontext，并使其成为当前着色器程序。任何先前绑定的着色器程序都将被释放
    //成功绑定返回ture,反之，返回false.
    {
//        view.setToIdentity();
//        view.lookAt(QVector3D(v2dMoveLength[0], v2dMoveLength[1], 3.0f), QVector3D(0.0f, 0.0f, 0.0f),
//            QVector3D(0.0f, 1.0f, 0.0f));
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
        shaderprogram.setUniformValue("v2dMove", v2dMoveLength);

        int n = vertices.capacity() / sizeof(float);
        QOpenGLVertexArrayObject::Binder bind(&VAO); //绑定VAO
        this->glDrawArrays(GL_TRIANGLES, 0, n);
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
    }
    else if ((event->buttons() == Qt::RightButton) && m_bContrlFlag)
    {
        QVector2D newPos = (QVector2D)event->pos();
        QVector2D diff = newPos - mousePos;
        v2dMoveLength[0] += (diff.x() / 300);
        v2dMoveLength[1] -= (diff.y() / 400);
        mousePos = newPos;
    }
    this->update();
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

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Control:
    {
        m_bContrlFlag = true;
        break;
    }
    case Qt::Key_Escape:
    {
        v2dMoveLength[0] = 0.0;
        v2dMoveLength[1] = 0.0;
        mousePos[0] = 400;
        mousePos[1] = 300;
        QQuaternion oRotation;
        rotation = oRotation;
        this->update();
        break;
    }
    default:
    {
        ZLOG << " not match key";
        break;
    }
    }
    event->accept();
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Control:
    {
        m_bContrlFlag = false;
        break;
    }
    default:
    {
        break;
    }
    }
    event->accept();
}
