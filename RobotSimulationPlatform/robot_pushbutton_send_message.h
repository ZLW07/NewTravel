//
// Created by wei on 2023/1/31.
//

#ifndef NEWTRAVEL_ROBOT_PUSHBUTTON_SEND_MESSAGE_H
#define NEWTRAVEL_ROBOT_PUSHBUTTON_SEND_MESSAGE_H

#include "robot_target_joint.h"
#include <QtWidgets/QPushButton>

class SendButton : public QPushButton
{
    Q_OBJECT
public:
    SendButton(QWidget *parent = nullptr);
    ~SendButton();
    void mousePressEvent(QMouseEvent *event) override;
signals :
    void SendMessage();
};
#endif // NEWTRAVEL_ROBOT_PUSHBUTTON_SEND_MESSAGE_H
