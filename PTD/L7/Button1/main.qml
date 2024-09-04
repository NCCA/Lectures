import QtQuick 
import QtQuick.Controls 
import QtQuick.Layouts
Window {
    visible: true
    width: 800
    height: 600
    title: qsTr("Button Types")
    GridLayout{
        anchors.fill: parent
        rows:   4
        columns:   3
    Button {
        Layout.row : 0
        Layout.columnSpan : 1
        text: qsTr("Simple Button")
        onPressed : {
            button1action.text = "onPress"
        }

        onReleased: {
            button1action.text = "onReleased"
        }

    }
    Text {
        id : button1action
        Layout.row : 0
        Layout.column : 1
        text : ""
    }
    ButtonGroup {
        id: radioGroup
    }
        RadioButton{
            Layout.row : 1
            Layout.column: 0
            checked: true
            text : qsTr("radio buttons")
              ButtonGroup.group: radioGroup
        }
        RadioButton{
            Layout.row : 1
            Layout.column: 1
            checked: false
            text : qsTr("are")
            ButtonGroup.group: radioGroup
        }
        RadioButton{
            Layout.row : 1
            Layout.column: 2

            checked: false
            text : qsTr("exclusive")
            ButtonGroup.group: radioGroup
        }
    }
}
