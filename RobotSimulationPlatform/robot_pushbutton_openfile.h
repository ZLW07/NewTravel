//
// Created by wei on 2023/1/18.
//

#ifndef NEWTRAVEL_ROBOT_PUSHBUTTON_OPENFILE_H
#define NEWTRAVEL_ROBOT_PUSHBUTTON_OPENFILE_H

#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <iostream>
class OpenFile : public QPushButton
{
Q_OBJECT
public:
    OpenFile(QWidget *parent = nullptr);
    ~OpenFile();

    void mousePressEvent(QMouseEvent *event) override
    {
        openfile();

    }
    void openfile()
    {
        QString strFileName = QFileDialog::getOpenFileName(this, "Open File", "",
                                                           tr("STL(*.STL)"), 0, QFileDialog::DontResolveSymlinks);
        strFileName = QDir::toNativeSeparators(strFileName);
        std::cout << "strFileName : "  << strFileName.toStdString() <<std::endl;
    }
};


#endif // NEWTRAVEL_ROBOT_PUSHBUTTON_OPENFILE_H
