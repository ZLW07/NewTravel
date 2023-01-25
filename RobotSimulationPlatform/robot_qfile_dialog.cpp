//
// Created by wei on 2023/1/22.
//

#include "robot_qfile_dialog.h"

FileDialog::FileDialog(QWidget *parent):QFileDialog(parent)
{
//    connect(this, SIGNAL(fileSelected(QString)), this, SLOT(SetPath(QString)));
}


FileDialog::~FileDialog()
{
}
void FileDialog::emitSelectFile(QString oFilePath)
{

    {

    }
}
void FileDialog::SetPath(QString sPath)
{
    emit fileSelected(sPath);
}
