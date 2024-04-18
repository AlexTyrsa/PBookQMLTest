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

        anchors.fill: parent

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
}
