#include "customlineEdit.h"

CustomLineEdit::CustomLineEdit(const QString& placeholder, QIcon icon, InputType type, bool useValidator)
{
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    QPushButton* button = new QPushButton();
    button->setIcon(icon);
    button->setStyleSheet("QPushButton{border:1px solid lightBlue; background-color:lightBlue;} ");
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    button->setFixedSize(QSize(30, 30));
    hLayout->addWidget(button);

    switch(type)
    {
    case InputType::EMAIL:
        button->setToolTip("Email must contain \"@\" character.");
        break;
    case InputType::PASSWORD:
        button->setToolTip("The Password must contain an uppercase letter, number, and symbol, and must have at least 8 characters.");
        break;
    default:
        break;
    }
    lineEdit = new QLineEdit();

    if (type == InputType::PASSWORD)
        lineEdit->setEchoMode(QLineEdit::Password);

    lineEdit->setFixedHeight(30);
    lineEdit->setPlaceholderText(placeholder);
    hLayout->addWidget(lineEdit);
    hLayout->setSpacing(0);
}

QLineEdit* CustomLineEdit::getLineEdit() const {
    return lineEdit;
}


