#include "chatwidget.h"

ChatWidget::ChatWidget()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *hLayout = new QHBoxLayout();

    chatListLayout = new QVBoxLayout();
    chatListLayout->setContentsMargins(5, 5, 5, 5);
    chatListLayout->setSpacing(10);
    chatListLayout->setObjectName("ChatListLayout");
    chatListLayout->setAlignment(Qt::AlignTop);

    // Horizontal layout ------Search--------------------
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLineEdit *searchContacts = new QLineEdit();
    searchContacts->setPlaceholderText("Search contacts...");

    QPushButton *searchButton = new QPushButton("Search");
    searchLayout->addWidget(searchContacts);
    searchLayout->addWidget(searchButton);
    chatListLayout->addLayout(searchLayout);

    connect(searchButton, &QPushButton::clicked, this, [this, searchContacts](){
        QString body = searchContacts->text();
        searchRequest(body);
    });

    QVBoxLayout *currentChatLayout = new QVBoxLayout();
    currentChatLayout->setContentsMargins(5, 5, 5, 5);
    currentChatLayout->setSpacing(10);
    currentChatLayout->setObjectName("CurrentChatLayout");

    chatDisplay = new QTextEdit();
    chatDisplay->setReadOnly(true);
    currentChatLayout->addWidget(chatDisplay);

    QLineEdit *messageInput = new QLineEdit();
    currentChatLayout->addWidget(messageInput);

    QPushButton *sendButton = new QPushButton("Send");
    currentChatLayout->addWidget(sendButton);

    connect(sendButton, &QPushButton::clicked, this, [this, messageInput]() {
        QString message = "    " + messageInput->text() + "    ";
        if (!message.isEmpty()) {
            QString formatted_message = QString("<div style='text-align: left;'><span style='display: inline-block; padding: 5px; margin: 5px; color: black; font-weight: bold; font-size: 20px;'>Me: %1</span></div>").arg(message);
            htmlContent += formatted_message;
            chatDisplay->setHtml(htmlContent);
            messageInput->clear();
            send_message(message);
        }
    });
    hLayout->addLayout(chatListLayout, 1);
    hLayout->addLayout(currentChatLayout, 3);

    mainLayout->addLayout(hLayout);
    setLayout(mainLayout);

    setStyleSheet("QWidget#ChatListLayout { background-color: lightblue; border: 1px solid blue; }"
                  "QWidget#CurrentChatLayout { background-color: lightgray; border: 1px solid gray; }");

    connect(this, &ChatWidget::loginSuccess, this, &ChatWidget::sendWebSocketRequest);
}

void ChatWidget::updateChatButtonStyle(int senderId, QString net_status) {
    for (int i = 1; i < chatListLayout->count(); ++i) {
        QWidget *widget = chatListLayout->itemAt(i)->widget();
        if (!widget) {
            qDebug() << "Widget at index" << i << "is null";
            continue;
        }

        QVBoxLayout *chatLayout = qobject_cast<QVBoxLayout *>(widget->layout());
        if (!chatLayout) {
            qDebug() << "Chat layout at index" << i << "is not a QVBoxLayout";
            continue;
        }

        if (chatLayout->count() < 1) {
            qDebug() << "Chat layout at index" << i << "does not have enough items";
            continue;
        }

        QHBoxLayout *buttonLayout = qobject_cast<QHBoxLayout *>(chatLayout->itemAt(0)->layout());
        if (!buttonLayout) {
            qDebug() << "Button layout at index" << i << "is not a QHBoxLayout";
            continue;
        }

        if (buttonLayout->count() < 2) {
            qDebug() << "Button layout at index" << i << "does not have enough items";
            continue;
        }

        QLabel *statusCircle = qobject_cast<QLabel *>(buttonLayout->itemAt(0)->widget());
        if (!statusCircle) {
            qDebug() << "Status circle at index" << i << "is null";
            continue;
        }

        if (net_status == "online") {
            qDebug() << "Setting status circle color to green for sender ID:" << senderId;
            statusCircle->setStyleSheet("border-radius: 5px; background-color: green;");
        } else {
            qDebug() << "Setting status circle color to gray for sender ID:" << senderId;
            statusCircle->setStyleSheet("border-radius: 5px; background-color: gray;");
        }

        // Force repaint to ensure the UI updates
        statusCircle->repaint();
    }
}

