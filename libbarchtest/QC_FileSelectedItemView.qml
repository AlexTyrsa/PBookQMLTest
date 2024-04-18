import QtQuick 2.15
import QtQuick.Layouts
import QFileListLib 1.0

Item
{
    id: root

    property QFileListDataItemI dataItem

    property color backColor: 'white'
    property color textColor: 'black'

    Rectangle
    {
        anchors.fill: parent

        color: backColor

        Column
        {
            anchors.fill: parent

            anchors.leftMargin: 10
            anchors.rightMargin: 10

            Text
            {
                anchors.left : parent.left
                anchors.right : parent.right

                color: textColor

                text: "Status: " + (dataItem ? dataItem.statusDescription : "")
            }

            RowLayout
            {
                anchors.left : parent.left
                anchors.right : parent.right

                Text
                {
                    color: textColor
                    text: "Src: " + (dataItem ? dataItem.source : "")

                    elide: Text.ElideLeft

                    Layout.alignment: Qt.AlignLeft
                    Layout.fillWidth: true
                }

                Text
                {
                    color: textColor
                    text: Math.floor((dataItem ? dataItem.sourceSize : 0) / 1024) + ' Kb'
                    horizontalAlignment: Text.AlignRight

                    Layout.alignment: Qt.AlignRight
                }
            }

            RowLayout
            {
                anchors.left : parent.left
                anchors.right : parent.right

                Text
                {
                    color: textColor
                    text: "Dst: " + (dataItem ? dataItem.destination : "")

                    elide: Text.ElideLeft

                    Layout.alignment: Qt.AlignLeft
                    Layout.fillWidth: true
                }

                Text
                {
                    color: textColor
                    text: Math.floor((dataItem ? dataItem.destinationSize : 0) / 1024) + ' Kb'
                    horizontalAlignment: Text.AlignRight

                    Layout.alignment: Qt.AlignRight
                }
            }
        }
    }
}
