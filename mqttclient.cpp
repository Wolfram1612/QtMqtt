#include "mqttclient.h"

#include <QValidator>

MqttClient::MqttClient(QObject *parent)
    : QMqttClient{parent}
{
    connect(this, &QMqttClient::connected, [=](){
        qInfo() << "Соединение с хостом установленно.";

        setIsBusy(true);
        QFile datafile(QUrl(m_filename).toLocalFile());
        if(!datafile.open(QIODevice::ReadOnly)){
            qCritical() << "Не удалось открыть файл с данными." << fileName();
        }
        QIntValidator validator;
        int pos = 0;
        QTextStream s(&datafile);
        while(!s.atEnd()){
            QString line(s.readLine());
            if(validator.validate(line, pos) == QValidator::Acceptable){
                qDebug() << QMqttClient::publish(willTopic(), line.toLocal8Bit(), 0, false);
                setLineCount(m_lineCount+1);
            }

        }
        datafile.close();

        qDebug() << "Отключение от хоста.";
        disconnectFromHost();
        setIsBusy(false);
    });

    connect(this, &QMqttClient::disconnected, [=](){
        qInfo() << "Соединение с хостом разорванно.";
        setIsBusy(false);
    });

    connect(this, &QMqttClient::errorChanged, [=](QMqttClient::ClientError error){
        setIsBusy(false);
        if(error > 0)
            qWarning() << "Ошибка: " << error;
    });

}

void MqttClient::sendFile()
{
    setIsBusy(true);
    qDebug() << "Подключение к хосту.";
    setLineCount(0);
    connectToHost();
}