void ChatWidget::onTextMessageReceived(const QString &message) {
    qDebug() << "namaka eke:" << message;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    if(jsonDoc.isNull()){
        qWarning() << "Failed to create Json doc";
        return;
    }
    QJsonObject jsonMessage = jsonDoc.object();

    if(jsonMessage["type"] == "search_result"){
        searchResult(message);
    }else if(jsonMessage["type"] == "status_update"){
        QString net_status = jsonMessage["net_status"].toString();
        int senderId = jsonMessage["target_id"].toString().toInt();
        updateChatButtonStyle(senderId, net_status);
    }else{
        int senderId = jsonMessage["sender_id"].toString().toInt();
        QString messageText = "    " + jsonMessage["message"].toString() + "    ";
        QString senderName = jsonMessage["sender_name"].toString();
        QString status = "online";

        auto it = messageMap.find(senderId);
        Message msg {.senderId = senderId, .senderName = senderName, .text = messageText, .timestamp = QDateTime::currentDateTime(), .status = status};
        messageMap[senderId].push_back(msg);
        if ( it == messageMap.end() ){
            addNewChatButton(senderId, senderName, status);

        if (my.currentChatId == -1){
            my.currentChatId = senderId;
        }
    }

    // If the current chat is the sender, display
    qDebug() << "currentChatID" << my.currentChatId;

    if (senderId == my.currentChatId) {
        std::cout << __LINE__ << std::endl;
        displayMessages(senderId);
    }
    }
}

void ChatWidget::receiveResponse(const QString &responseBody) {
    qDebug() << "Received response in ChatWidget:" << responseBody;
    processResponse(responseBody);
}

void ChatWidget::send_message(QString& message){
    QJsonObject json_object_message;
    json_object_message["recipient_id"] = QString::number(my.currentChatId);
    std::cout << "Koko uxarkleuc drela id: " << my.Id;
    json_object_message["sender_id"] = QString::number(my.Id);
    json_object_message["sender_name"] = my.Name;
    json_object_message["type"] = "message";
    json_object_message["message"] = message;

    Message msg {.senderId = my.Id, .text = message, .timestamp = QDateTime::currentDateTime()};
    messageMap[my.currentChatId].push_back(msg);
    QJsonDocument json_doc_message(json_object_message);
    QString formated_message = json_doc_message.toJson(QJsonDocument::Compact);
    webSocket->sendTextMessage(formated_message);
}

void ChatWidget::searchRequest(QString body){
        QJsonObject json_object_message;
        json_object_message["type"] = "search";
        json_object_message["email"] = body;
        json_object_message["sender_name"] = my.Name;
        QJsonDocument json_doc_message(json_object_message);
        QString formated_message = json_doc_message.toJson(QJsonDocument::Compact);
        webSocket->sendTextMessage(formated_message);
}

void ChatWidget::searchResult(const QString &message) {
    qDebug() << "Search Result:" << message;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    if(jsonDoc.isNull()){
        qWarning() << "Failed to create Json doc";
        return;
    }
    QJsonObject jsonMessage = jsonDoc.object();
    int targetId = jsonMessage["user_id"].toInt();
    QString targetName = jsonMessage["target_name"].toString();
    QString status = jsonMessage["net_status"].toString();
    if (targetId == -1) return;
    auto it = messageMap.find(targetId);                                    // ----poxel toxy----------

    if ( it == messageMap.end() ){
        addNewChatButton(targetId, targetName, status);
        messageMap[targetId] = std::vector<Message>();
        if (my.currentChatId == -1){
            my.currentChatId = targetId;
        }
    }
    if (targetId == my.currentChatId) {
        displayMessages(targetId);
    }
}

void ChatWidget::sendWebSocketRequest() {
    webSocket = new QWebSocket();
    connect(webSocket, &QWebSocket::connected, this, [=]() {
        qDebug() << "WebSocket connected!";
    });
    connect(webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, [=](QAbstractSocket::SocketError error) {
        qDebug() << "WebSocket error:" << error;
    });
    connect(webSocket, &QWebSocket::disconnected, this, [=]() {
        qDebug() << "WebSocket disconnected!";
    });
    connect(webSocket, &QWebSocket::textMessageReceived, this, &ChatWidget::onTextMessageReceived);
    QUrl url("ws://localhost:8080");
    QNetworkRequest request(url);
    request.setRawHeader("Session-ID", my.sessionId.toUtf8());
    webSocket->open(request);
}

