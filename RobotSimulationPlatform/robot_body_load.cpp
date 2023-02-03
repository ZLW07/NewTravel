//
// Created by wei on 2022/5/21.
//

#include "robot_body_load.h"
#include "Configure/configure_base.h"
#include <QFile>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QStringList>

RobotBody::RobotBody(QWidget *parent)
    : QOpenGLWidget(parent), alpha(0.0), theta(0.0), m_dEyeToModelDistance(0.00), m_v2cMove(0.0, 0.0)
{
    QSurfaceFormat format;
    format.setAlphaBufferSize(24); //设置alpha缓冲大小
    format.setVersion(3, 3);       //设置版本号
    format.setSamples(10);         //设置重采样次数，用于反走样
    m_bIsFile = false;
    m_bTargetJointRadianFlag = false;
    m_bMillimeterFlag = false;
    this->setFormat(format);

    // Set Joint rotation
    QVector3D qRotVector(0, -1, 0);
    m_mapRotVector[0] = qRotVector;
    qRotVector = {0, 0, 1};
    m_mapRotVector[1] = qRotVector;
    qRotVector = {0, 0, 1};
    m_mapRotVector[2] = qRotVector;
    qRotVector = {0, 0, 1};
    m_mapRotVector[3] = qRotVector;
    qRotVector = {0, 0, 1};
    m_mapRotVector[4] = qRotVector;
    qRotVector = {0, 0, 1};
    m_mapRotVector[5] = qRotVector;

/*    QVector3D qRotVector(0, 0, 1);
    m_mapRotVector[0] = qRotVector;
    qRotVector = {0, 0, 1};
    m_mapRotVector[1] = qRotVector;
    qRotVector = {0, 0, 1};
    m_mapRotVector[2] = qRotVector;
    qRotVector = {0, 0, 1};
    m_mapRotVector[3] = qRotVector;
    qRotVector = {0, 0, 1};
    m_mapRotVector[4] = qRotVector;
    qRotVector = {0, 0, 1};
    m_mapRotVector[5] = qRotVector;*/

    m_vecRotDegree.resize(6);
    for (float &ii : m_vecRotDegree)
    {
        ii = 0.0;
    }
    Rot.setToIdentity();
    m_v3dCamera = QVector3D(2, 0, 0.5);
    mousePosForTranslationView = QVector2D(0.0, 0.0);

    // External import fixed model
    m_matJointTrans[7].setToIdentity();
    m_matJointTrans[7].translate(0, -1, 0);
    m_matJointTrans[7].rotate(90, 1, 0, 0);
    m_matJointTrans[8].setToIdentity();
}

RobotBody::~RobotBody()
{
    makeCurrent();
}

void RobotBody::loadAscllStl(const QString &filename, int ratio, JointParameters &oJointPara)
{
    ZLOG << "load text file " << filename.toStdString();

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ZLOG << "Open stl_file failed.";
        return;
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
    oJointPara.iNumberOfTriangle = oJointPara.vecJoint.size()/6;
}

void RobotBody::SetDrawParameters(JointParameters &oJointPara)
{
    oJointPara.vaoJoint.create(); // 创建一个VAO对象，OpenGL会给它（顶点数组缓存对象）分配一个id
    oJointPara.vaoJoint.bind();   //将RC中的当前顶点数组缓存对象Id设置为VAO的id
    oJointPara.vboJoint.create();
    oJointPara.vboJoint.bind();
    oJointPara.vboJoint.allocate(oJointPara.vecJoint.data(),
        sizeof(float) *
            oJointPara.vecJoint.size()); //将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
    shaderprogram.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, sizeof(GLfloat) * 6);
    shaderprogram.enableAttributeArray("aPos");
    shaderprogram.setAttributeBuffer("aNormal", GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 6);
    shaderprogram.enableAttributeArray("aNormal");
    this->glEnable(GL_DEPTH_TEST);
    oJointPara.vaoJoint.release(); //释放
    oJointPara.vboJoint.release();
}

