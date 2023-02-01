//
// Created by wei on 2023/1/29.
//

#ifndef NEWTRAVEL_ROBOT_TARGET_JOINT_H
#define NEWTRAVEL_ROBOT_TARGET_JOINT_H
#include <QtWidgets/QTextEdit>

class InputText : public QTextEdit
{
Q_OBJECT
public:
    InputText(QWidget *parent = nullptr);
    ~InputText() override;

signals :
    void SetValue(const QString &oFilePath);
public  Q_SLOTS:
    void SetValue();
public:
    void emitValue();
};

#endif // NEWTRAVEL_ROBOT_TARGET_JOINT_H
