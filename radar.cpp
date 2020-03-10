#include "radar.h"

radar::radar(QObject *parant):QThread(parant)
{
    qRegisterMetaType<CloudT::Ptr>("CloudT::Ptr"); //Register custom type for connecting signal/slot
    isCancel = false;
    cloud.reset(new CloudT);
    serial_connect.setBaud(opt_com_baudrate); //setup baud rate
    serial_connect.setPort(opt_com_path.c_str()); //setup usb port
    ZdepthInner = 0;
    Zdepth = 1000;
    count = 0;
}

void radar::ZdepthChange(int theValue)
{
    Zdepth = theValue;
}

void radar::initializeRadar()
{
    cloud.reset(new CloudT);
    ZdepthInner = 0;
    Zdepth = 1000;
    count = 0;
}
void radar::cancelRun()
{
    isCancel = true;
}

void radar::run()
{
    isCancel = false;
    serial_connect.openSimple();
    robotics_lidar.initilize(&serial_connect);
    while(!isCancel)
    {
        result = robotics_lidar.getScanData();
        if(isCancel)
        {
            serial_connect.closeSerial();
            cloud->width = cloud->points.size();
            cloud->height = 1;
            cloud->points.resize(cloud->width * cloud->height);
            pcl::io::savePCDFileASCII("ScannedCloud.pcd", *cloud);
            break;

        }
        switch(result)
        {
            case LIDAR_GRAB_ING:
            {

                break;

            }
            case LIDAR_GRAB_SUCESS:
            {

                lidar_scan = robotics_lidar.getLidarScan();
                size_t lidar_scan_size = lidar_scan.getSize();
                std::vector<RslidarDataComplete> send_lidar_scan_data;
                send_lidar_scan_data.resize(lidar_scan_size);
                RslidarDataComplete one_lidar_data;
                for(size_t i = 0; i < lidar_scan_size; i++)
                {
                    one_lidar_data.signal = lidar_scan.signal[i];
                    one_lidar_data.angle = lidar_scan.angle[i];
                    one_lidar_data.distance = lidar_scan.distance[i];
                    send_lidar_scan_data[i] = one_lidar_data;
                    pcl::PointXYZ temp;
                    temp.x = send_lidar_scan_data[i].distance * sin(send_lidar_scan_data[i].angle*M_PI/180);
                    temp.y = send_lidar_scan_data[i].distance * cos(send_lidar_scan_data[i].angle*M_PI/180);
                    temp.z = ZdepthInner / 2000000.0;
                    cloud->points.push_back(temp);
                }
                std::cout << "Round: " << ZdepthInner <<", " << ZdepthInner % 1000<< std::endl;
                break;

            }
            case LIDAR_GRAB_ERRO:
            {
                //std::cout << "some error happened." << endl;
                break;

            }
            case LIDAR_GRAB_ELSE:
            {
                //cout << "[Main] LIDAR_GRAB_ELSE!\n" << endl;
                break;

            }
        }

        ZdepthInner++;
        count = ZdepthInner % 1000;
        if(count > Zdepth)
        {

            cloud->width = cloud->points.size();
            cloud->height = 1;
            cloud->points.resize(cloud->width * cloud->height);
            emit updateCloud(cloud, count/16);
            count = 0;
            ZdepthInner = count;
            //serial_connect.closeSerial();
            //break;
        }
    }
}
