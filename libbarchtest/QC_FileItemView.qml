import QtQuick 2.15
import QtQuick.Layouts
import QFileListLib 1.0

Item
{
    id: root

    property QFileListDataItemI dataItem
    property color textColor: 'black'
    property color backColor: "white"

    signal failed(string what)

    implicitHeight: 25

    Rectangle
    {
        anchors.fill: parent
        color: backColor

        RowLayout
        {
            id: layout

            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10

            spacing: 20

            Text
            {
                id: textStatus
                color: textColor

                states:
                [
                    State
                    {
                        name: "ready"
                        when: dataItem.status == QFileListDataItemI.EQFileListDataItemStatus_Ready
                        PropertyChanges { target: textStatus; text: "Ready"}
                    },
                    State
                    {
                        name: "inprogress"
                        when: dataItem.status == QFileListDataItemI.EQFileListDataItemStatus_InProgress
                        PropertyChanges { target: textStatus; text: "In Progress"}
                    },
                    State
                    {
                        name: "complete"
                        when: dataItem.status == QFileListDataItemI.EQFileListDataItemStatus_Complete
                        PropertyChanges { target: textStatus; text: "Complete"}
                    },
                    State
                    {
                        name: "fail"
                        when: dataItem.status == QFileListDataItemI.EQFileListDataItemStatus_Fail
                        changes:[
                                    PropertyChanges{target: textStatus; text: "Fail"},
                                    StateChangeScript{ script: root.failed(dataItem.statusDescription)}
                                ]
                    }
                ]

                Layout.alignment: Qt.AlignLeft
                Layout.fillWidth: false
                Layout.preferredWidth: 70
            }

            Text
            {
                id: textName
                color: textColor
                text: dataItem.source

                elide: Text.ElideLeft

                Layout.alignment: Qt.AlignLeft
                Layout.fillWidth: true
            }

            Text
            {
                id: textSize
                color: textColor
                text: Math.floor(dataItem.sourceSize / 1024) + ' Kb'
                horizontalAlignment: Text.AlignRight

                Layout.alignment: Qt.AlignRight
            }
        }
    }

    MouseArea
    {
        anchors.fill: parent

        onClicked:
        {
            dataItem.selected = true;
            dataItem.processItem();
        }
    }
}
