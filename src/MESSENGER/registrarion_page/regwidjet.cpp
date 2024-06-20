#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QLineEdit>
#include <QMessageBox>
#include "separator.h"
#include "customlineEdit.h"
#include "chatwidget.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QProcess>

#include "regwidget.h"

RegWidget::RegWidget(QStackedWidget *stack)
    : QWidget(), stackedWidget(stack)
{
    setObjectName("RegWidget");
    setFixedSize(QSize(500, 300));
    QVBoxLayout* vLayout = new QVBoxLayout(this);

    QLabel* header = new QLabel("Register");
    header->setAlignment(Qt::AlignHCenter);
    QFont ft = header->font();
    ft.setPointSize(16);
    header->setFont(ft);
    vLayout->addWidget(header);

    vLayout->addWidget(new Separator());

    emailLineEdit = new CustomLineEdit("Email", QIcon("/home/gevor/Desktop/messenger/src/MESSENGER/icons/email.png"), InputType::EMAIL);
    vLayout->addWidget(emailLineEdit);

    passwordLineEdit = new CustomLineEdit("Password", QIcon("/home/gevor/Desktop/messenger/src/MESSENGER/icons/lock.png"), InputType::PASSWORD);
    vLayout->addWidget(passwordLineEdit);

    vLayout->addWidget(new Separator());

    QPushButton* reg_and_log = new QPushButton("Sign up");
    reg_and_log->setStyleSheet("QPushButton{background-color:#afc6db; border:1px solid #5e788f; height:30px; border-radius: 5px; } QPushButton:pressed {background-color:#8ea8bf;} ");
    vLayout->addWidget(reg_and_log);

    connect(reg_and_log, &QPushButton::clicked, this, &RegWidget::handle_reg_log);
    connect(this, &RegWidget::registrationSuccess, this, &RegWidget::showSuccessDialog);

    setStyleSheet("QWidget#RegWidget { border: 2px solid red; border-radius: 10px; background-color: red; }");
}

RegWidget::~RegWidget() {}

void RegWidget::handle_reg_log() {
    QString email = emailLineEdit->getLineEdit()->text();
    QString password = passwordLineEdit->getLineEdit()->text();
    qDebug() << "Email: " << email;
    qDebug() << "Password: " << password;

    sendRegistrationRequest(email, password);
}

void RegWidget::openChatWindow() {
    ChatWidget *chatWidget = new ChatWidget;

    stackedWidget->addWidget(chatWidget);
    stackedWidget->setCurrentWidget(chatWidget);
}

void RegWidget::showSuccessDialog() {
    QMessageBox::information(this, "Registration Successful", "You have successfully registered!");

    stackedWidget->setCurrentIndex(0);
}

void RegWidget::sendRegistrationRequest(const QString& email, const QString& password) {
    QNetworkAccessManager* manager = new QNetworkAccessManager();

    QJsonObject json;
    json["email"] = email;
    json["password"] = password;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QNetworkRequest request(QUrl("http://localhost:8080/registration"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = manager->post(request, data);

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Registration successful";
            qDebug() << "Response:" << reply->readAll();

            emit registrationSuccess();
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
        manager->deleteLater();
    });
}
