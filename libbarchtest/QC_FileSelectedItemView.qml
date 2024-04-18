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

                text: "Status: " + dataItem.statusDescription
            }

            RowLayout
            {
                anchors.left : parent.left
                anchors.right : parent.right

                Text
                {
                    color: textColor
                    text: "Src: " + dataItem.source

                    elide: Text.ElideLeft

                    Layout.alignment: Qt.AlignLeft
                    Layout.fillWidth: true
                }

                Text
                {
                    color: textColor
                    text: Math.floor(dataItem.sourceSize / 1024) + ' Kb'
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
                    text: "Dst: " + dataItem.destination

                    elide: Text.ElideLeft

                    Layout.alignment: Qt.AlignLeft
                    Layout.fillWidth: true
                }

                Text
                {
                    color: textColor
                    text: Math.floor(dataItem.destinationSize / 1024) + ' Kb'
                    horizontalAlignment: Text.AlignRight

                    Layout.alignment: Qt.AlignRight
                }
            }
        }
    }
}
