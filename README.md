# GViewer
This project is for 3D-Modeling using 3irobotix radar, with pcl-1.9.1 and Qt5.14.1 as GUI.

# Basic functionality
## Clouds acquisition
Acquire point clouds from 3D radar.
## Clouds visualization
Visualize point clouds。
## Mesh generation
Load "Autosaved.pcd" file;
Mesh clouds by pcl::KdTree, pcl::NormalEstimation and pcl::GreedyProjectionTriangulation;
Save as "meshed.stl".
