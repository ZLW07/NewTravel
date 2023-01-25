//
// Created by wei on 2023/1/22.
//

#ifndef NEWTRAVEL_ROBOT_QFILE_DIALOG_H
#define NEWTRAVEL_ROBOT_QFILE_DIALOG_H

#include <QtWidgets/QFileDialog>

class FileDialog : public QFileDialog
{
    Q_OBJECT
public:
    explicit FileDialog(QWidget *parent = nullptr);
    ~FileDialog() override;
public  Q_SLOTS:
    void SetPath(QString sPath);
signals :
    void fileSelected(QString oFilePath);

public:
    void emitSelectFile(QString oFilePath);

};


#endif // NEWTRAVEL_ROBOT_QFILE_DIALOG_H
