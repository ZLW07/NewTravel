//
// Created by wei on 2023/1/29.
//

#include "robot_qtext.h"
InputText::InputText(QWidget *parent) : QTextEdit(parent) {}


InputText::~InputText() = default;;

void InputText::emitValue()
{
    QString sValue = toPlainText();
    printf("00000000000000");
    emit SetValue(sValue);
}


