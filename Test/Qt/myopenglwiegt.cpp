//
// Created by wei on 2022/5/21.
//

#include "myopenglwiegt.h"
#include <GL/glut.h>
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWidget>

MyopenGLWiegt::MyopenGLWiegt(QWidget *parent) : QOpenGLWidget(parent)
{
    fullscreen = false;
    m_rtri = 0.0f;
    m_rquad = 0.0f;

    //    QTimer *timer = new QTimer(this);                   //创建一个定时器
    //    //将定时器的计时信号与updateGL()绑定
    //    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //    timer->start(10);
}

/*
 * 这里首先调用QOpenGLFunctions::initializeOpenGLFunctions()对OpenGL函数进行初始化，这样QOpenGLFunctions中的函数只能在当前环境中使用
 * 然后进行了着色器的i相关设置，使用QOpenGLShader创建了一个顶点着色器和一个片段着色器，并使用compileSourceCode()函数为着色器设置了源码并进行了编译
 * 下面创建了着色器程序QOpenGLShaderProgram对象，使用addShapder()将前面已经编译好的着色器添加进来，然后调用link()函数将所有加入到程序中的着色器链接到一起
 * 最后调用bind()函数将该着色器程序绑定到当前OpenGLhuanjingzhong1
 * (为了使程序尽量简单，这里直接在程序中编写了着色器源码，对于较复杂的着色器源码，一般是写在文件中的，可以使用compileSourceFile()进行加载编译。
 *  这个程序只是绘制一个白色的点，所以只需要指定一个顶点vec4和渲染颜色vec4，这里的vec4类型是GLSL的4位浮点数向量）
 */
void MyopenGLWiegt::initializeGL()
{

    glClearColor(0.0, 0.0, 0.0, 0.0); //黑色背景
    glShadeModel(GL_SMOOTH);          //启用阴影平滑

    glClearDepth(1.0);                                 //设置深度缓存
    glEnable(GL_DEPTH_TEST);                           //启用深度测试
    glDepthFunc(GL_LEQUAL);                            //所作深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //告诉系统对透视进行修正
}

/*
 * 作为简单示例，这里直接调用glDrawArrays()函数来进行OpenGL图形绘制
 * void glDrawArrays(GLenum mode,GLint first,GLsizei count)该函数使用当前绑定的顶点数组来建立几何图形
 * 第一个参数mode设置了构建图形的类型，GL_POINTS(点)、GL_LINES(线)、GL_LINE_STRIP(条带线)、GL_LINE_LOOP(循环线)、GL_TRIANGLES(独立三角形)、GL_TRIANGLE_STRIP(三角形条带)、GL_TRIANGLE_FAN(三角形扇面)
 * 第2个参数first指定元素起始位置，第3个参数count为元素位置
 * 就是用顶点数组中索引为first-first+count-1的元素为顶点来绘制mode指定的图形
 */