void RobotBody::initializeGL()
{
    this->initializeOpenGLFunctions(); //初始化opengl函数
    shaderprogram.create();            //生成着色器程序
    const char *vertexShaderSource =
        "#version 330 core \n"
        "layout (location = 0) in vec3 aPos; \n"
        "layout (location = 1) in vec3 aNormal; \n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "uniform vec2 v2dMove;\n"
        "uniform mat4 baseTrans;\n"
        "uniform mat4 Rot;\n"
        "out vec3 FragPos;\n"
        "out vec3 Normal;\n"
        "void main()\n"
        "{\n"
        "gl_Position = Rot * projection * view * baseTrans * vec4(aPos[0] ,aPos[1] , aPos[2],1.0);\n"
        "Normal = vec3(baseTrans * vec4(aNormal,1.0));\n"
        "FragPos = vec3(vec4(aPos, 1.0));\n"
        "}\0";
    // 片段着色器
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "uniform vec3 objectColor;\n"
                                       "uniform vec3 lightColor;\n"
                                       "in vec3 FragPos;\n"
                                       "in vec3 Normal;\n"
                                       "uniform vec3 lightPos;\n"
                                       "void main()\n"
                                       "{\n"
                                       "float ambientStrength = 0.05;\n"
                                       "vec3 ambient = ambientStrength * lightColor;\n"
                                       "vec3 norm = normalize(Normal);\n"
                                       "vec3 lightDir = normalize(lightPos - FragPos);\n"
                                       "float diff = max(dot(norm, lightDir), 0.0);\n"
                                       "vec3 diffuse = diff * lightColor;\n"
                                       "vec3 result = (ambient + diffuse) * objectColor;\n"
                                       "FragColor = vec4(result, 1.0);\n"
                                       "}\n\0";
    shaderprogram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    shaderprogram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    //将添加到此程序的着色器与addshader链接在一起
    if (!shaderprogram.link())
    {
        ZLOG << "ERROR: link error"; //如果链接出错,打印报错信息
    }
}

void RobotBody::resizeGL(int w, int h)
{
    this->glViewport(0, 0, w, h);
    projection.setToIdentity();
    projection.perspective(60.0f, (GLfloat)w / (GLfloat)h, 0.001f, 500.0f);
}

void RobotBody::paintGL()
{
    this->glClearColor(0.9f, 0.94f, 1.0f, 1.0f);              //设置清屏颜色
    this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色缓冲区
    if (m_bIsFile)
    {
        std::vector<std::string> sPath;
        if (ReadXml(sPath))
        {
            for (size_t ii = 0; ii < sPath.size(); ++ii)
            {
                loadAscllStl(sPath[ii].c_str(), 1, m_aJointModel[ii]);
                ZLOG << sPath[ii];
            }
            for (auto &ii : m_aJointModel)
            {
                SetDrawParameters(ii);
            }
            m_bIsFile = false;
        }
    }
    shaderprogram.bind();
    //将此着色器程序绑定到活动的qopenglcontext，并使其成为当前着色器程序。任何先前绑定的着色器程序都将被释放
    //成功绑定返回ture,反之，返回false.
    {
        QVector3D lightColor(1.0f, 1.0f, 1.0f);
        QVector3D objectColor(1.0f, 0.5f, 0.31f);
        QVector3D lightPos(m_oRobotCamera.NewEye->x(), m_oRobotCamera.NewEye->y(), m_oRobotCamera.NewEye->z());

        GLfloat mat_ambient[] = {0.0f, 0.0f, 0.2f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

        view.setToIdentity();
        view.lookAt(QVector3D(m_oRobotCamera.NewEye->x(), m_oRobotCamera.NewEye->y(), m_oRobotCamera.NewEye->z()),
            QVector3D(m_oRobotCamera.NewView->x(), m_oRobotCamera.NewView->y(), m_oRobotCamera.NewView->z()),
            QVector3D(m_oRobotCamera.NewUp->x(), m_oRobotCamera.NewUp->y(), m_oRobotCamera.NewUp->z()));

        shaderprogram.setUniformValue("objectColor", objectColor);
        shaderprogram.setUniformValue("lightColor", lightColor);
        shaderprogram.setUniformValue("lightPos", lightPos);

        Rot.translate(m_v2cMove.x(), -m_v2cMove.y(), 0);
        m_v2cMove = QVector2D(0, 0);
        shaderprogram.setUniformValue("Rot", Rot);
        shaderprogram.setUniformValue("view", view);
        projection.translate(0.0, 0.0, m_dEyeToModelDistance);
        m_dEyeToModelDistance = 0.0;
        shaderprogram.setUniformValue("projection", projection);
        InitialTranslate();
        for (int ii = 0; ii < 6; ii++)
        {
            SetRobotRotation(ii);
            shaderprogram.setUniformValue("baseTrans", m_matJointTrans[ii]);
            m_aJointModel[ii].vaoJoint.bind();
            this->glDrawArrays(GL_TRIANGLES, 0, m_aJointModel[ii].iNumberOfTriangle);
        }
        shaderprogram.setUniformValue("baseTrans", m_matJointTrans[6]);
        m_aJointModel[6].vaoJoint.bind();
        this->glDrawArrays(GL_TRIANGLES, 0, m_aJointModel[6].iNumberOfTriangle);

        shaderprogram.setUniformValue("baseTrans", m_matJointTrans[7]);
        m_aJointModel[7].vaoJoint.bind();
        this->glDrawArrays(GL_TRIANGLES, 0, m_aJointModel[7].iNumberOfTriangle);

        shaderprogram.setUniformValue("baseTrans", m_matJointTrans[8]);
        m_aJointModel[8].vaoJoint.bind();
        this->glDrawArrays(GL_LINES, 0, m_aJointModel[8].iNumberOfTriangle);
    }
}

void RobotBody::InitialTranslate()
{
    m_matJointTrans[0].setToIdentity();
    m_matJointTrans[1].setToIdentity();
    m_matJointTrans[1].translate(0, 0, 0.375);
    m_matJointTrans[1].rotate(-90, 1, 0, 0);
    m_matJointTrans[2].setToIdentity();
    m_matJointTrans[3].setToIdentity();
    m_matJointTrans[3].translate(0, -0.4, 0.02);
    m_matJointTrans[4].setToIdentity();
    m_matJointTrans[4].rotate(90, 1, 0, 0);
    m_matJointTrans[5].setToIdentity();
    m_matJointTrans[5].translate(0, 0, 0.45);
    m_matJointTrans[5].rotate(-90, 1, 0, 0);
    m_matJointTrans[6].setToIdentity();
    m_matJointTrans[6].translate(0, -0.07, 0.0);
    m_matJointTrans[6].rotate(90, 1, 0, 0);

/*    m_matJointTrans[0].setToIdentity();
    m_matJointTrans[1].setToIdentity();
    m_matJointTrans[2].setToIdentity();
    m_matJointTrans[2].rotate(-90,1,0,0);
    m_matJointTrans[2].rotate(-90,0,0,1);
    m_matJointTrans[3].setToIdentity();
    m_matJointTrans[3].translate(0.4, 0, 0.02);
    m_matJointTrans[3].rotate(90,0,0,1);
    m_matJointTrans[4].setToIdentity();
    m_matJointTrans[4].translate(0, -0.45, 0);
    m_matJointTrans[4].rotate(90, 1, 0, 0);
    m_matJointTrans[5].setToIdentity();
    m_matJointTrans[5].rotate(-90, 1, 0, 0);
    m_matJointTrans[6].setToIdentity();
    m_matJointTrans[6].translate(0, -0.07, 0.0);
    m_matJointTrans[6].rotate(90, 1, 0, 0);*/
}

void RobotBody::SetRobotRotation(int iJointIndex)
{
    m_matJointRot[iJointIndex].setToIdentity();
    m_matJointRot[iJointIndex].rotate(m_vecRotDegree[iJointIndex], m_mapRotVector[iJointIndex]);
    m_matJointTrans[iJointIndex + 1] =
        m_matJointTrans[iJointIndex] * m_matJointTrans[iJointIndex + 1] * m_matJointRot[iJointIndex];
}

void RobotBody::mousePressEvent(QMouseEvent *event)
{
    mousePos = QVector2D(event->pos());
    m_oRobotCamera.getInitPos(event->x(), event->y());
}

void RobotBody::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::MiddleButton)
    {
        if (event->modifiers() == Qt::CTRL)
        {
            QVector2D newPos = (QVector2D)event->pos();
            m_v2cMove = (newPos - mousePos) / 500;
            mousePos = newPos;
        }
        else
        {
            m_oRobotCamera.executeRotateOperation(event->x(), event->y());
        }
    }
    this->update();
}

