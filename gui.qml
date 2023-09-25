import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform
import MqttClient 1.0

import "qrc:/"

ApplicationWindow{
    visible: true
    height: 600
    width: 800
    color: "lightblue"
    title: "MQTT test"

    MqttClient{
        id: client
        hostname: host.text
        port: port.text
        username: username.text
        password: password.text
        fileName: filepath.text
        willTopic: topic.text
    }

    ColumnLayout{
        spacing: 20
        anchors.centerIn: parent

        MyRowLayout{
                MyLabel{
                id: hostLabel
                text: "Host"
            }
            MyTextInput{
                id: host
                text: "test.mosquitto.org"
            }
        }
        MyRowLayout{
            MyLabel{
                text: "Port"
            }
            MyTextInput{
                id: port
                text: "1883"
                validator: IntValidator{bottom: 0; top: 65536}
            }
        }
        MyRowLayout{
            MyLabel{
                text: "Username"
            }
            MyTextInput{
                id: username
            }
        }
        MyRowLayout{
            MyLabel{
                text: "Password"
            }
            MyTextInput{
                id: password
                echoMode: TextInput.Password
            }
        }
        MyRowLayout{
            MyLabel{
                text: "Topic"
            }
            MyTextInput{
                id: topic
                text: "piklema/test"
            }
        }
        MyRowLayout{

            MyLabel{
                text: "Filepath"
            }
            MyTextInput{
                id:filepath
                selectByMouse: true
                MouseArea{
                    anchors.fill: parent
                    onClicked: filedialog.open()
                }
            }

            FileDialog{
                id: filedialog
                title: "Выберите файл"
                folder: shortcuts.home
                acceptLabel: "Выбрать"
                nameFilters: ["Text files(*.txt)"," All files(*.*)"]
                onAccepted: {
                    filepath.text = currentFile
                }
            }
        }
        RoundButton{
            id: run
            text: "Run"
            font.pixelSize: 24
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
            radius: 10
            enabled: !client.isBusy
            onClicked: {
                client.sendFile()
            }
        }
        MyLabel{
            text: "Строк отправленно: " + client.lineCount
        }
    }
}


