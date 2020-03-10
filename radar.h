#ifndef RADAR_H
#define RADAR_H

#include <iostream>
#include <QThread>
#include <QMetaType>
#include "C3iroboticsLidar.h"
#include "CSerialConnection.h"
#include <boost/smart_ptr.hpp>
#include <boost/atomic.hpp>
//pcl
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/smart_ptr.hpp>
#include <pcl/io/pcd_io.h>

typedef pcl::PointCloud<pcl::PointXYZ> CloudT;
typedef pcl::visualization::PCLVisualizer ViewerT;
using namespace std;
using namespace everest::hwdrivers;

typedef struct _rslidar_data
{
    _rslidar_data()
    {
        signal = 0;
        angle = 0.0;
        distance = 0.0;
    }
    uint8_t signal;
    float   angle;
    float   distance;
} RslidarDataComplete;

class radar:public QThread
{
    Q_OBJECT
public:
    radar(QObject *parant = 0);
signals:
    void updateCloud(CloudT::Ptr thecloud, int roundCount);
    //void
public slots:
    void cancelRun();
    void initializeRadar();
    void ZdepthChange(int theValue);

protected:
    void run() override;
private:
    boost::atomic<bool> isCancel;
    CloudT::Ptr cloud;

    int Zdepth;
    int ZdepthInner;
    int count;
    int opt_com_baudrate = 230400;
    string opt_com_path = "/dev/ttyUSB0";

    CSerialConnection serial_connect;
    C3iroboticsLidar robotics_lidar;
    TLidarScan lidar_scan;
    TLidarGrabResult result;
};

#endif // RADAR_H
