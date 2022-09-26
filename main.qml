import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts 2.15
import QtQuick.Controls 2.15

import ru.gb.ChartDataSource 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Homework 4 part 1")

    ChartDataSource {
        id: chartDataSource
        parameter_name: qsTr("синусоиды")

        onYGettingWayChanged: {

            for (var i = 0; i < chartDataSource.getPointersSize(); i++)
            {
                lineSeries.replace(i, chartDataSource.getX(i), chartDataSource.getY(i));
            }
        }

        onParameterNameChanged: {
            lineSeries.name = chartDataSource.parameter_name
        }
    }

    ValueAxis{
        id: valueAxisX
        min: 0.0
        max: 5.0
        }
    ValueAxis{
        id: valueAxisY
        min: -5.0
        max: 5.0
    }

    ChartView {
        title: qsTr("График (кликни для смены)")
        anchors.fill: parent
        antialiasing: true
        LineSeries {
            id: lineSeries
            name: qsTr(chartDataSource.parameter_name)
            color: chartDataSource.color
            axisX: valueAxisX
            axisY: valueAxisY

            Component.onCompleted: {
                for (var i = 0; i < chartDataSource.getPointersSize(); i++)
                {
                    lineSeries.append(chartDataSource.getX(i), chartDataSource.getY(i));
                }
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                chartDataSource.color = '#' + (0x1000000 + Math.random() * 0xFFFFFF).toString(16).substr(1,6)
                chartDataSource.changeYGettingWay();
            }
        }
    }
}
