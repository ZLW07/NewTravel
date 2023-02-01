//
// Created by wei on 2023/1/18.
//

#ifndef NEWTRAVEL_ROBOT_PUSHBUTTON_OPENFILE_H
#define NEWTRAVEL_ROBOT_PUSHBUTTON_OPENFILE_H

#include <QtWidgets/QPushButton>
#include "robot_qfile_dialog.h"
#include <iostream>
class OpenFile : public QPushButton
{
Q_OBJECT
public:
    OpenFile(FileDialog *pFileDialog,QWidget *parent = nullptr);
    ~OpenFile();

    void mousePressEvent(QMouseEvent *event) override
    {
        openfile();
    }
    void openfile()
    {
        QString strFileName = FileDialog::getOpenFileName(this, "Open File", "",
                                                           tr("XML(*.xml)"), nullptr, QFileDialog::DontResolveSymlinks);
        strFileName = QDir::toNativeSeparators(strFileName);
        if (!strFileName.isEmpty())
        {
            m_pQFileDialog->SetPath(strFileName);
            std::cout << "strFileName : "  << strFileName.toStdString() <<std::endl;
        }
    }

private:
    FileDialog *m_pQFileDialog;
};


#endif // NEWTRAVEL_ROBOT_PUSHBUTTON_OPENFILE_H
