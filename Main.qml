import QtQuick
import QtQuick.Layouts
import QtCharts
import QtQuick.Controls
import QtQuick.Dialogs

import qml.pid 1.0

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

                Connections
                {
                    target: term

                    function onGot_current_temperature(_temperature: float)
                    {
                        _temperature = Math.floor(_temperature);

                        temperature.text = _temperature + " °C";

                        var series = chart.series(0);

                        if( series.count === 0 )
                        {
                            chart.startTime = Date.now();
                        }

                        let timestamp = Date.now() - chart.startTime;

                        console.log("Timestamp: "+chart.startTime+" ms");
                        console.log("Timestamp: "+timestamp+" ms");

                        console.log(series);

                        if( series.count > 100000 )
                        {
                            chart.startTime = Date.now();
                            series.clear();
                        }

                        series.append(timestamp,_temperature);

                        axisX.max = timestamp;
                        axisX.min = series.at(0).x

                        chart.update();

                        chart.seriesAdded(series)

                        // series.replace(series.count - 1, timestamp, _temperature);

                        console.log("Series count: ",chart.series(0).count);
                    }
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

                Connections
                {
                    target: term

                    function onGot_power(_power: float)
                    {
                        power.text = Math.floor(_power) + " %";
                    }
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
                    to: 1000000
                    editable: true
                    font: defFont
                    value: common.pid.p
                }

                SpinBox
                {
                    id: integral
                    Layout.fillWidth: false
                    from: 0
                    to: 1000000
                    editable: true
                    font: defFont
                    value: common.pid.i

                }

                SpinBox
                {
                    id: differential
                    Layout.fillWidth: false
                    from: 0
                    to: 1000000
                    editable: true
                    font: defFont
                    value: common.pid.d
                }

                Connections
                {
                    id: dupa
                    target: term
                    function onGot_pid(pid: PID)
                    {
                        common.pid = pid;
                    }

                }
            }

            Button
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                id:set_pid
                text:"Set PID"
                font: defFont


                onClicked: function()
                {
                    serial.set_pid(common.pid)
                }
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

                    onClicked: serial.set_temperature(set_temperature_val.value)
                }
            }

            RowLayout
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                SpinBox
                {
                    id: set_power_val
                    // Layout.fillWidth: false
                    from: 0
                    to: 100
                    editable: true
                    font: defFont
                }

                Button
                {
                    id: set_power_button
                    text: "Set power"
                    font: defFont

                    onClicked: serial.set_power(set_power_val.value)
                }
            }

            RowLayout
            {
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                Button
                {
                    id: refresh_serial
                    text: "Refresh"
                    font: defFont

                    onClicked: serial.scan_for_serial()
                }

                Button
                {
                    id: connect_serial
                    text: "Connect"
                    font: defFont

                    onClicked: serial.connect_to_serial()
                }

                ComboBox {
                    currentIndex: 0
                    font: defFont

                    id: serial_select

                    model: ["1","2"]
                    width: 200

                    onCurrentIndexChanged: serial.serial_selected(serial_select.currentIndex)

                    Connections
                    {
                        target: serial
                        function onUpdateList(dev_list: list)
                        {
                            serial_select.model = dev_list
                        }
                    }

                }
            }

            RowLayout
            {
                id: serial_connection_status
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                Connections
                {
                    target: serial
                    function onSerialConnected()
                    {
                        serial_status.text = "Connected"
                        serial_status.color = "green"
                    }

                    function onSerialDisconnected()
                    {
                        serial_status.text = "Disconnected"
                        serial_status.color = "red"
                    }
                }

                Text {
                    text: "Status:"
                    font: defFont
                }

                Text {
                    id: serial_status

                    text: "Disconnected"
                    font: defFont
                    color: "red"
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

                property var startTime: Date.now();

                Layout.fillWidth: true
                Layout.fillHeight: true
                anchors.fill:parent.fill

                antialiasing: true

                ValueAxis
                {
                    id: axisY
                    min: 0
                    max: 500
                    titleText:"Temperature [&deg;C]"
                }

                ValueAxis
                {
                    id: axisX
                    min: 0
                    max: 5000000
                    titleText:"Time [ms]"
                }

                LineSeries {
                    name: "Temperature"

                    id: temperature_series

                    axisX: axisX
                    axisY: axisY

                    // XYPoint { x: 0; y: 0 }
                    // XYPoint { x: 10; y: 20 }
                }

            }

            MessageDialog {
                id: fileError
                title: "File error"
                text: "Cannot open file for saving!"
                onAccepted: {
                    visible = false
                }

                Connections
                {
                    target: chart_tool
                    onFileError: fileError.visible = true
                }

            }

            FileDialog {
                    id: fileDialog
                    // currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
                    nameFilters: ["CSV files (*.csv)"]
                    fileMode: FileDialog.SaveFile
                    onAccepted: function()
                    {
                        let fileName = fileDialog.selectedFile.toString().slice(7);

                        console.log("File: "+fileName);

                        let series = chart.series(0);

                        let text = "N,Time [ms],Temperature [°C]\n";

                        for(let i=0;i<series.count;i++)
                        {
                            let point = series.at(i);

                            text+=i+","+point.x+","+point.y+"\n";
                        }

                        chart_tool.saveToFile(text,fileName);
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

                    onClicked: function()
                    {
                        var series = chart.series(0);

                        series.clear();
                    }
                }

                Button
                {
                    id: save_chart
                    text: "Save"
                    font: defFont

                    onClicked: function()
                    {
                        fileDialog.visible = true
                    }
                }

                Button
                {
                    id: mode_select
                    text: "Automatic"
                    font: defFont

                    Connections
                    {
                        target: term

                        function onGot_mode(mode: bool)
                        {
                            if( mode )
                            {

                                mode_select.text = "Automatic"

                            }
                            else
                            {

                                mode_select.text = "Manual"

                            }

                        }
                    }
                }
            }
        }
    }

}