void MyopenGLWiegt::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存
    glLoadIdentity();                                   //重置当前的模型观察矩阵

    std::vector<float> vecData;
    vecData.push_back(-0.0);
    vecData.push_back(1.0);
    vecData.push_back(0.0);

    vecData.push_back(-1.0);
    vecData.push_back(-1.0);
    vecData.push_back(1.0);

    vecData.push_back(1.0);
    vecData.push_back(-1.0);
    vecData.push_back(1.0);

    glTranslatef(-1.5f, 0.0f, -6.0f);    //左移1.5单位，并移入屏幕6.0单位
    glRotatef(m_rtri, 0.0f, 1.0f, 0.0f); //绕y轴旋转三角形
    glBegin(GL_TRIANGLES);               //开始绘制金字塔
    glColor3f(1.0f, 0.0f, 0.0f);         //红色
                                         //    glVertex3f(0.0f, 1.0f, 0.0f);                   //上顶点(前侧面)
                                         //    //   glColor3f(0.0f, 1.0f, 0.0f);                    //绿色
                                         //    glVertex3f(-1.0f, -1.0f, 1.0f);                 //左下(前侧面)
                                         //    // glColor3f(0.0f, 0.0f, 1.0f);                    //蓝色
                                         //    glVertex3f(1.0f, -1.0f, 1.0f);                  //右下(前侧面)
    for (int ii = 0; ii < vecData.size(); ++ii)
    {
        glVertex3f(vecData.at(ii), vecData.at(ii + 1), vecData.at(ii + 2));
        ii = ii + 2;
    }

    //   glColor3f(1.0f, 0.0f, 0.0f);                    //红色
    glVertex3f(0.0f, 1.0f, 0.0f); //上顶点(右侧面)
    //  glColor3f(0.0f, 0.0f, 1.0f);                    //蓝色
    glVertex3f(1.0f, -1.0f, 1.0f);  //左下(右侧面)
                                    //    glColor3f(0.0f, 1.0f, 0.0f);                    //绿色
    glVertex3f(1.0f, -1.0f, -1.0f); //右下(右侧面)

    //   glColor3f(1.0f, 0.0f, 0.0f);                    //红色
    glVertex3f(0.0f, 1.0f, 0.0f);    //上顶点(后侧面)
                                     //    glColor3f(0.0f, 1.0f, 0.0f);                    //绿色
    glVertex3f(1.0f, -1.0f, -1.0f);  //左下(后侧面)
                                     //    glColor3f(0.0f, 0.0f, 1.0f);                    //蓝色
    glVertex3f(-1.0f, -1.0f, -1.0f); //右下(后侧面)

    //    glColor3f(1.0f, 0.0f, 0.0f);                    //红色
    glVertex3f(0.0f, 1.0f, 0.0f); //上顶点(左侧面)
    //   glColor3f(0.0f, 0.0f, 1.0f);                    //蓝色
    glVertex3f(-1.0f, -1.0f, -1.0f); //左下(左侧面)
    // glColor3f(0.0f, 1.0f, 0.0f);                    //绿色
    glVertex3f(-1.0f, -1.0f, 1.0f); //右下(左侧面)
    glEnd();                        //金字塔绘制结束

    //    glLoadIdentity();                                   //重置模型观察矩阵
    //    glTranslatef(1.5f, 0.0f, -6.0f);                    //右移1.5单位，并移入屏幕6.0单位
    //    glRotatef(m_rquad, 1.0f, 0.0f, 0.0f);               //绕x轴旋转四边形
    //    glBegin(GL_QUADS);                                  //开始绘制立方体
    //    glColor3f(0.0f, 1.0f, 0.0f);                    //绿色
    //    glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(顶面)
    //    glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(顶面)
    //    glVertex3f(-1.0f, 1.0f, 1.0f);                  //左下(顶面)
    //    glVertex3f(1.0f, 1.0f, 1.0f);                   //右下(顶面)
    //
    //    glColor3f(1.0f, 0.5f, 0.0f);                    //橙色
    //    glVertex3f(1.0f, -1.0f, 1.0f);                  //右上(底面)
    //    glVertex3f(-1.0f, -1.0f, 1.0f);                 //左上(底面)
    //    glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(底面)
    //    glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(底面)
    //
    //    glColor3f(1.0f, 0.0f, 0.0f);                    //红色
    //    glVertex3f(1.0f, 1.0f, 1.0f);                   //右上(前面)
    //    glVertex3f(-1.0f, 1.0f, 1.0f);                  //左上(前面)
    //    glVertex3f(-1.0f, -1.0f, 1.0f);                 //左下(前面)
    //    glVertex3f(1.0f, -1.0f, 1.0f);                  //右下(前面)
    //
    //    glColor3f(1.0f, 1.0f, 0.0f);                    //黄色
    //    glVertex3f(1.0f, -1.0f, -1.0f);                 //右上(后面)
    //    glVertex3f(-1.0f, -1.0f, -1.0f);                //左上(后面)
    //    glVertex3f(-1.0f, 1.0f, -1.0f);                 //左下(后面)
    //    glVertex3f(1.0f, 1.0f, -1.0f);                  //右下(后面)
    //
    //    glColor3f(0.0f, 0.0f, 1.0f);                    //蓝色
    //    glVertex3f(-1.0f, 1.0f, 1.0f);                  //右上(左面)
    //    glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(左面)
    //    glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(左面)
    //    glVertex3f(-1.0f, -1.0f, 1.0f);                 //右下(左面)
    //
    //    glColor3f(1.0f, 0.0f, 1.0f);                    //紫色
    //    glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(右面)
    //    glVertex3f(1.0f, 1.0f, 1.0f);                   //左上(右面)
    //    glVertex3f(1.0f, -1.0f, 1.0f);                  //左下(右面)
    //    glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(右面)
    //    glEnd();                                            //立方体绘制结束

    m_rtri += 0.5f;  //增加金字体的旋转变量
    m_rquad -= 0.5f; //减少立方体的旋转变量
}

void MyopenGLWiegt::resizeGL(int width, int height)
{
    glViewport(0, 0, (GLint)width, (GLint)height); //重置当前的视口
    glMatrixMode(GL_PROJECTION);                   //选择投影矩阵
    glLoadIdentity();                              //重置投影矩阵
    //设置视口的大小
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW); //选择模型观察矩阵
    glLoadIdentity();
}

void MyopenGLWiegt::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        // F1为全屏和普通屏的切换键
    case Qt::Key_F1:
        fullscreen = !fullscreen;
        if (fullscreen)
        {
            showFullScreen();
        }
        else
        {
            showNormal();
        }
        update();
        //        updateGL();
        break;
        // ESC为退出键
    case Qt::Key_Escape:
        close();
    }
}
