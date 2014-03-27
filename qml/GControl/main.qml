import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.0

ApplicationWindow {
    title: qsTr("GControl")
    color: "black"

    Rectangle {
        anchors.fill: parent
        antialiasing: true
        gradient: Gradient {
            GradientStop {
                position: 0.166
                color: "#000000"
            }

            GradientStop {
                position: 0.709
                color: "#1e2024"
            }

            GradientStop {
                position: 1
                color: "#32405b"
            }

        }

        ColumnLayout {
            anchors.fill: parent
            RowLayout {

                Rectangle {
                    implicitHeight: 15
                    Layout.fillWidth: true
                    color: "transparent"
                    Text {
                        text: "Stream"
                        color: "white"
                        font.bold: true
                        style: Text.Raised
                    }
                }

                Rectangle {
                    implicitHeight: 15
                    Layout.fillWidth: true
                    color: "transparent"
                Text {

                    text: "State"
                    color: "white"
                    font.bold: true
                    style: Text.Raised
                }
                }
            }

            RowLayout {
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    border.width:  2
                    border.color: "steelblue"
                }

                Rectangle {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: "transparent"
                    border.width: 2
                    border.color: "steelblue"

                    ColumnLayout {

                        Button {
                            text: "Get temp"
                            onClicked: device.getTemp()
                        }

                        Text {
                            id: txtTemp
                            color: "white"
                            text: device.pTemp
                        }
                    }
                }
            }
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")

            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }
}
