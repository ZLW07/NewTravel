//
// Created by wei on 2022/12/22.
//

#ifndef NEWTRAVEL_SIMULATION_H
#define NEWTRAVEL_SIMULATION_H
#include <QFileDialog>

#include "robot_body_load.h"
#include "robot_joint_degree_control_slider.h"
#include "robot_joint_degree_spinbox.h"
#include "robot_joint_label.h"
#include "robot_pushbutton_openfile.h"
#include "robot_qtext.h"
#include "ui_robot_simulation_platform.h"
#include <QGroupBox>
#include <QKeyEvent>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
class RobotSimulationPlatform;
}

namespace Ui
{

class RobotSimulation : public RobotSimulationPlatform, public QWidget
{
public:
    RobotSimulation(QWidget *parent = nullptr);
    void Init();

    void InitIconInitialPosition();
    void InitSignalConnection();
    void SetUpUI(QWidget *RobotSimulationPlatform);
    void RetranslateUi(QWidget *RobotSimulationPlatform);

public:
    void InitMainWindow(QWidget *RobotSimulationPlatform);
    void InitRobotShowGroupt(QWidget *pQWidget);

    void InitRobotShowAndButtonVerticalLayout();
    void InitMainGridLayout(QWidget *pQWidget);
    void InitPushButtonGroup();
    void InitRobotControllerVerticalLayout();
    void InitRobtJointsGroup();
    void InitRobtJointsWidget();
    void InitRobotJointsVerticalLayout();
    void InitRobtJoint_1HorizontalLayout();
    void InitRobotJointsController();

    void InitRobotTargetJointSettingFormat();
    void InitRobotTargetJointSettingComponent();

    void InitLoadOtherModelComponent();
    void InitLoadOtherModelFormat();

    void SetMainGridLayout();
    void SetRobotShowAndButtonVerticalLayout();
    void SetRobotControllerVerticalLayout();
    void SetRobotJointsController();
    void SetRobotJointsVerticalLayout();

    void SetRobotTargetJointsFormat();
    void SetLoadOtherModelFormat();

