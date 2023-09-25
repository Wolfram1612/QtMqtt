#include <QGuiApplication>

#include <QQmlApplicationEngine>

#include <iostream>

#include "mqttclient.h"

#include <QDebug>


void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile logFile("log.txt");
    if(!logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        std::cout << "Не удаётся открыть лог файл." << std::endl;
    }
    QTextStream s(&logFile);
    s << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss ");

    switch (type) {
    case QtDebugMsg:
        s << "Debug: ";
        break;
    case QtInfoMsg:
        s << "Info: ";
        break;
    case QtWarningMsg:
        s << "Warning: ";
        break;
    case QtCriticalMsg:
        s << "Critical: ";
        break;
    case QtFatalMsg:
        s << "Fatal: ";
        break;
    }

    s << msg << Qt::endl;

    logFile.close();
}
int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);

    qInfo() << "Запуск приложения.";
    QGuiApplication a(argc, argv);

    QQmlApplicationEngine eng;
    qmlRegisterType<MqttClient>("MqttClient", 1, 0, "MqttClient");

    qInfo() <<  "Загрузка интерпретатора QML.";
    eng.load(QString("qrc:gui.qml"));
    if(eng.rootObjects().isEmpty()){
        qCritical() <<  "Загрузка интерпретатора QML не удалась.";
        return -1;
    }

    QObject::connect(&a, &QGuiApplication::aboutToQuit, []() {
        qWarning() << "Выход из приложения";
    });
    return a.exec();
}
