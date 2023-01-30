//
// Created by wei on 2023/1/29.
//

#ifndef NEWTRAVEL_ROBOT_QTEXT_H
#define NEWTRAVEL_ROBOT_QTEXT_H
#include <QtWidgets/QTextEdit>
#include <QKeyEvent>

class InputText : public QTextEdit
{
Q_OBJECT
public:
    InputText(QWidget *parent = nullptr);
    ~InputText() override;

signals :
    void SetValue(const QString &oFilePath);

public:
    void emitValue();
};

#endif // NEWTRAVEL_ROBOT_QTEXT_H
