//
// Created by wei on 2022/6/6.
//

#ifndef NEWTRAVEL_MY_SLIDER_H
#define NEWTRAVEL_MY_SLIDER_H

#include <QSlider>
#include <iostream>

class my_slider  :  public  QSlider
{
Q_OBJECT
public:
    my_slider(QWidget *parent = nullptr);
    ~my_slider();

public:
    void Initial(int iIndex);
    int  GetCurrent();

};

#endif // NEWTRAVEL_MY_SLIDER_H
