#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QIcon>
#include <QValidator>
#include "InputType.h"
#include "validatorfactory.h"
#include <iostream>

class CustomLineEdit : public QWidget
{
    Q_OBJECT
public:
    CustomLineEdit(const QString& placeholder, QIcon icon, InputType type, bool useValidator = true);
    QLineEdit* getLineEdit() const;

private:
    QLineEdit* lineEdit;
};

#endif // CUSTOMLINEEDIT_H
