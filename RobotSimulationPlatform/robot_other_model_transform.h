//
// Created by wei on 2023/1/31.
//

#ifndef NEWTRAVEL_ROBOT_OTHER_MODEL_TRANSFORM_H
#define NEWTRAVEL_ROBOT_OTHER_MODEL_TRANSFORM_H

#include <QtWidgets/QTextEdit>
#include <QMatrix4x4>

class OtherModelTrans : public QTextEdit
{
Q_OBJECT
public:
    OtherModelTrans(QWidget *parent = nullptr);
    ~OtherModelTrans() override;

signals :
    void SetValue(QMatrix4x4 oFilePath);
public  Q_SLOTS:
    void SetValue();
public:
    void emitValue();
};

#endif // NEWTRAVEL_ROBOT_OTHER_MODEL_TRANSFORM_H