void RobotBody::wheelEvent(QWheelEvent *event)
{
    if (event->delta() >= 0)
    {
        m_dEyeToModelDistance = 0.1f;
    }
    else
    {
        m_dEyeToModelDistance = -0.1f;
    }
    this->update();
}

void RobotBody::SetRotationAngleOfJoint_0(double value)
{
    InitialTranslate();
    m_vecRotDegree[0] = (float)value;
    SetRobotRotation(0);
    m_v2cMove = QVector2D(0, 0);
    m_dEyeToModelDistance = 0.0;
    update();
}

void RobotBody::SetRotationAngleOfJoint_1(double value)
{
    InitialTranslate();
    m_vecRotDegree[1] = (float)value;
    SetRobotRotation(1);
    m_v2cMove = QVector2D(0, 0);
    m_dEyeToModelDistance = 0.0;
    update();
}

void RobotBody::SetRotationAngleOfJoint_2(double value)
{
    InitialTranslate();
    m_vecRotDegree[2] = (float)value;
    SetRobotRotation(2);
    m_v2cMove = QVector2D(0, 0);
    m_dEyeToModelDistance = 0.0;
    update();
}

void RobotBody::SetRotationAngleOfJoint_3(double value)
{
    InitialTranslate();
    m_vecRotDegree[3] = (float)value;
    SetRobotRotation(3);
    m_v2cMove = QVector2D(0, 0);
    m_dEyeToModelDistance = 0.0;
    update();
}

