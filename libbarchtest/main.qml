import QtQuick 2.15
import QtQuick.Window 2.15
import QFileListLib 1.0
import "."

Window
{
    width: 800
    height: 600
    visible: true
    title: qsTr("libbarch")

    color: "grey"

    QC_FileView
    {
        objectName: "fileView"

        anchors.fill: parent
        anchors.margins: 20

        dataList: QFileListData{}
    }
}
