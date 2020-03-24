#ifndef GVIEWER_H
#define GVIEWER_H

#include <QDebug>

#include <iostream>
#include <string>
#include <boost/thread.hpp>

// Qt
#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QSlider>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>

// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/smart_ptr.hpp>
#include <pcl/io/pcd_io.h>

//Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>

//DELTA_2B_LIDAR_SDK
#include "C3iroboticsLidar.h"
#include "CSerialConnection.h"

//radar
#include "radar.h"

//mesh
#include "gmesh.h"

typedef pcl::PointCloud<pcl::PointXYZ> CloudT;
typedef pcl::visualization::PCLVisualizer ViewerT;
using namespace std;
using namespace everest::hwdrivers;
QT_BEGIN_NAMESPACE
namespace Ui { class GViewer; }
QT_END_NAMESPACE

class GViewer : public QMainWindow
{
    Q_OBJECT

public:
    GViewer(QWidget *parent = 0);
    ~GViewer();
protected:
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void lcdShow(int theValue);
    void showClouds(bool);
    void receiveUpdateRequest(CloudT::Ptr thecloud, int roundCount);
signals:
    void cancelRequest();

private slots:
    void on_CtrlBtn_clicked();
    void on_StopBtn_clicked();
    void initParas();
    void updateStatus(QString str, int roundCount);

    void on_MeshBtn_clicked();

private:
    Ui::GViewer *ui;
    CloudT::Ptr cloud;

    ViewerT::Ptr viewer;
    boost::shared_ptr<QTimer> timer;
    boost::shared_ptr<radar> radarClass;
    boost::atomic<bool> ifInit;
};
#endif // GVIEWER_H