void ChatWidget::processResponse(const QString &responseBody) {
    messageMap.clear();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseBody.toUtf8());
    if (!jsonResponse.isNull()) {
        QJsonObject jsonObject = jsonResponse.object();
        my.sessionId = jsonObject["session_id"].toString();
        my.Id = jsonObject["user_id"].toString().toInt();
        my.Name = jsonObject["user_name"].toString();
        emit loginSuccess();
        QJsonArray messagesArray = jsonObject["messages"].toArray();
        for (const auto &message : messagesArray) {
            QJsonObject messageObject = message.toObject();
            QString messageText = messageObject["message"].toString();
            int senderId = messageObject["sender_id"].toInt();
            QString senderName = messageObject["sender_name"].toString();
            QString status = messageObject["net_status"].toString();

            Message msg {.senderId = senderId, .senderName = senderName, .text = messageText, .timestamp = QDateTime::currentDateTime(), .status = status};
            if(msg.text == "") {searchFriends.insert(senderId);}
            else {messageMap[senderId].push_back(msg);}
        }
    }
    addChatButtons();
}

QWidget* ChatWidget::createChatButton(int senderId, const QString &chatName, const QString &status) {
    QWidget *chatWidget = new QWidget();
    QVBoxLayout *chatLayout = new QVBoxLayout(chatWidget);
    // Chat status
    QLabel *statusCircle = new QLabel();
    statusCircle->setFixedSize(10, 10);
    if (status == "offline") {
        statusCircle->setStyleSheet("border-radius: 5px; background-color: gray;");
    } else {
        statusCircle->setStyleSheet("border-radius: 5px; background-color: green;");
    }
    // Chat button
    QPushButton *chatButton = new QPushButton(chatName);
    chatButton->setFixedSize(450, 100);
    // Add to chat list
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(statusCircle);
    buttonLayout->addWidget(chatButton);
    chatLayout->addLayout(buttonLayout);
    chatWidget->setLayout(chatLayout);

    connect(chatButton, &QPushButton::clicked, this, [this, senderId]() {
        my.currentChatId = senderId;
        displayMessages(senderId);
    });

    return chatWidget;
}

void ChatWidget::addChatButtons() {
    std::set<int> uniqueSenderIds;
    for (const auto &entry : messageMap) {
        uniqueSenderIds.insert(entry.first);
    }

    for (int senderId : uniqueSenderIds) {
        auto it = messageMap.find(senderId);
        QString chatName = it->second.front().senderName;
        QString status = it->second.front().status;

        QWidget *chatWidget = createChatButton(senderId, chatName, status);
        chatListLayout->addWidget(chatWidget);
    }
}

void ChatWidget::addNewChatButton(int senderId, const QString &chatName, const QString &status) {
    std::cout << "oline message" << std::endl;
    QWidget *chatWidget = createChatButton(senderId, chatName, status);
    chatListLayout->addWidget(chatWidget);
}

void ChatWidget::displayMessages(int senderId) {
    htmlContent.clear();
    auto it = messageMap.find(senderId);
    if (it != messageMap.end()) {
        for (const Message &msg : it->second) {
            QString formatted_message;
            if (msg.senderId == my.Id) {
                formatted_message = QString("<div style='text-align: left;'><span style='display: inline-block; padding: 5px; margin: 5px; color: black; font-weight: bold; font-size: 20px;'>Me: %1</span></div>").arg(msg.text);
            } else {
                formatted_message = QString("<div style='text-align: left;'><span style='display: inline-block; padding: 5px; margin: 5px; color: black; font-weight: bold; font-size: 20px;'>%1: %2</span></div>").arg(msg.senderName ,msg.text);
            }
            htmlContent += formatted_message;
        }
    }
    chatDisplay->clear();
    chatDisplay->setHtml(htmlContent);
}

void ChatWidget::printMessageMap(const std::multimap<int, QString> &messageMap) {
    for (auto it = messageMap.begin(); it != messageMap.end(); ++it) {
        qDebug() << "Sender ID:" << it->first << ", Message:" << it->second;
    }
}
