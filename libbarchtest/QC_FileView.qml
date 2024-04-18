import QtQuick 2.15
import QFileListLib 1.0
import '.'

Item
{
    id: root

    property QFileListData dataList

    ListView
    {
        id: fileList

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: selectedFile.bottom

        model: dataList.items.length

        delegate: QC_FileItemView
        {
            dataItem: dataList.items[index]

            anchors.left : parent.left
            anchors.right : parent.right

            backColor: index % 2 == 0 ? '#202020' : '#505050'
            textColor: dataItem.selected ? '#6565FF' : '#FFFFFF'
        }
    }

    QC_FileSelectedItemView
    {
        id: selectedFile

        dataItem: dataList.selected

        backColor: 'grey'
        height: 100

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