void RobotBody::SetRotationAngleOfJoint_4(double value)
{
    InitialTranslate();
    m_vecRotDegree[4] = (float)value;
    SetRobotRotation(4);
    m_v2cMove = QVector2D(0, 0);
    m_dEyeToModelDistance = 0.0;
    update();
}

void RobotBody::SetRotationAngleOfJoint_5(double value)
{
    InitialTranslate();
    m_vecRotDegree[5] = (float)value;
    SetRobotRotation(5);
    m_v2cMove = QVector2D(0, 0);
    m_dEyeToModelDistance = 0.0;
    update();
}

void RobotBody::SetFilePath(const QString &sFilePath)
{
    m_sXmlFile = sFilePath;
    ZLOG << "The path is: " << sFilePath.toStdString();
    m_bIsFile = true;
    update();
}

bool RobotBody::ReadXml(std::vector<std::string> &vecNodePath)
{
    LoadConfigre oConfig;
    oConfig.ReadXML(m_sXmlFile.toStdString());

    std::string sNodePath = "/Joint";
    int iCount = oConfig.GetCountBrotherElement(sNodePath);

    std::string sResult;
    for (int ii = 0; ii < iCount; ++ii)
    {
        ZLOG << "sNodePath: " << sNodePath + "[" + std::to_string(ii) + "]";
        if (!oConfig.GetElementValue(sNodePath + "[" + std::to_string(ii) + "]", sResult))
        {
            ZLOG << "Failed to load xml " << sNodePath;
            return false;
        }
        vecNodePath.push_back(sResult);
    }
    return true;
}

void RobotBody::setTargetJoints(const QString &sTrans)
{
    std::string sTargetJoint = sTrans.toStdString();
    ZLOG << "The path is: " << sTargetJoint;
    int iIndex = sTargetJoint.find(',');
    int iCount = 0;
    while (std::string::npos != iIndex)
    {
        std::string sJointValue = sTargetJoint.substr(0, sTargetJoint.find(','));
        m_vecRotDegree[iCount] = strtod(sJointValue.c_str(), nullptr);
        iCount++;
        sTargetJoint = sTargetJoint.substr(sTargetJoint.find(',') + 1, std::string::npos);
        iIndex = sTargetJoint.find(',');
    }
    m_vecRotDegree[5] = strtod(sTargetJoint.c_str(), nullptr);
    if (m_bTargetJointRadianFlag)
    {
        for (int ii = 0; ii < m_vecRotDegree.size(); ++ii)
        {
            double dDegree = m_vecRotDegree[ii] * 180 / 3.1415926;
            m_vecRotDegree[ii] = dDegree;
        }
    }
    SetJointValue();
}

void RobotBody::SetJointValue()
{
    emit SetRotationOfJoint_0(m_vecRotDegree[0]);
    emit SetRotationOfJoint_1(m_vecRotDegree[1]);
    emit SetRotationOfJoint_2(m_vecRotDegree[2]);
    emit SetRotationOfJoint_3(m_vecRotDegree[3]);
    emit SetRotationOfJoint_4(m_vecRotDegree[4]);
    emit SetRotationOfJoint_5(m_vecRotDegree[5]);
}
void RobotBody::SetTargetJointDegreeFlag(bool bDegreeFlag)
{
    m_bTargetJointRadianFlag = bDegreeFlag;
    ZLOG << " Degree flag is " << m_bTargetJointRadianFlag;
}

void RobotBody::SetOtherModelTransform(QMatrix4x4 mat4Tansform)
{
    if (mat4Tansform(3,0) != 1)
    {
        QVector4D vecPos;
        if (m_bMillimeterFlag)
        {
            vecPos[0] = mat4Tansform(0, 3)/1000;
            vecPos[1] = mat4Tansform(1, 3)/1000;
            vecPos[2] = mat4Tansform(2, 3)/1000;
            vecPos[3] = 1;
            mat4Tansform.setColumn(3,vecPos);
        }
        m_matJointTrans[7] = mat4Tansform;
        ZLOG << "TransForm is: " << mat4Tansform(0, 0) << ", " << mat4Tansform(1, 1) << ", " << mat4Tansform(1, 2) << ", "
             << mat4Tansform(0, 3);
        ZLOG << "TransForm is: " << mat4Tansform(1, 0) << ", " << mat4Tansform(2, 1) << ", " << mat4Tansform(2, 2) << ", "
             << mat4Tansform(1, 3);
        ZLOG << "TransForm is: " << mat4Tansform(2, 0) << ", " << mat4Tansform(2, 1) << ", " << mat4Tansform(2, 2) << ", "
             << mat4Tansform(2, 3);
        update();
    }
}
void RobotBody::SetUnitOfLength(bool bIsMillimeter)
{
    m_bMillimeterFlag = true;
}
