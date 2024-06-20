#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QString>
#include <QStackedWidget>

#include "customlineEdit.h"


class LogWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogWidget(QStackedWidget *stack, QWidget *parent = nullptr);
    ~LogWidget();

signals:
    void signUpRequested();
    void loginSuccess();
    void responseReceived(const QString &responseBody);

public slots:
    void handleLogin();

private:
    void sendLoginRequest(const QString &email, const QString &password);
    void sendLoginRequestGRPC(const QString &email, const QString &password);

    QStackedWidget *stackedWidget;
    CustomLineEdit *emailLineEdit;
    CustomLineEdit *passwordLineEdit;
    QString responseBody;
};

#endif // LOGWIDGET_H
























































































































/*#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QLineEdit>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QProcess>
#include "separator.h"
#include "customlineEdit.h"
#include "chatwidget.h"
#include <grpcpp/grpcpp.h>
#include <grpc++/grpc++.h>

#include <grpcpp/create_channel.h> // For grpc::CreateChannel
#include <grpcpp/security/credentials.h> // For grpc::InsecureChannelCredentials

#include "../../../proto/chat.grpc.pb.h"



class LogWidget : public QWidget
{
    Q_OBJECT
public:
    LogWidget(QStackedWidget *stack)
        : QWidget(), stackedWidget(stack)
    {
        // Create a gRPC server
        setObjectName("LogWidget");
        setFixedSize(QSize(500, 300));
        QVBoxLayout* vLayout = new QVBoxLayout(this);

        QLabel* header = new QLabel("Log in");
        header->setAlignment(Qt::AlignHCenter);
        QFont ft = header->font();
        ft.setPointSize(16);
        header->setFont(ft);
        vLayout->addWidget(header);

        vLayout->addWidget(new Separator());

        emailLineEdit = new CustomLineEdit("Email", QIcon("/home/gevor/Desktop/messenger/src/MESSENGER/icons/email.png"), InputType::EMAIL, false);
        vLayout->addWidget(emailLineEdit);

        passwordLineEdit = new CustomLineEdit("Password", QIcon("/home/gevor/Desktop/messenger/src/MESSENGER/icons/lock.png"), InputType::PASSWORD, false);
        vLayout->addWidget(passwordLineEdit);

        vLayout->addWidget(new Separator());

        QPushButton* log_in = new QPushButton("Log In");
        log_in->setStyleSheet("QPushButton{background-color:#afc6db; border:1px solid #5e788f; height:30px; border-radius: 5px; } QPushButton:pressed {background-color:#8ea8bf;}");
        vLayout->addWidget(log_in);

        connect(log_in, &QPushButton::clicked, this, &LogWidget::handleLogin);

        QPushButton* reg_and_log = new QPushButton("Sign up");
        reg_and_log->setStyleSheet("QPushButton{background-color:#afc6db; border:1px solid #5e788f; height:30px; border-radius: 5px; } QPushButton:pressed {background-color:#8ea8bf;} ");
        vLayout->addWidget(reg_and_log);

        connect(reg_and_log, &QPushButton::clicked, this, &LogWidget::signUpRequested);

        setStyleSheet("QWidget#LogWidget { border: 2px solid red; border-radius: 10px; background-color: red; }");
    }

    ~LogWidget() {}

signals:
    void signUpRequested();
    void loginSuccess();
    void responseReceived(const QString &responseBody);


public slots:
    void handleLogin() {
        QString email = emailLineEdit->getLineEdit()->text();
        QString password = passwordLineEdit->getLineEdit()->text();
        qDebug() << "Email: " << email;
        qDebug() << "Password: " << password;

        //sendLoginRequestGRPC(email, password);
        sendLoginRequest(email, password);
    }

private:
    QStackedWidget *stackedWidget;
    CustomLineEdit *emailLineEdit;
    CustomLineEdit *usernameLineEdit;
    CustomLineEdit *passwordLineEdit;
    QString responseBody;

    /*void sendLoginRequestGRPC(const QString& arg1, const QString& password) {
        // gRPC client setup
        auto channel = grpc::CreateChannel("localhost:8080", grpc::InsecureChannelCredentials());
    }
        // Assuming chat::ChatService::Stub is defined and has a constructor that accepts grpc::Channel arguments
        //std::unique_ptr<chat::ChatService::Stub> stub = chat::ChatService::NewStub(channel);

        // Now you can use 'stub' to make gRPC calls
    //}
        // Prepare request
        /*chat::loginMessage request;
        request.set_username(email.toStdString());
        request.set_password(password.toStdString());

        // Send request and handle response
        grpc::ClientContext context;
        chat::loginResponse response;
        grpc::Status status = stub->log_in(&context, request, &response);

        if (status.ok()) {
            qDebug() << "Login successful";
            responseBody = QString::fromStdString(response.session_id()); // Example response data
            qDebug() << "responseBody: " << responseBody;
            emit responseReceived(responseBody);
            emit loginSuccess();
        } else {
            qDebug() << "Login failed: " << status.error_code() << ": " << status.error_message().c_str();
        }
    //}


    void sendLoginRequest(const QString& email, const QString& password) {
        QNetworkAccessManager* manager = new QNetworkAccessManager();

        QJsonObject json;
        json["email"] = email;
        json["password"] = password;
        QJsonDocument doc(json);
        QByteArray data = doc.toJson();

        QNetworkRequest request(QUrl("http://localhost:8080/login"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

        QNetworkReply* reply = manager->post(request, data);

        QObject::connect(reply, &QNetworkReply::finished, [=]() {
            if (reply->error() == QNetworkReply::NoError) {
                qDebug() << "Login successful";
                responseBody = reply->readAll();

                emit responseReceived(responseBody);
                emit loginSuccess();
            } else {
                qDebug() << "Error:" << reply->errorString();
            }

            reply->deleteLater();
            manager->deleteLater();
        });
    }
};

#endif
*/
