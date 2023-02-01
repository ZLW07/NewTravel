//
// Created by wei on 2023/1/31.
//

#include "robot_pushbutton_send_message.h"

SendButton::SendButton(QWidget*parent):QPushButton(parent){}

SendButton::~SendButton() {}

void SendButton::mousePressEvent(QMouseEvent *event)
{
    emit SendMessage();
}
