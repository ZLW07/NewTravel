/********************************************************************************
** Form generated from reading UI file 'robot_simulation_platform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOT_SIMULATION_PLATFORM_H
#define UI_ROBOT_SIMULATION_PLATFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RobotSimulationPlatform
{
public:
    QWidget *m_pMainWidget;
    QGridLayout *m_pMainGridLayout;
    QVBoxLayout *m_pRobotShowAndButtonVerticalLayout;
    QGroupBox *m_pRobotGroup;
    QOpenGLWidget *openGLWidget;
    QGroupBox *m_pPushButtonGroup;
    QSplitter *m_pSplitterPushButton;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QVBoxLayout *m_pVerticalLayoutRobotController;
    QGroupBox *m_pGroupBoxRobotJoints;
    QWidget *m_pQWidgetRobotJoint;
    QVBoxLayout *m_pVerticalLayoutRobotJoints;

    QHBoxLayout *m_pHorizontalLayoutJoint_1;
    QLabel *m_pLabelRobotJoint_1;
    QDoubleSpinBox *m_pDoubleSpinBoxJoint_1;
    QSlider *m_pHorizontalSliderJoint_1;

    QHBoxLayout *m_pHorizontalLayoutJoint_2;
    QLabel *m_pLabelRobotJoint_2;
    QDoubleSpinBox *m_pDoubleSpinBoxJoint_2;
    QSlider *m_pHorizontalSliderJoint_2;

    QHBoxLayout *m_pHorizontalLayoutJoint_3;
    QLabel *m_pLabelRobotJoint_3;
    QDoubleSpinBox *m_pDoubleSpinBoxJoint_3;
    QSlider *m_pHorizontalSliderJoint_3;

    QHBoxLayout *m_pHorizontalLayoutJoint_4;
    QLabel *m_pLabelRobotJoint_4;
    QDoubleSpinBox *m_pDoubleSpinBoxJoint_4;
    QSlider *m_pHorizontalSliderJoint_4;

    QHBoxLayout *m_pHorizontalLayoutJoint_5;
    QLabel *m_pLabelRobotJoint_5;
    QDoubleSpinBox *m_pDoubleSpinBoxJoint_5;
    QSlider *m_pHorizontalSliderJoint_5;

    QHBoxLayout *m_pHorizontalLayoutJoint_6;
    QLabel *m_pLabelRobotJoint_6;
    QDoubleSpinBox *m_pDoubleSpinBoxJoint_6;
    QSlider *m_pHorizontalSliderJoint_6;

    QGroupBox *m_pGroupBoxTargetJointsSettingCenter;
    QWidget *m_pWidgetTargetJointsSettingCenter;
    QVBoxLayout *m_pVerticalLayoutTargetJointsSettingCenter;
    QHBoxLayout *m_pHorizontalLayoutTargetJointsLabel;
    QLabel *m_pLabelSettingJoints;
    QCheckBox *m_pCheckBoxDegree;
    QTextEdit *m_pTextEditTargetJoints;

    QGroupBox *m_pGroupBoxOtherModelSetting;
    QWidget *m_pWidgetOtherModelSetting;
    QVBoxLayout *m_pVerticalLayoutOtherModel;
    QHBoxLayout *m_pHorizontalLayoutOtherModel;
    QLabel *m_pLabelOtherModelTransformName;
    QCheckBox *m_pCheckBoxTransformUnitOfLength;
    QCheckBox *m_pCheckBoxOtherModelDegree;
    QTextEdit *m_pTextEditOtherModelTransform;

    void setupUi(QWidget *RobotSimulationPlatform)
    {
        if (RobotSimulationPlatform->objectName().isEmpty())
            RobotSimulationPlatform->setObjectName(QString::fromUtf8("RobotSimulationPlatform"));
        RobotSimulationPlatform->resize(1210, 916);
        m_pMainWidget = new QWidget(RobotSimulationPlatform);
        m_pMainWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        m_pMainWidget->setGeometry(QRect(10, 10, 1151, 791));
        m_pMainGridLayout = new QGridLayout(m_pMainWidget);
        m_pMainGridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        m_pMainGridLayout->setContentsMargins(0, 0, 0, 0);
        m_pRobotShowAndButtonVerticalLayout = new QVBoxLayout();
        m_pRobotShowAndButtonVerticalLayout->setSpacing(6);
        m_pRobotShowAndButtonVerticalLayout->setObjectName(QString::fromUtf8("verticalLayout_4"));
        m_pRobotGroup = new QGroupBox(m_pMainWidget);
        m_pRobotGroup->setObjectName(QString::fromUtf8("groupBox_4"));
        openGLWidget = new QOpenGLWidget(m_pRobotGroup);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setEnabled(true);
        openGLWidget->setGeometry(QRect(20, 40, 721, 611));
        openGLWidget->setMinimumSize(QSize(650, 600));

        m_pRobotShowAndButtonVerticalLayout->addWidget(m_pRobotGroup);

        m_pPushButtonGroup = new QGroupBox(m_pMainWidget);
        m_pPushButtonGroup->setObjectName(QString::fromUtf8("groupBox_5"));
        m_pSplitterPushButton = new QSplitter(m_pPushButtonGroup);
        m_pSplitterPushButton->setObjectName(QString::fromUtf8("splitter_3"));
        m_pSplitterPushButton->setGeometry(QRect(0, 20, 311, 41));
        m_pSplitterPushButton->setOrientation(Qt::Horizontal);
        pushButton = new QPushButton(m_pSplitterPushButton);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        m_pSplitterPushButton->addWidget(pushButton);
        pushButton_2 = new QPushButton(m_pSplitterPushButton);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        m_pSplitterPushButton->addWidget(pushButton_2);

        m_pRobotShowAndButtonVerticalLayout->addWidget(m_pPushButtonGroup);

        m_pRobotShowAndButtonVerticalLayout->setStretch(0, 6);
        m_pRobotShowAndButtonVerticalLayout->setStretch(1, 1);

        m_pMainGridLayout->addLayout(m_pRobotShowAndButtonVerticalLayout, 0, 0, 1, 1);

        m_pVerticalLayoutRobotController = new QVBoxLayout();
        m_pVerticalLayoutRobotController->setObjectName(QString::fromUtf8("verticalLayout_5"));
        m_pGroupBoxRobotJoints = new QGroupBox(m_pMainWidget);
        m_pGroupBoxRobotJoints->setObjectName(QString::fromUtf8("groupBox"));
        m_pGroupBoxRobotJoints->setMinimumSize(QSize(2, 12));
        m_pGroupBoxRobotJoints->setTabletTracking(false);
        m_pQWidgetRobotJoint = new QWidget(m_pGroupBoxRobotJoints);
        m_pQWidgetRobotJoint->setObjectName(QString::fromUtf8("layoutWidget1"));
        m_pQWidgetRobotJoint->setGeometry(QRect(10, 30, 361, 250));
        m_pVerticalLayoutRobotJoints = new QVBoxLayout(m_pQWidgetRobotJoint);
        m_pVerticalLayoutRobotJoints->setSpacing(16);
        m_pVerticalLayoutRobotJoints->setObjectName(QString::fromUtf8("verticalLayout"));
        m_pVerticalLayoutRobotJoints->setContentsMargins(0, 0, 0, 0);
        m_pHorizontalLayoutJoint_1 = new QHBoxLayout();
        m_pHorizontalLayoutJoint_1->setObjectName(QString::fromUtf8("horizontalLayout"));
        m_pLabelRobotJoint_1 = new QLabel(m_pQWidgetRobotJoint);
        m_pLabelRobotJoint_1->setObjectName(QString::fromUtf8("label"));

        m_pHorizontalLayoutJoint_1->addWidget(m_pLabelRobotJoint_1);

        m_pDoubleSpinBoxJoint_1 = new QDoubleSpinBox(m_pQWidgetRobotJoint);
        m_pDoubleSpinBoxJoint_1->setObjectName(QString::fromUtf8("doubleSpinBox"));

        m_pHorizontalLayoutJoint_1->addWidget(m_pDoubleSpinBoxJoint_1);

        m_pHorizontalSliderJoint_1 = new QSlider(m_pQWidgetRobotJoint);
        m_pHorizontalSliderJoint_1->setObjectName(QString::fromUtf8("horizontalSlider"));
        m_pHorizontalSliderJoint_1->setMinimum(-180);
        m_pHorizontalSliderJoint_1->setMaximum(180);
        m_pHorizontalSliderJoint_1->setOrientation(Qt::Horizontal);

        m_pHorizontalLayoutJoint_1->addWidget(m_pHorizontalSliderJoint_1);

        m_pVerticalLayoutRobotJoints->addLayout(m_pHorizontalLayoutJoint_1);

        m_pHorizontalLayoutJoint_2 = new QHBoxLayout();
        m_pHorizontalLayoutJoint_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        m_pLabelRobotJoint_2 = new QLabel(m_pQWidgetRobotJoint);
        m_pLabelRobotJoint_2->setObjectName(QString::fromUtf8("label_2"));

        m_pHorizontalLayoutJoint_2->addWidget(m_pLabelRobotJoint_2);

        m_pDoubleSpinBoxJoint_2 = new QDoubleSpinBox(m_pQWidgetRobotJoint);
        m_pDoubleSpinBoxJoint_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));

        m_pHorizontalLayoutJoint_2->addWidget(m_pDoubleSpinBoxJoint_2);

        m_pHorizontalSliderJoint_2 = new QSlider(m_pQWidgetRobotJoint);
        m_pHorizontalSliderJoint_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        m_pHorizontalSliderJoint_2->setOrientation(Qt::Horizontal);

        m_pHorizontalLayoutJoint_2->addWidget(m_pHorizontalSliderJoint_2);

        m_pVerticalLayoutRobotJoints->addLayout(m_pHorizontalLayoutJoint_2);

        m_pHorizontalLayoutJoint_3 = new QHBoxLayout();
        m_pHorizontalLayoutJoint_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_pLabelRobotJoint_3 = new QLabel(m_pQWidgetRobotJoint);
        m_pLabelRobotJoint_3->setObjectName(QString::fromUtf8("label_3"));

        m_pHorizontalLayoutJoint_3->addWidget(m_pLabelRobotJoint_3);

        m_pDoubleSpinBoxJoint_3 = new QDoubleSpinBox(m_pQWidgetRobotJoint);
        m_pDoubleSpinBoxJoint_3->setObjectName(QString::fromUtf8("doubleSpinBox_3"));

        m_pHorizontalLayoutJoint_3->addWidget(m_pDoubleSpinBoxJoint_3);

        m_pHorizontalSliderJoint_3 = new QSlider(m_pQWidgetRobotJoint);
        m_pHorizontalSliderJoint_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
        m_pHorizontalSliderJoint_3->setOrientation(Qt::Horizontal);

        m_pHorizontalLayoutJoint_3->addWidget(m_pHorizontalSliderJoint_3);

        m_pVerticalLayoutRobotJoints->addLayout(m_pHorizontalLayoutJoint_3);

        m_pHorizontalLayoutJoint_4 = new QHBoxLayout();
        m_pHorizontalLayoutJoint_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        m_pLabelRobotJoint_4 = new QLabel(m_pQWidgetRobotJoint);
        m_pLabelRobotJoint_4->setObjectName(QString::fromUtf8("label_4"));

        m_pHorizontalLayoutJoint_4->addWidget(m_pLabelRobotJoint_4);

        m_pDoubleSpinBoxJoint_4 = new QDoubleSpinBox(m_pQWidgetRobotJoint);
        m_pDoubleSpinBoxJoint_4->setObjectName(QString::fromUtf8("doubleSpinBox_4"));

        m_pHorizontalLayoutJoint_4->addWidget(m_pDoubleSpinBoxJoint_4);

        m_pHorizontalSliderJoint_4 = new QSlider(m_pQWidgetRobotJoint);
        m_pHorizontalSliderJoint_4->setObjectName(QString::fromUtf8("horizontalSlider_4"));
        m_pHorizontalSliderJoint_4->setOrientation(Qt::Horizontal);

        m_pHorizontalLayoutJoint_4->addWidget(m_pHorizontalSliderJoint_4);

        m_pVerticalLayoutRobotJoints->addLayout(m_pHorizontalLayoutJoint_4);

        m_pHorizontalLayoutJoint_5 = new QHBoxLayout();
        m_pHorizontalLayoutJoint_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        m_pLabelRobotJoint_5 = new QLabel(m_pQWidgetRobotJoint);
        m_pLabelRobotJoint_5->setObjectName(QString::fromUtf8("label_5"));

        m_pHorizontalLayoutJoint_5->addWidget(m_pLabelRobotJoint_5);

        m_pDoubleSpinBoxJoint_5 = new QDoubleSpinBox(m_pQWidgetRobotJoint);
        m_pDoubleSpinBoxJoint_5->setObjectName(QString::fromUtf8("doubleSpinBox_5"));

        m_pHorizontalLayoutJoint_5->addWidget(m_pDoubleSpinBoxJoint_5);

        m_pHorizontalSliderJoint_5 = new QSlider(m_pQWidgetRobotJoint);
        m_pHorizontalSliderJoint_5->setObjectName(QString::fromUtf8("horizontalSlider_5"));
        m_pHorizontalSliderJoint_5->setOrientation(Qt::Horizontal);

        m_pHorizontalLayoutJoint_5->addWidget(m_pHorizontalSliderJoint_5);

        m_pVerticalLayoutRobotJoints->addLayout(m_pHorizontalLayoutJoint_5);

        m_pHorizontalLayoutJoint_6 = new QHBoxLayout();
        m_pHorizontalLayoutJoint_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        m_pLabelRobotJoint_6 = new QLabel(m_pQWidgetRobotJoint);
        m_pLabelRobotJoint_6->setObjectName(QString::fromUtf8("label_6"));

        m_pHorizontalLayoutJoint_6->addWidget(m_pLabelRobotJoint_6);

        m_pDoubleSpinBoxJoint_6 = new QDoubleSpinBox(m_pQWidgetRobotJoint);
        m_pDoubleSpinBoxJoint_6->setObjectName(QString::fromUtf8("doubleSpinBox_6"));

        m_pHorizontalLayoutJoint_6->addWidget(m_pDoubleSpinBoxJoint_6);

        m_pHorizontalSliderJoint_6 = new QSlider(m_pQWidgetRobotJoint);
        m_pHorizontalSliderJoint_6->setObjectName(QString::fromUtf8("horizontalSlider_6"));
        m_pHorizontalSliderJoint_6->setOrientation(Qt::Horizontal);

        m_pHorizontalLayoutJoint_6->addWidget(m_pHorizontalSliderJoint_6);

        m_pVerticalLayoutRobotJoints->addLayout(m_pHorizontalLayoutJoint_6);

        m_pVerticalLayoutRobotController->addWidget(m_pGroupBoxRobotJoints);

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
        m_pLabelSettingJoints = new QLabel(m_pWidgetTargetJointsSettingCenter);
        m_pLabelSettingJoints->setObjectName(QString::fromUtf8("label_7"));

        m_pHorizontalLayoutTargetJointsLabel->addWidget(m_pLabelSettingJoints);

        m_pCheckBoxDegree = new QCheckBox(m_pWidgetTargetJointsSettingCenter);
        m_pCheckBoxDegree->setObjectName(QString::fromUtf8("checkBox"));

        m_pHorizontalLayoutTargetJointsLabel->addWidget(m_pCheckBoxDegree);

        m_pVerticalLayoutTargetJointsSettingCenter->addLayout(m_pHorizontalLayoutTargetJointsLabel);

        m_pTextEditTargetJoints = new QTextEdit(m_pWidgetTargetJointsSettingCenter);
        m_pTextEditTargetJoints->setObjectName(QString::fromUtf8("textEdit"));

        m_pVerticalLayoutTargetJointsSettingCenter->addWidget(m_pTextEditTargetJoints);

        m_pVerticalLayoutRobotController->addWidget(m_pGroupBoxTargetJointsSettingCenter);

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
        m_pLabelOtherModelTransformName = new QLabel(m_pWidgetOtherModelSetting);
        m_pLabelOtherModelTransformName->setObjectName(QString::fromUtf8("label_8"));

        m_pHorizontalLayoutOtherModel->addWidget(m_pLabelOtherModelTransformName);

        m_pCheckBoxTransformUnitOfLength = new QCheckBox(m_pWidgetOtherModelSetting);
        m_pCheckBoxTransformUnitOfLength->setObjectName(QString::fromUtf8("checkBox_3"));

        m_pHorizontalLayoutOtherModel->addWidget(m_pCheckBoxTransformUnitOfLength);

        m_pCheckBoxOtherModelDegree = new QCheckBox(m_pWidgetOtherModelSetting);
        m_pCheckBoxOtherModelDegree->setObjectName(QString::fromUtf8("checkBox_2"));

        m_pHorizontalLayoutOtherModel->addWidget(m_pCheckBoxOtherModelDegree);

        m_pVerticalLayoutOtherModel->addLayout(m_pHorizontalLayoutOtherModel);

        m_pTextEditOtherModelTransform = new QTextEdit(m_pWidgetOtherModelSetting);
        m_pTextEditOtherModelTransform->setObjectName(QString::fromUtf8("textEdit_2"));

        m_pVerticalLayoutOtherModel->addWidget(m_pTextEditOtherModelTransform);

        m_pVerticalLayoutRobotController->addWidget(m_pGroupBoxOtherModelSetting);

        m_pVerticalLayoutRobotController->setStretch(0, 2);
        m_pVerticalLayoutRobotController->setStretch(1, 1);
        m_pVerticalLayoutRobotController->setStretch(2, 1);

        m_pMainGridLayout->addLayout(m_pVerticalLayoutRobotController, 0, 1, 1, 1);

        m_pMainGridLayout->setColumnStretch(0, 2);
        m_pMainGridLayout->setColumnStretch(1, 1);

        retranslateUi(RobotSimulationPlatform);

        QMetaObject::connectSlotsByName(RobotSimulationPlatform);
    } // setupUi

    void retranslateUi(QWidget *RobotSimulationPlatform)
    {
        RobotSimulationPlatform->setWindowTitle(QApplication::translate("RobotSimulationPlatform", "RobotSimulationPlatform", nullptr));
        m_pRobotGroup->setTitle(QString());
        m_pPushButtonGroup->setTitle(QApplication::translate("RobotSimulationPlatform", "GroupBox", nullptr));
        pushButton->setText(QApplication::translate("RobotSimulationPlatform", "PushButton", nullptr));
        pushButton_2->setText(QApplication::translate("RobotSimulationPlatform", "PushButton", nullptr));
        m_pGroupBoxRobotJoints->setTitle(QString());
        m_pLabelRobotJoint_1->setText(QApplication::translate("RobotSimulationPlatform", "Joint_1", nullptr));
        m_pLabelRobotJoint_2->setText(QApplication::translate("RobotSimulationPlatform", "Joint_2", nullptr));
        m_pLabelRobotJoint_3->setText(QApplication::translate("RobotSimulationPlatform", "Joint_3", nullptr));
        m_pLabelRobotJoint_4->setText(QApplication::translate("RobotSimulationPlatform", "Joint_4", nullptr));
        m_pLabelRobotJoint_5->setText(QApplication::translate("RobotSimulationPlatform", "Joint_5", nullptr));
        m_pLabelRobotJoint_6->setText(QApplication::translate("RobotSimulationPlatform", "Joint_6", nullptr));
        m_pGroupBoxTargetJointsSettingCenter->setTitle(QString());
        m_pLabelSettingJoints->setText(QApplication::translate("RobotSimulationPlatform", "\346\234\253\347\253\257\345\205\263\350\212\202\345\200\274", nullptr));
        m_pCheckBoxDegree->setText(QApplication::translate("RobotSimulationPlatform", "\345\274\247\345\272\246", nullptr));
        m_pGroupBoxOtherModelSetting->setTitle(QString());
        m_pLabelOtherModelTransformName->setText(QApplication::translate("RobotSimulationPlatform", "\345\244\264\351\203\250\345\210\260\346\234\272\345\231\250\344\272\272\345\235\220\346\240\207\350\275\254\346\215\242\347\237\251\351\230\265\357\274\232", nullptr));
        m_pCheckBoxTransformUnitOfLength->setText(QApplication::translate("RobotSimulationPlatform", "\347\261\263", nullptr));
        m_pCheckBoxOtherModelDegree->setText(QApplication::translate("RobotSimulationPlatform", "\345\274\247\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RobotSimulationPlatform: public Ui_RobotSimulationPlatform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOT_SIMULATION_PLATFORM_H
