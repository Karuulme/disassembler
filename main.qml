import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick
import Qt.labs.qmlmodels
import QtQuick.Layouts 1.15
import QtQuick.Window 2.12
Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: "Ana Pencere"

    Rectangle {
        width: parent.width
        height: parent.height

        // Ana pencere içeriği
        Text {
            text: "Ana Pencere İçeriği"
            anchors.centerIn: parent
        }

        // Alt pencere
      /*  Window {
            id: subWindow
            visible: true
            width: 200
            height: 200
            color: "lightblue"
            flags: Qt.Tool

            // Alt pencere içeriği
            Text {
                text: "Alt Pencere İçeriği"
                anchors.centerIn: parent
            }

            // Alt pencereyi sağ kenara sabitle
            property bool isSized: false
            property int windowWidth: 200

            MouseArea {
                id: dragArea
                anchors.fill: parent
                cursorShape: Qt.SizeAllCursor

                onPressed: {
                    subWindow.isSized = true
                }

                onPositionChanged: {
                    if (subWindow.isSized) {
                        if (mouse.x < 0) {
                            subWindow.x = 0
                        } else if (mouse.x > mainWindow.width - subWindow.windowWidth) {
                            subWindow.x = mainWindow.width - subWindow.windowWidth
                        } else {
                            subWindow.x = mouse.x
                        }
                        subWindow.y = mouse.y
                    }
                }

                onReleased: {
                    subWindow.isSized = false
                }
            }
        }*/
}

   /* Rectangle{
        width: 250
        height: 250
        color:"red"
        MouseArea {
               id: dragArea
               anchors.fill: parent
               cursorShape: Qt.SizeHorCursor

               property int mouseX

               onPressed: {
                   mouseX = mouse.x
               }

               onPositionChanged: {
                   myRect.x += mouse.x - mouseX
                   mouseX = mouse.x
               }
           }
        Window {
            id: subWindow
            visible: true
            width: 200
            height: 200
            color: "lightblue"
            //flags: Qt.Tool
            flags: Qt.FramelessWindowHint
        }
    }
*/


}

/*
    MenuBar {
        id: menuBar

        Menu {
            id: fileMenu
            title: qsTr("File")
            MenuItem { text: qsTr("&New...") }
            MenuItem { text: qsTr("&Open...") }
            MenuItem { text: qsTr("&Save") }
            MenuItem { text: qsTr("Save &As...") }
            MenuItem { text: qsTr("&Exit") }
            Rectangle {
                color: "lightgray" // Menü arka plan rengini burada ayarlayın
                width: fileMenu.width-2

            }
        }

        Menu {
            id: editMenu
            title: qsTr("&Edit")
            Rectangle {
                color: "lightgray" // Menü arka plan rengini burada ayarlayın
                width: editMenu.width

            }
            MenuItem { text: qsTr("&Undo") }
            Rectangle {
                color: "black"
                width: editMenu.width
                height: 1

            }
            MenuItem { text: qsTr("&Redo") }
            Rectangle {
                color: "black"
                width: editMenu.width
                height: 1

            }
            MenuItem { text: qsTr("Cu&t") }
            Rectangle {
                color: "black"
                width: editMenu.width
                height: 1

            }
            MenuItem { text: qsTr("&Copy") }
            Rectangle {
                color: "black"
                width: editMenu.width
                height: 1

            }
            MenuItem { text: qsTr("&Paste") }
        }

        // Diğer menüler için aynı şekilde yapabilirsiniz
    }
    Rectangle {
          anchors.topMargin: 28
          id: rectangle
          anchors.fill: parent
          color: "darkGrey"

          SplitView {
              id: horizontalSplitView
              anchors.fill: parent
              orientation: Qt.Horizontal

              Rectangle {
                  id: leftRectangle
                  SplitView.fillWidth: true
                  SplitView.minimumWidth: 200
                  color: "red"
              }

              Rectangle {
                  id: rightRectangle
                  SplitView.minimumWidth: 200
                  color: "green"
              }
          }
      }*/

