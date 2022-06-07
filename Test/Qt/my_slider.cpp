//
// Created by wei on 2022/6/6.
//

#include "my_slider.h"

my_slider::my_slider(QWidget *parent) : QSlider(parent)
{

}

my_slider::~my_slider() noexcept {}

void my_slider::Initial(int iIndex)
{
    setMaximum(180);
    setMinimum(-180);
   setOrientation(Qt::Horizontal);
   resize(260, 30);
   move(860, iIndex * 40);
   setSingleStep(5);
   show();
}

int my_slider::GetCurrent()
{
    int iValue = value();
    std::cout << iValue << std::endl;
    return iValue;
}


