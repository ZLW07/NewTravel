//
// Created by wei on 2023/1/29.
//

#include "robot_target_joint.h"
InputText::InputText(QWidget *parent) : QTextEdit(parent) {}

InputText::~InputText() = default;

void InputText::emitValue()
{
    QString sValue = toPlainText();
    emit SetValue(sValue);
}

void InputText::SetValue()
{
    emitValue();
}
