import QtQuick 2.15
import QFileListLib 1.0
import QtQuick.Controls 2.1
import '.'

Item
{
    id: root

    property QFileListData dataList

    signal failed(string file, string what)

    ListView
    {
        id: fileList

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: selectedFile.bottom

        flickableDirection: Flickable.VerticalFlick
        boundsBehavior: Flickable.StopAtBounds

        clip: true

        ScrollBar.vertical: ScrollBar {}

        model: dataList.items.length

        delegate: QC_FileItemView
        {
            dataItem: dataList.items[index]

            anchors.left : parent.left
            anchors.right : parent.right

            backColor: index % 2 == 0 ? '#202020' : '#505050'
            textColor: dataItem.selected ? '#6565FF' : '#FFFFFF'

            onFailed: (what) =>
            {
                root.failed(dataItem.source, what);
            }
        }
    }

    QC_FileSelectedItemView
    {
        id: selectedFile

        dataItem: dataList.selected

        visible: dataItem

        backColor: 'grey'
        height: 100

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
