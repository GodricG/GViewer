#ifndef GMESH_H
#define GMESH_H
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/io/io.h>
#include <pcl/io/vtk_lib_io.h>

#include <iostream>

class gmesh
{
public:
    explicit gmesh(std::string pcdpath);
    ~gmesh();

    int mesh();


private:
    std::string pcdPath;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;

    pcl::PointCloud<pcl::Normal>::Ptr normals;
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree;
    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals;
    pcl::search::KdTree<pcl::PointNormal>::Ptr tree2;
    pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
};

#endif // GMESH_H
