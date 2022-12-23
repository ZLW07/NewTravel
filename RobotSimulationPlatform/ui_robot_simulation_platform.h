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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RobotSimulationPlatform
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_9;
    QOpenGLWidget *openGLWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_2;
    QSlider *horizontalSlider_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_3;
    QSlider *horizontalSlider_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_4;
    QSlider *horizontalSlider_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_5;
    QSlider *horizontalSlider_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_6;
    QSlider *horizontalSlider_6;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QCheckBox *checkBox;
    QTextBrowser *textBrowser;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QTextBrowser *textBrowser_2;

    void setupUi(QWidget *RobotSimulationPlatform)
    {
        if (RobotSimulationPlatform->objectName().isEmpty())
            RobotSimulationPlatform->setObjectName(QString::fromUtf8("RobotSimulationPlatform"));
        RobotSimulationPlatform->resize(1083, 713);
        gridLayout = new QGridLayout(RobotSimulationPlatform);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        openGLWidget = new QOpenGLWidget(RobotSimulationPlatform);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setEnabled(true);
        openGLWidget->setMinimumSize(QSize(700, 600));

        horizontalLayout_9->addWidget(openGLWidget);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(21);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, -1, -1, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(RobotSimulationPlatform);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        doubleSpinBox = new QDoubleSpinBox(RobotSimulationPlatform);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));

        horizontalLayout->addWidget(doubleSpinBox);

        horizontalSlider = new QSlider(RobotSimulationPlatform);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(-180);
        horizontalSlider->setMaximum(180);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(RobotSimulationPlatform);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        doubleSpinBox_2 = new QDoubleSpinBox(RobotSimulationPlatform);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));

        horizontalLayout_2->addWidget(doubleSpinBox_2);

        horizontalSlider_2 = new QSlider(RobotSimulationPlatform);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(RobotSimulationPlatform);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        doubleSpinBox_3 = new QDoubleSpinBox(RobotSimulationPlatform);
        doubleSpinBox_3->setObjectName(QString::fromUtf8("doubleSpinBox_3"));

        horizontalLayout_3->addWidget(doubleSpinBox_3);

        horizontalSlider_3 = new QSlider(RobotSimulationPlatform);
        horizontalSlider_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(RobotSimulationPlatform);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        doubleSpinBox_4 = new QDoubleSpinBox(RobotSimulationPlatform);
        doubleSpinBox_4->setObjectName(QString::fromUtf8("doubleSpinBox_4"));

        horizontalLayout_4->addWidget(doubleSpinBox_4);

        horizontalSlider_4 = new QSlider(RobotSimulationPlatform);
        horizontalSlider_4->setObjectName(QString::fromUtf8("horizontalSlider_4"));
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSlider_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(RobotSimulationPlatform);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        doubleSpinBox_5 = new QDoubleSpinBox(RobotSimulationPlatform);
        doubleSpinBox_5->setObjectName(QString::fromUtf8("doubleSpinBox_5"));

        horizontalLayout_5->addWidget(doubleSpinBox_5);

        horizontalSlider_5 = new QSlider(RobotSimulationPlatform);
        horizontalSlider_5->setObjectName(QString::fromUtf8("horizontalSlider_5"));
        horizontalSlider_5->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(horizontalSlider_5);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(RobotSimulationPlatform);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        doubleSpinBox_6 = new QDoubleSpinBox(RobotSimulationPlatform);
        doubleSpinBox_6->setObjectName(QString::fromUtf8("doubleSpinBox_6"));

        horizontalLayout_6->addWidget(doubleSpinBox_6);

        horizontalSlider_6 = new QSlider(RobotSimulationPlatform);
        horizontalSlider_6->setObjectName(QString::fromUtf8("horizontalSlider_6"));
        horizontalSlider_6->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(horizontalSlider_6);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_7 = new QLabel(RobotSimulationPlatform);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        checkBox = new QCheckBox(RobotSimulationPlatform);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_7->addWidget(checkBox);


        verticalLayout_2->addLayout(horizontalLayout_7);

        textBrowser = new QTextBrowser(RobotSimulationPlatform);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_2->addWidget(textBrowser);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_8 = new QLabel(RobotSimulationPlatform);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_8->addWidget(label_8);

        checkBox_3 = new QCheckBox(RobotSimulationPlatform);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout_8->addWidget(checkBox_3);

        checkBox_2 = new QCheckBox(RobotSimulationPlatform);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout_8->addWidget(checkBox_2);


        verticalLayout_3->addLayout(horizontalLayout_8);

        textBrowser_2 = new QTextBrowser(RobotSimulationPlatform);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));

        verticalLayout_3->addWidget(textBrowser_2);


        verticalLayout_4->addLayout(verticalLayout_3);


        horizontalLayout_9->addLayout(verticalLayout_4);


        gridLayout->addLayout(horizontalLayout_9, 0, 0, 1, 1);


        retranslateUi(RobotSimulationPlatform);

        QMetaObject::connectSlotsByName(RobotSimulationPlatform);
    } // setupUi

    void retranslateUi(QWidget *RobotSimulationPlatform)
    {
        RobotSimulationPlatform->setWindowTitle(QApplication::translate("RobotSimulationPlatform", "RobotSimulationPlatform", nullptr));
        label->setText(QApplication::translate("RobotSimulationPlatform", "Joint_1", nullptr));
        label_2->setText(QApplication::translate("RobotSimulationPlatform", "Joint_2", nullptr));
        label_3->setText(QApplication::translate("RobotSimulationPlatform", "Joint_3", nullptr));
        label_4->setText(QApplication::translate("RobotSimulationPlatform", "Joint_4", nullptr));
        label_5->setText(QApplication::translate("RobotSimulationPlatform", "Joint_5", nullptr));
        label_6->setText(QApplication::translate("RobotSimulationPlatform", "Joint_6", nullptr));
        label_7->setText(QApplication::translate("RobotSimulationPlatform", "\346\234\253\347\253\257\345\205\263\350\212\202\345\200\274", nullptr));
        checkBox->setText(QApplication::translate("RobotSimulationPlatform", "\345\274\247\345\272\246", nullptr));
        label_8->setText(QApplication::translate("RobotSimulationPlatform", "\345\244\264\351\203\250\345\210\260\346\234\272\345\231\250\344\272\272\345\235\220\346\240\207\350\275\254\346\215\242\347\237\251\351\230\265\357\274\232", nullptr));
        checkBox_3->setText(QApplication::translate("RobotSimulationPlatform", "\346\257\253\347\261\263", nullptr));
        checkBox_2->setText(QApplication::translate("RobotSimulationPlatform", "\345\274\247\345\272\246", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RobotSimulationPlatform: public Ui_RobotSimulationPlatform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOT_SIMULATION_PLATFORM_H
