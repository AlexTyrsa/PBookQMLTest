import QtQuick 2.2
import QtQuick.Controls 2.15

Dialog
{
    id: root

    property string text: ""

    implicitWidth: 400
    implicitHeight: 150

    title: "Error"
    standardButtons: Dialog.Ok

    contentItem: Item
    {
        Text
        {
            text: root.text
            anchors.centerIn: parent
        }
    }
}
