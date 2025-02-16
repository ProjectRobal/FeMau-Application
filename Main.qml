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

    width: 800
    height: 600
    visible: true
    title: "FeMau Application"

    GridLayout
    {
        id:root
        columns:4

        anchors.fill:parent.fill
        width: parent.width
        height: parent.height

        ColumnLayout
        {
            Layout.columnSpan: 1
            Layout.column: 3
            // Layout.fillWidth: true
            // Layout.fillHeight: true

            Layout.alignment: Qt.AlignTop

            Layout.margins: 10

            RowLayout
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                Text {
                    text: "Temperature:"
                    font: defFont
                    // Layout.fillWidth: true
                    // Layout.fillHeight: true
                }

                Text {
                    id: temperature
                    text: "0 °C"
                    // Layout.fillWidth: true
                    font: defFont
                    // Layout.fillHeight: true
                }
            }

            RowLayout
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                Text {
                    text: "Power:"
                    font: defFont
                    // Layout.fillWidth: true
                    // Layout.fillHeight: true
                }

                Text {
                    width:parent.width
                    id: power
                    text: "0 %"
                    font: defFont
                    // Layout.fillWidth: true
                    // Layout.fillHeight: true
                }
            }

            RowLayout
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                Text {
                    text: "PID:"
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
                    // Layout.fillWidth: false
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
            Layout.columnSpan: 3
            // Layout.fillWidth: true
            // Layout.fillHeight: true
            Layout.column: 0
            Layout.margins: 10

            ChartView {

                id: chart

                Layout.fillWidth: true
                Layout.fillHeight: true
                anchors.fill:parent.fill

                antialiasing: true


                ValueAxis
                {
                    id: axisY
                    titleText:"Temperature [&deg;C]"
                }

                ValueAxis
                {
                    id: axisX
                    titleText:"Time [s]"
                }

                LineSeries {
                    name: "Temperature"

                    axisX: axisX
                    axisY: axisY

                    XYPoint { x: 0; y: 0 }
                    XYPoint { x: 1.1; y: 2.1 }
                    XYPoint { x: 1.9; y: 3.3 }
                    XYPoint { x: 2.1; y: 2.1 }
                    XYPoint { x: 2.9; y: 4.9 }
                    XYPoint { x: 3.4; y: 3.0 }
                    XYPoint { x: 4.1; y: 3.3 }
                }
            }

            RowLayout
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                Button
                {
                    id: reset_chart
                    text: "Reset"
                    font: defFont
                }

                Button
                {
                    id: save_chart
                    text: "Save"
                    font: defFont
                }

                Button
                {
                    id: mode_select
                    text: "Automatic"
                    font: defFont
                }
            }
        }
    }

}
