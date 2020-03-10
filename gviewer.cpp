#include "gviewer.h"
#include "./ui_gviewer.h"



GViewer::GViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GViewer)
{
    ui->setupUi(this);
    this->setWindowTitle("3D Modeling");
    ui->ZCount->display(ui->ZSlider->value());
    ui->ZCount->setDigitCount(3);
    ifInit = true;
    radarClass.reset(new radar);

    connect(this, SIGNAL(cancelRequest()), radarClass.get(), SLOT(cancelRun()));
    connect(ui->ShowBtn, SIGNAL(clicked(bool)), this, SLOT(showClouds(bool)));
    connect(ui->ZSlider, SIGNAL(valueChanged(int)), this, SLOT(lcdShow(int)));
    connect(ui->ZSlider, SIGNAL(valueChanged(int)), radarClass.get(), SLOT(ZdepthChange(int)));
    connect(ui->InitBtn, SIGNAL(clicked(bool)), radarClass.get(), SLOT(initializeRadar()));
    connect(ui->InitBtn, SIGNAL(clicked(bool)), this, SLOT(initParas()));
    connect(radarClass.get(), SIGNAL(updateCloud(CloudT::Ptr, int)), this, SLOT(receiveUpdateRequest(CloudT::Ptr, int)));
    //Add one point(0,0,0) to prevent the ghosting when dragging the window
    pcl::PointXYZ tmp;
    tmp.x = 0;
    tmp.y = 0;
    tmp.z = 0;
    cloud.reset(new CloudT);
    viewer.reset(new ViewerT("3D Modeling Window", false));
    ui->gVTKWidget->SetRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(ui->gVTKWidget->GetInteractor(), ui->gVTKWidget->GetRenderWindow());
    cloud->points.push_back(tmp);
    viewer->addPointCloud(cloud);
    viewer->resetCamera();
}

GViewer::~GViewer()
{
    delete ui;
}

void GViewer::initParas()
{
    ifInit = true;
}
void GViewer::showClouds(bool)
{

    if(ifInit)
    {
        cloud.reset(new CloudT);
        pcl::io::loadPCDFile("Autosaved.pcd", *cloud);
        viewer.reset(new ViewerT("3D Modeling Window", false));
        ui->gVTKWidget->SetRenderWindow(viewer->getRenderWindow());
        viewer->setupInteractor(ui->gVTKWidget->GetInteractor(), ui->gVTKWidget->GetRenderWindow());
        viewer->addPointCloud(cloud);
        ifInit = false;
    }
    else{
        viewer->updatePointCloud(cloud);
    }
    ui->gVTKWidget->update();
    //viewer->resetCamera();

}

void GViewer::receiveUpdateRequest(CloudT::Ptr thecloud, int roundCount)
{
    std::cout << "width: " << thecloud->width <<", height: " << thecloud->height << std::endl;
    thecloud->points.resize(thecloud->width*thecloud->height);
    pcl::io::savePCDFileASCII("Autosaved.pcd", *thecloud);
    cloud = thecloud;
    emit ui->ShowBtn->clicked();
    emit this->updateStatus("Autosaved.pcd",roundCount);

}
void GViewer::updateStatus(QString str, int roundCount) //show status in QTextBrowser
{
    QString tmp = QString("PointCloud data file saved to: %1, datasize: %2, data acquisition round: %3\n").arg(str).arg(cloud->points.size()).arg(roundCount);
    ui->textStatus->setText(tmp);
}

void GViewer::resizeEvent(QResizeEvent *event) //QWidget resize event
{
    //viewer->resetCamera();
    //ui->gVTKWidget->update();
    qDebug() << this->width() << this->height();
}

void GViewer::lcdShow(int theValue) //show fresh rate
{
    ui->ZCount->display(theValue);

}

void GViewer::on_CtrlBtn_clicked()
{
    radarClass->start();
}

void GViewer::on_StopBtn_clicked()
{
    cancelRequest();
}
