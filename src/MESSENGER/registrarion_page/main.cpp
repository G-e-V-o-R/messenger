#include "mainwindow.h"
#include "regwidget.h"
#include "logwidget.h"
#include "chatwidget.h"
#include <QApplication>
#include <QStackedWidget>
#include <QVBoxLayout>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QStackedWidget *stackedWidget = new QStackedWidget;

    LogWidget* logWidget = new LogWidget(stackedWidget);
    logWidget->setFixedSize(500, 300);

    RegWidget* regWidget = new RegWidget(stackedWidget);
    regWidget->setFixedSize(500, 300);

    ChatWidget* chatWidget = new ChatWidget;

    QWidget* logContainer = new QWidget();
    QVBoxLayout* logLayout = new QVBoxLayout(logContainer);
    logLayout->addStretch();
    logLayout->addWidget(logWidget, 0, Qt::AlignCenter);
    logLayout->addStretch();
    logContainer->setLayout(logLayout);

    QWidget* regContainer = new QWidget();
    QVBoxLayout* regLayout = new QVBoxLayout(regContainer);
    regLayout->addStretch();
    regLayout->addWidget(regWidget, 0, Qt::AlignCenter);
    regLayout->addStretch();
    regContainer->setLayout(regLayout);

    QWidget* chatContainer = new QWidget();
    chatContainer->setStyleSheet("background-color: lightblue;");
    QVBoxLayout* chatLayout = new QVBoxLayout(chatContainer);
    chatLayout->setContentsMargins(0, 0, 0, 0);
    chatLayout->addWidget(chatWidget);
    chatContainer->setLayout(chatLayout);

    stackedWidget->addWidget(logContainer);
    stackedWidget->addWidget(regContainer);
    stackedWidget->addWidget(chatContainer);

    stackedWidget->setCurrentIndex(0);

    QWidget* centralWidget = new QWidget(&w);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(stackedWidget);
    centralWidget->setLayout(mainLayout);

    QObject::connect(regWidget, &RegWidget::registrationSuccess, [=]() {
        stackedWidget->setCurrentWidget(logContainer);
    });

    QObject::connect(logWidget, &LogWidget::loginSuccess, [=]() {
        stackedWidget->setCurrentWidget(chatContainer);
    });

    QObject::connect(logWidget, &LogWidget::signUpRequested, [=]() {
        stackedWidget->setCurrentWidget(regContainer);
    });

    QObject::connect(logWidget, &LogWidget::responseReceived, chatWidget, &ChatWidget::receiveResponse);


    w.setCentralWidget(centralWidget);
    w.show();

    return a.exec();
}
