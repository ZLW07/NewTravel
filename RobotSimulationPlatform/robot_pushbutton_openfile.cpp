//
// Created by wei on 2023/1/18.
//
#include "robot_pushbutton_openfile.h"

OpenFile::OpenFile(FileDialog *pFileDialog,QWidget *parent) : QPushButton(parent)
{
    m_pQFileDialog = pFileDialog;
}

OpenFile::~OpenFile() {}
