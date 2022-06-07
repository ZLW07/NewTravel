//
// Created by wei on 2022/6/6.
//

#include "my_SpinBox.h"

my_SpinBox::my_SpinBox(QWidget *parent) : QSpinBox(parent)
{
}

my_SpinBox::~my_SpinBox() noexcept {

}

void my_SpinBox::Initial(int iIndex)
{
    resize(50, 30);
    move(800, iIndex * 40);
    setMinimum(-180);
    setMaximum(180);
    setSingleStep(1);
    show();
}



