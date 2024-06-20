#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSet>
#include <QWebSocket>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <set>
#include <iostream>
#include <QDateTime>
#include <QCloseEvent>
#include <map>
#include <vector>

class ChatWidget : public QWidget
{
    Q_OBJECT
private:
    struct Message {
        int senderId;
        QString senderName;
        QString text;
        QDateTime timestamp;
        QString status;
    };

    struct user {
        int Id;
        QString Name;
        QString sessionId;
        int currentChatId = -1;
    };

    QTextEdit *chatDisplay;
    QVBoxLayout *chatListLayout;
    QWebSocket *webSocket;
    std::map<int, std::vector<Message>> messageMap;
    QString htmlContent;
    user my;
    std::set<int> searchFriends;

public:
    ChatWidget();
    void updateChatButtonStyle(int senderId, QString net_status);

signals:
    void loginSuccess();
    void responseReceived(const QString &responseBody);

public slots:
    void onTextMessageReceived(const QString &message);
    void receiveResponse(const QString &responseBody);
    void send_message(QString& message);

private slots:
    void searchRequest(QString body);
    void searchResult(const QString &message);
    void sendWebSocketRequest();
    void processResponse(const QString &responseBody);
    QWidget* createChatButton(int senderId, const QString &chatName, const QString &status);
    void addChatButtons();
    void addNewChatButton(int senderId, const QString &chatName, const QString &status);
    void displayMessages(int senderId);
    void printMessageMap(const std::multimap<int, QString> &messageMap);
};

#endif // CHATWIDGET_H
