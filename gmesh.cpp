#include "gmesh.h"

gmesh::gmesh(std::string pcdpath):pcdPath(pcdpath)
{
    cloud.reset(new pcl::PointCloud<pcl::PointXYZ>);

    normals.reset(new pcl::PointCloud<pcl::Normal>);
    tree.reset(new pcl::search::KdTree<pcl::PointXYZ>);
    cloud_with_normals.reset(new pcl::PointCloud<pcl::PointNormal>);
    tree2.reset(new pcl::search::KdTree<pcl::PointNormal>);

}

gmesh::~gmesh()
{

}

int gmesh::mesh()
{
    pcl::io::loadPCDFile(pcdPath, *cloud);
    tree->setInputCloud (cloud);
    n.setInputCloud (cloud);
    n.setSearchMethod (tree);
    n.setKSearch (20);
    n.compute (*normals);
    pcl::concatenateFields (*cloud, *normals, *cloud_with_normals);
    tree2->setInputCloud (cloud_with_normals);
    pcl::PolygonMesh triangles;
    gp3.setSearchRadius (0.1);

    // Set typical values for the parameters
    gp3.setMu (2.5);
    gp3.setMaximumNearestNeighbors (100);
    gp3.setMaximumSurfaceAngle(M_PI/4); // 45 degrees
    gp3.setMinimumAngle(M_PI/18); // 10 degrees
    gp3.setMaximumAngle(2*M_PI/3); // 120 degrees
    gp3.setNormalConsistency(false);

    // Get result
    gp3.setInputCloud (cloud_with_normals);
    gp3.setSearchMethod (tree2);
    gp3.reconstruct (triangles);

    // Additional vertex information
    //std::vector<int> parts = gp3.getPartIDs();
    //std::vector<int> states = gp3.getPointStates();
    pcl::io::savePolygonFileSTL("meshed.stl", triangles, false);

    return 0;

}
