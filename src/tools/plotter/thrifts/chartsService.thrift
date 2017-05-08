struct Vector {
  1: list<double> content;
} (
  yarp.name = "yarp::sig::Vector"
  yarp.includefile="yarp/sig/Vector.h"
)

struct Series {
    1: string name;
    2: Vector x;
    3: Vector y;
}

struct Chart {
    1: string title;
    2: string xAxisTitle;
    3: string yAxisTitle;
    4: list<Series> series;
}

struct AxisInfo {
    1: string type = "auto";
    2: double minimum = 0;
    3: double maximum = 30;
}

struct RealTimeChartRequest {
    1: AxisInfo xAxis;
    2: AxisInfo yAxis;
}

struct RealTimeChartResponse {
    1: string id;
    2: string streamingPortName;
}

struct ChartSimpleInfo {
    1: string id;
    2: string title;
}

struct RealTimeStreamData {
    1: list<Series> newPoints;
}


service ChartsService {
    string plotBatchChart(1: Chart chart);
    RealTimeChartResponse plotRealTimeChart(1: Chart chart, 2: RealTimeChartRequest chartInfo);

    oneway void closeAllCharts();
    oneway void closeChart(1: string chartID);

    list<ChartSimpleInfo> listAllCharts();
}

