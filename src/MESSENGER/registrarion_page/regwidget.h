#ifndef REGWIDGET_H
#define REGWIDGET_H

#include <QString>
#include <QStackedWidget>
#include "customlineEdit.h"

#include <QProcess>

class RegWidget : public QWidget
{
    Q_OBJECT
public:
    RegWidget(QStackedWidget *stack);
    ~RegWidget();

signals:
    void registrationSuccess();

public slots:
    void handle_reg_log();
    void openChatWindow();
    void showSuccessDialog();

private:
    QStackedWidget *stackedWidget;
    CustomLineEdit *emailLineEdit;
    CustomLineEdit *usernameLineEdit;
    CustomLineEdit *passwordLineEdit;

    void sendRegistrationRequest(const QString& email, const QString& password);
};

#endif // REGWIDGET_H
