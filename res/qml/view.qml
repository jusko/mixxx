import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ListView {
    id: root
    anchors.fill: parent
    boundsBehavior:  Flickable.StopAtBounds

    signal loadTrack(int row, string group)

    Component.onCompleted: {
        root.loadTrack.connect(LiteTrackListModel.slotLoadTrack)
    }

    model: LiteTrackListModel

    delegate: Item {
        width: root.width
        height: coverArt.height

        Flickable {
            anchors.fill: parent
            flickableDirection: Flickable.HorizontalFlick

            onFlickStarted: {
               root.loadTrack(model.row, "[Channel" + (contentX > 0 ? "1]" : "2]"));
            }

            MouseArea {
                anchors.fill: parent
                onClicked: console.debug(model.title + " click")
            }

            Row {
                spacing: 20
                
                Text {
                    id: coverArt
                    height: 80
                    text: "<Cover Art>"
                }

                Column {
                    spacing: 3
                    Text {
                        text: model.title
                        font.bold: true
                    }

                    Text {
                        text: model.artist
                    }

                    Row {
                        spacing: 30
                        Text {
                            text: model.bpm
                        }
                        Text {
                            text: model.key
                        }
                        Text {
                            text: model.duration
                        }
                    }
                }
            }
        }
    } 
} 
