#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QStandardItemModel>
#include <QStringList>

class ChatModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit ChatModel(QObject *parent = nullptr)
        : QStandardItemModel(parent)
    {
        QStringList chatList = {"Chat 1", "Chat 2", "Chat 3", "Chat 4"};
        for (const QString &chatName : chatList) {
            QStandardItem *item = new QStandardItem(chatName);
            appendRow(item);
        }
    }
};

#endif // CHATMODEL_H
