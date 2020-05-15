import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import QtQuick 2.14

ApplicationWindow {

    // Application Window attributes
    id: root
    visible: true
    width: 1920
    height: 1080
    title: "Hydro-UQ"
    minimumWidth: 1024
    minimumHeight: 768
    Material.theme: Material.Light
    Material.accent: Material.Purple

    // Menu bar items
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
                MenuItem {
                    text: qsTr("Exit")
                    onTriggered: Qt.quit();
                }
            }
        }

    // Top frame
    Grid {
        id: grid
        width: parent.width
        height: parent.height
        anchors.right: parent.right
        anchors.rightMargin: 12
        anchors.left: parent.left
        anchors.leftMargin: 12
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 12
        anchors.top: parent.top
        anchors.topMargin: 12
        spacing: 12
        columns: 1
        rows: 3

        Frame {
            id: frame
            width: parent.width
            height: 0.1*parent.height
            padding: 0
            focusPolicy: Qt.StrongFocus


            Image {
                id: h20logo
                source: "qrc:/new/res/images/SimCenter_H2O_logo.png"
                fillMode: Image.PreserveAspectFit
                height: parent.height
                x:6
            }
        }

        Grid {
            id: grid2
            width: parent.width
            height: 0.77*parent.height
            columns: 2
            rows: 1

            Column {
                            id: column1
                            width: 0.2*parent.width
                            height: parent.height
                            layer.enabled: true

                            Image {
                                id: h20logo2
                                source: "qrc:/new/res/images/SimCenter_H2O_logo.png"
                                height: parent.height
                                x:6
                            }
                        }

                        Column {
                            id: column2
                            width: 0.2*parent.width
                            height: parent.height
                            layer.enabled: true

                            Image {
                                id: h20logo3
                                source: "qrc:/new/res/images/SimCenter_H2O_logo.png"
                                height: parent.height
                                x:6
                            }
                        }

                        Column {
                            id: column3
                            width: 0.6*parent.width
                            height: parent.height
                            layer.enabled: true

                            Image {
                                id: h20logo4
                                source: "qrc:/new/res/images/SimCenter_H2O_logo.png"
                                height: parent.height
                                x:6
                            }
                        }
        }

        Frame {
            id: frame3
            width: parent.width
            height: 0.1*parent.height
            padding: 0
            focusPolicy: Qt.StrongFocus
        }






    }
}
/*##^##
Designer {
    D{i:4;anchors_x:53;anchors_y:27}
}
##^##*/
