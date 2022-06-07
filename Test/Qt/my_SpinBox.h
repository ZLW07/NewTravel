//
// Created by wei on 2022/6/6.
//

#ifndef NEWTRAVEL_MY_SPINBOX_H
#define NEWTRAVEL_MY_SPINBOX_H

#include <QTextEdit>
#include <QSpinBox>
#include "my_slider.h"

class my_SpinBox :  public  QSpinBox
{
Q_OBJECT
public:
    my_SpinBox(QWidget *parent = nullptr);
    ~my_SpinBox();

public:
    void Initial(int iIndex);
    void SetValue(int iValue);

private:
    my_slider *m_pSlider;
};

#endif // NEWTRAVEL_MY_SPINBOX_H