    void keyPressEvent(QKeyEvent *ev) override;

private:
    RobotJointSpinBox *m_pMySpinBox[6]{};
    RobotJointDegreeControlSlider *m_pMySlider[6]{};
    RobotJointLabel *m_pMyJointLabel[6]{};
    QHBoxLayout *m_pRobotJointsHorizontalLayout[6]{};
    OpenFile *pOpenFile{};
    FileDialog *m_pFileDialog{};
    InputText *m_pTargetTrans;
};

RobotSimulation::RobotSimulation(QWidget *parent) : QWidget(parent)
{
    Init();
    SetUpUI(this);
    InitIconInitialPosition();
    InitSignalConnection();
}

void RobotSimulation::SetUpUI(QWidget *RobotSimulationPlatform)
{
    if (RobotSimulationPlatform->objectName().isEmpty())
        RobotSimulationPlatform->setObjectName(QString::fromUtf8("RobotSimulationPlatform"));

    InitMainWindow(RobotSimulationPlatform);
    InitMainGridLayout(m_pMainWidget);

    InitRobotShowGroupt(m_pMainWidget);
    InitPushButtonGroup();

    InitRobotShowAndButtonVerticalLayout();
    SetRobotShowAndButtonVerticalLayout();

    InitRobtJointsGroup();
    InitRobtJointsWidget();

    InitRobtJoint_1HorizontalLayout();

    InitRobotJointsController();
    SetRobotJointsController();

    InitRobotJointsVerticalLayout();
    SetRobotJointsVerticalLayout();

    InitRobotTargetJointSettingFormat();

    InitRobotTargetJointSettingComponent();

    SetRobotTargetJointsFormat();

    InitLoadOtherModelFormat();
    InitLoadOtherModelComponent();
    //

    SetLoadOtherModelFormat();

    InitRobotControllerVerticalLayout();
    SetRobotControllerVerticalLayout();

    SetMainGridLayout();

    QMetaObject::connectSlotsByName(RobotSimulationPlatform);
    RetranslateUi(RobotSimulationPlatform);
}

void RobotSimulation::RetranslateUi(QWidget *RobotSimulationPlatform)
{
    RobotSimulationPlatform->setWindowTitle(
        QApplication::translate("RobotSimulationPlatform", "RobotSimulationPlatform", nullptr));

} // retranslateUi

void RobotSimulation::InitIconInitialPosition()
{
    for (int ii = 0; ii < 6; ++ii)
    {
        m_pMySpinBox[ii]->SetLimitValue(180, -180, 1);
        m_pMySlider[ii]->setMaximum(180);
        m_pMySlider[ii]->setMinimum(-180);
        m_pMySlider[ii]->setValue(0);
    }
}

void RobotSimulation::InitSignalConnection()
{
    for (int ii = 0; ii < 6; ++ii)
    {
        QObject::connect(m_pMySlider[ii], SIGNAL(valueChanged(double)), m_pMySpinBox[ii], SLOT(setValue(double)));
        QObject::connect(m_pMySpinBox[ii], SIGNAL(valueChanged(double)), m_pMySlider[ii], SLOT(setValue(double)));
    }
    QObject::connect(m_pMySlider[0], SIGNAL(valueChanged(double)), openGLWidget,
        SLOT(SetRotationAngleOfJoint_0(double)));
    QObject::connect(m_pMySlider[1], SIGNAL(valueChanged(double)), openGLWidget,
        SLOT(SetRotationAngleOfJoint_1(double)));
    QObject::connect(m_pMySlider[2], SIGNAL(valueChanged(double)), openGLWidget,
        SLOT(SetRotationAngleOfJoint_2(double)));
    QObject::connect(m_pMySlider[3], SIGNAL(valueChanged(double)), openGLWidget,
        SLOT(SetRotationAngleOfJoint_3(double)));
    QObject::connect(m_pMySlider[4], SIGNAL(valueChanged(double)), openGLWidget,
        SLOT(SetRotationAngleOfJoint_4(double)));
    QObject::connect(m_pMySlider[5], SIGNAL(valueChanged(double)), openGLWidget,
        SLOT(SetRotationAngleOfJoint_5(double)));
    QObject::connect(m_pFileDialog, SIGNAL(fileSelected(const QString &)), openGLWidget,
        SLOT(SetFilePath(const QString &)));
    QObject::connect(m_pTargetTrans, SIGNAL(SetValue(const QString &)), openGLWidget,
                     SLOT(setTransForm(const QString &)));
}

void RobotSimulation::InitRobotShowGroupt(QWidget *pQWidget)
{
    m_pRobotGroup = new QGroupBox(pQWidget);
    m_pRobotGroup->setObjectName(QString::fromUtf8("groupBox_4"));
    openGLWidget = new RobotBody(m_pRobotGroup);
    openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
    openGLWidget->setEnabled(true);
    openGLWidget->setGeometry(QRect(20, 40, 721, 611));
    openGLWidget->setMinimumSize(QSize(650, 600));
}

void RobotSimulation::InitMainGridLayout(QWidget *pQWidget)
{
    m_pMainGridLayout = new QGridLayout(pQWidget);
    m_pMainGridLayout->setObjectName(QString::fromUtf8("gridLayout"));
}

void RobotSimulation::InitRobotShowAndButtonVerticalLayout()
{
    m_pRobotShowAndButtonVerticalLayout = new QVBoxLayout();
    m_pRobotShowAndButtonVerticalLayout->setSpacing(6);
    m_pRobotShowAndButtonVerticalLayout->setObjectName(QString::fromUtf8("verticalLayout_4"));
}

void RobotSimulation::InitMainWindow(QWidget *RobotSimulationPlatform)
{
    RobotSimulationPlatform->resize(1200, 850);
    RobotSimulationPlatform->setWindowTitle("史陶比尔机器人三维仿真软件");

    m_pMainWidget = new QWidget(RobotSimulationPlatform);
    m_pMainWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    m_pMainWidget->setGeometry(QRect(10, 10, 1151, 791));
}

void RobotSimulation::InitPushButtonGroup()
{
    m_pPushButtonGroup = new QGroupBox(m_pMainWidget);
    m_pPushButtonGroup->setObjectName(QString::fromUtf8("groupBox_5"));
    m_pSplitterPushButton = new QSplitter(m_pPushButtonGroup);
    m_pSplitterPushButton->setObjectName(QString::fromUtf8("splitter_3"));
    m_pSplitterPushButton->setGeometry(QRect(0, 20, 311, 41));
    m_pSplitterPushButton->setOrientation(Qt::Horizontal);
    m_pFileDialog = new FileDialog(m_pSplitterPushButton);
    pOpenFile = new OpenFile(m_pFileDialog, m_pSplitterPushButton);
    pOpenFile->setObjectName(QString::fromUtf8("pushButton"));
    pOpenFile->setText("加载存储模型路径文件");

    m_pSplitterPushButton->addWidget(pOpenFile);
    pushButton_2 = new QPushButton(m_pSplitterPushButton);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setText("待定");
    m_pSplitterPushButton->addWidget(pushButton_2);
}

void RobotSimulation::SetRobotShowAndButtonVerticalLayout()
{
    m_pRobotShowAndButtonVerticalLayout->addWidget(m_pRobotGroup);
    m_pRobotShowAndButtonVerticalLayout->addWidget(m_pPushButtonGroup);

    m_pRobotShowAndButtonVerticalLayout->setStretch(0, 6);
    m_pRobotShowAndButtonVerticalLayout->setStretch(1, 1);
}

void RobotSimulation::SetMainGridLayout()
{
    m_pMainGridLayout->setContentsMargins(0, 0, 0, 0);
    m_pMainGridLayout->addLayout(m_pRobotShowAndButtonVerticalLayout, 0, 0, 1, 1);
    m_pMainGridLayout->addLayout(m_pVerticalLayoutRobotController, 0, 1, 1, 1);
    m_pMainGridLayout->setColumnStretch(0, 2);
    m_pMainGridLayout->setColumnStretch(1, 1);
}

void RobotSimulation::InitRobotControllerVerticalLayout()
{
    m_pVerticalLayoutRobotController = new QVBoxLayout();
    m_pVerticalLayoutRobotController->setObjectName(QString::fromUtf8("verticalLayout_5"));
}
void RobotSimulation::SetRobotControllerVerticalLayout()
{
    m_pVerticalLayoutRobotController->addWidget(m_pGroupBoxRobotJoints);
    m_pVerticalLayoutRobotController->addWidget(m_pGroupBoxTargetJointsSettingCenter);
    m_pVerticalLayoutRobotController->addWidget(m_pGroupBoxOtherModelSetting);

    m_pVerticalLayoutRobotController->setStretch(0, 2);
    m_pVerticalLayoutRobotController->setStretch(1, 1);
    m_pVerticalLayoutRobotController->setStretch(2, 1);
}
void RobotSimulation::InitRobtJointsGroup()
{
    m_pGroupBoxRobotJoints = new QGroupBox(m_pMainWidget);
    m_pGroupBoxRobotJoints->setObjectName(QString::fromUtf8("groupBox"));
    m_pGroupBoxRobotJoints->setMinimumSize(QSize(2, 12));
    m_pGroupBoxRobotJoints->setTabletTracking(false);
}
void RobotSimulation::InitRobtJointsWidget()
{
    m_pQWidgetRobotJoint = new QWidget(m_pGroupBoxRobotJoints);
    m_pQWidgetRobotJoint->setObjectName(QString::fromUtf8("layoutWidget1"));
    m_pQWidgetRobotJoint->setGeometry(QRect(10, 30, 361, 250));
}

void RobotSimulation::InitRobotJointsVerticalLayout()
{
    m_pVerticalLayoutRobotJoints = new QVBoxLayout(m_pQWidgetRobotJoint);
    m_pVerticalLayoutRobotJoints->setSpacing(16);
    m_pVerticalLayoutRobotJoints->setObjectName(QString::fromUtf8("verticalLayout"));
    m_pVerticalLayoutRobotJoints->setContentsMargins(0, 0, 0, 0);
}

void RobotSimulation::InitRobtJoint_1HorizontalLayout()
{
    for (auto &ii : m_pRobotJointsHorizontalLayout)
    {
        ii = new QHBoxLayout();
        ii->setObjectName(QString::fromUtf8("horizontalLayout"));
    }
}

void RobotSimulation::Init()
{
    m_pRobotJointsHorizontalLayout[0] = m_pHorizontalLayoutJoint_1;
    m_pRobotJointsHorizontalLayout[1] = m_pHorizontalLayoutJoint_2;
    m_pRobotJointsHorizontalLayout[2] = m_pHorizontalLayoutJoint_3;
    m_pRobotJointsHorizontalLayout[3] = m_pHorizontalLayoutJoint_4;
    m_pRobotJointsHorizontalLayout[4] = m_pHorizontalLayoutJoint_5;
    m_pRobotJointsHorizontalLayout[5] = m_pHorizontalLayoutJoint_6;
}

void RobotSimulation::InitRobotJointsController()
{
    for (int ii = 0; ii < 6; ++ii)
    {
        m_pMyJointLabel[ii] = new RobotJointLabel();
        m_pMyJointLabel[ii]->Initial(ii);

        m_pMySpinBox[ii] = new RobotJointSpinBox(m_pQWidgetRobotJoint);
        m_pMySpinBox[ii]->setObjectName(QString::fromUtf8("doubleSpinBox"));

        m_pMySlider[ii] = new RobotJointDegreeControlSlider(m_pQWidgetRobotJoint);
        m_pMySlider[ii]->setObjectName(QString::fromUtf8("horizontalSlider"));
        m_pMySlider[ii]->setOrientation(Qt::Horizontal);
    }

}
void RobotSimulation::SetRobotJointsController()
{
    for (int ii = 0; ii < 6; ++ii)
    {
        m_pRobotJointsHorizontalLayout[ii]->addWidget(m_pMyJointLabel[ii]);
        m_pRobotJointsHorizontalLayout[ii]->addWidget(m_pMySpinBox[ii]);
        m_pRobotJointsHorizontalLayout[ii]->addWidget(m_pMySlider[ii]);
    }
}

void RobotSimulation::SetRobotJointsVerticalLayout()
{
    m_pVerticalLayoutRobotJoints->addLayout(m_pRobotJointsHorizontalLayout[0]);
    m_pVerticalLayoutRobotJoints->addLayout(m_pRobotJointsHorizontalLayout[1]);
    m_pVerticalLayoutRobotJoints->addLayout(m_pRobotJointsHorizontalLayout[2]);
    m_pVerticalLayoutRobotJoints->addLayout(m_pRobotJointsHorizontalLayout[3]);
    m_pVerticalLayoutRobotJoints->addLayout(m_pRobotJointsHorizontalLayout[4]);
    m_pVerticalLayoutRobotJoints->addLayout(m_pRobotJointsHorizontalLayout[5]);
}
void RobotSimulation::InitRobotTargetJointSettingFormat()
{
    m_pGroupBoxTargetJointsSettingCenter = new QGroupBox(m_pMainWidget);
    m_pGroupBoxTargetJointsSettingCenter->setObjectName(QString::fromUtf8("groupBox_3"));

    m_pWidgetTargetJointsSettingCenter = new QWidget(m_pGroupBoxTargetJointsSettingCenter);
    m_pWidgetTargetJointsSettingCenter->setObjectName(QString::fromUtf8("layoutWidget2"));
    m_pWidgetTargetJointsSettingCenter->setGeometry(QRect(10, 30, 361, 141));

    m_pVerticalLayoutTargetJointsSettingCenter = new QVBoxLayout(m_pWidgetTargetJointsSettingCenter);
    m_pVerticalLayoutTargetJointsSettingCenter->setObjectName(QString::fromUtf8("verticalLayout_2"));
    m_pVerticalLayoutTargetJointsSettingCenter->setContentsMargins(0, 0, 0, 0);

    m_pHorizontalLayoutTargetJointsLabel = new QHBoxLayout();
    m_pHorizontalLayoutTargetJointsLabel->setObjectName(QString::fromUtf8("horizontalLayout_7"));
}

void RobotSimulation::InitRobotTargetJointSettingComponent()
{
    m_pLabelSettingJoints = new QLabel(m_pWidgetTargetJointsSettingCenter);
    m_pLabelSettingJoints->setObjectName(QString::fromUtf8("Target joints"));
    m_pLabelSettingJoints->setText("目标关节值");

    m_pCheckBoxDegree = new QCheckBox(m_pWidgetTargetJointsSettingCenter);
    m_pCheckBoxDegree->setObjectName(QString::fromUtf8("Angular unit about target joint"));
    m_pCheckBoxDegree->setText("弧度");

//    m_pTextEditTargetJoints = new QTextEdit(m_pWidgetTargetJointsSettingCenter);
//    m_pTextEditTargetJoints->setObjectName(QString::fromUtf8("textEdit"));

    m_pTargetTrans = new InputText(m_pWidgetTargetJointsSettingCenter);
    m_pTargetTrans->setObjectName(QString::fromUtf8("textEdit"));

}
void RobotSimulation::SetRobotTargetJointsFormat()
{
    m_pHorizontalLayoutTargetJointsLabel->addWidget(m_pLabelSettingJoints);
    m_pHorizontalLayoutTargetJointsLabel->addWidget(m_pCheckBoxDegree);
    m_pVerticalLayoutTargetJointsSettingCenter->addLayout(m_pHorizontalLayoutTargetJointsLabel);
    m_pVerticalLayoutTargetJointsSettingCenter->addWidget(m_pTargetTrans);
}
void RobotSimulation::InitLoadOtherModelComponent()
{

    m_pLabelOtherModelTransformName = new QLabel(m_pWidgetOtherModelSetting);
    m_pLabelOtherModelTransformName->setObjectName(QString::fromUtf8("Transform from other model to robot"));
    m_pLabelOtherModelTransformName->setText("到机器人坐标系的转换矩阵");

    m_pCheckBoxTransformUnitOfLength = new QCheckBox(m_pWidgetOtherModelSetting);
    m_pCheckBoxTransformUnitOfLength->setObjectName(QString::fromUtf8("Unit Of Length"));
    m_pCheckBoxTransformUnitOfLength->setText("毫米");

    m_pCheckBoxOtherModelDegree = new QCheckBox(m_pWidgetOtherModelSetting);
    m_pCheckBoxOtherModelDegree->setObjectName(QString::fromUtf8("Angular Unit"));
    m_pCheckBoxOtherModelDegree->setText("弧度");

    m_pTextEditOtherModelTransform = new QTextEdit(m_pWidgetOtherModelSetting);
    m_pTextEditOtherModelTransform->setObjectName(QString::fromUtf8("textEdit_2"));
}
void RobotSimulation::InitLoadOtherModelFormat()
{
    m_pGroupBoxOtherModelSetting = new QGroupBox(m_pMainWidget);
    m_pGroupBoxOtherModelSetting->setObjectName(QString::fromUtf8("groupBox_2"));

    m_pWidgetOtherModelSetting = new QWidget(m_pGroupBoxOtherModelSetting);
    m_pWidgetOtherModelSetting->setObjectName(QString::fromUtf8("layoutWidget3"));
    m_pWidgetOtherModelSetting->setGeometry(QRect(10, 30, 361, 151));

    m_pVerticalLayoutOtherModel = new QVBoxLayout(m_pWidgetOtherModelSetting);
    m_pVerticalLayoutOtherModel->setObjectName(QString::fromUtf8("verticalLayout_3"));
    m_pVerticalLayoutOtherModel->setContentsMargins(0, 0, 0, 0);

    m_pHorizontalLayoutOtherModel = new QHBoxLayout();
    m_pHorizontalLayoutOtherModel->setObjectName(QString::fromUtf8("horizontalLayout_8"));
}

void RobotSimulation::SetLoadOtherModelFormat()
{
    m_pHorizontalLayoutOtherModel->addWidget(m_pLabelOtherModelTransformName);
    m_pHorizontalLayoutOtherModel->addWidget(m_pCheckBoxTransformUnitOfLength);
    m_pHorizontalLayoutOtherModel->addWidget(m_pCheckBoxOtherModelDegree);
    m_pVerticalLayoutOtherModel->addLayout(m_pHorizontalLayoutOtherModel);
    m_pVerticalLayoutOtherModel->addWidget(m_pTextEditOtherModelTransform);
}

void RobotSimulation::keyPressEvent(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Escape)
    {
        close();
    }
    else if (ev->key() == Qt::Key_E)
    {
        m_pTargetTrans->emitValue();
    }
}

} // namespace Ui

QT_END_NAMESPACE

#endif // NEWTRAVEL_SIMULATION_H
