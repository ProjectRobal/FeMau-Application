import QtQuick
import QtQuick.Layouts
import QtCharts
import QtQuick.Controls



Window {

    readonly property font defFont: ({
        family: "Arial",
        pointSize: 13,
        bold: true
    })

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


        // ChartView {
        //     anchors.fill:parent

        //     antialiasing: true

        //     LineSeries {
        //         name: "Temperature"
        //         XYPoint { x: 0; y: 0 }
        //         XYPoint { x: 1.1; y: 2.1 }
        //         XYPoint { x: 1.9; y: 3.3 }
        //         XYPoint { x: 2.1; y: 2.1 }
        //         XYPoint { x: 2.9; y: 4.9 }
        //         XYPoint { x: 3.4; y: 3.0 }
        //         XYPoint { x: 4.1; y: 3.3 }
        //     }
        // }
    GridLayout
    {
        id:root
        columns:4
        anchors.fill:parent.fill
        width: parent.width
        height: parent.height

        ColumnLayout
        {
            Layout.columnSpan: 2
            Layout.column: 1
            Layout.fillWidth: true
            anchors.top: parent.top
            Layout.topMargin: 10
            Layout.bottomMargin: 10

            RowLayout
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                Text {
                    text: qsTr("Temperature:")
                    font: defFont
                    // Layout.fillWidth: true
                    // Layout.fillHeight: true
                }

                Text {
                    id: temperature
                    text: qsTr("0 °C")
                    Layout.fillWidth: true
                    font: defFont
                    // Layout.fillHeight: true
                }
            }

            RowLayout
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                Text {
                    text: qsTr("Power:")
                    font: defFont
                    // Layout.fillWidth: true
                    // Layout.fillHeight: true
                }

                Text {
                    width:parent.width
                    id: power
                    text: qsTr("0 %")
                    font: defFont
                    Layout.fillWidth: true
                    // Layout.fillHeight: true
                }
            }

            RowLayout
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                Text {
                    text: qsTr("PID:")
                    font: defFont
                    // Layout.fillWidth: true
                    // Layout.fillHeight: true
                }

                SpinBox
                {
                    id: propotional
                    Layout.fillWidth: false
                    from: 1
                    editable: true
                    font: defFont
                }

                SpinBox
                {
                    id: integral
                    Layout.fillWidth: false
                    from: 0
                    editable: true
                    font: defFont
                }

                SpinBox
                {
                    id: differential
                    Layout.fillWidth: false
                    from: 0
                    editable: true
                    font: defFont
                }
            }

            Button
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                id:set_pid
                text:"Set PID"
                font: defFont
            }

            RowLayout
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                SpinBox
                {
                    id: set_temperature_val
                    Layout.fillWidth: false
                    from: 0
                    to: 300
                    editable: true
                    font: defFont
                }

                Button
                {
                    id: set_temperature_button
                    text: "Set temperature"
                    font: defFont
                }
            }
        }


        ColumnLayout
        {
            Layout.columnSpan: 2
            Layout.fillWidth: true
            Layout.column: 0
            Layout.topMargin: 10
            Layout.bottomMargin: 10

            RowLayout
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                Button
                {
                    id: reset_chart
                    text: "Reset"
                }

                Button
                {
                    id: save_chart
                    text: "Save"
                }

                Button
                {
                    id: mode_select
                    text: "Automatic"
                }
            }
        }
    }

}
