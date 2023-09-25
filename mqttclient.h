#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <QMqttClient>

#include <QObject>
#include <QQmlEngine>

#include <QFile>

class MqttClient : public QMqttClient
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged FINAL)
    Q_PROPERTY(int lineCount READ lineCount WRITE setLineCount NOTIFY lineCountChanged FINAL)
    Q_PROPERTY(bool isBusy READ isBusy WRITE setIsBusy NOTIFY isBusyChanged FINAL)
    QML_ELEMENT

public:
    explicit MqttClient(QObject *parent = nullptr);

public slots:
    void sendFile();

    const QString fileName(){return m_filename;}
    void setFileName(QString fileName) {m_filename = fileName;}

    int lineCount() const {return m_lineCount;}
    void setLineCount(int lineCount) {
        m_lineCount = lineCount;
        emit lineCountChanged(m_lineCount);
    }

    bool isBusy() const{return m_isBusy;}
    void setIsBusy(bool isBusy){
        m_isBusy = isBusy;
        emit isBusyChanged(m_isBusy);
    }

private:
    QString m_filename;
    int m_lineCount = 0;
    bool m_isBusy = false;

signals:
    void fileNameChanged(QString fileName);
    void lineCountChanged(int lineCount);
    void isBusyChanged(bool isBusy);
};

#endif // MQTTCLIENT_H
