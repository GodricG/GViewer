cmake_minimum_required(VERSION 3.5)

project(gviewer)



# init_qt: Let's do the CMake job for us
set(CMAKE_AUTOMOC ON) # For meta object compiler
set(CMAKE_AUTORCC ON) # Resource files
set(CMAKE_AUTOUIC ON) # UI files
set(PCL_DIR /Apps/PCL191/share/pcl-1.9)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(DELTA_2B_LIDAR_SDK_PATH "./src/")

FILE(GLOB DELTA_2B_LIDAR_SDK_SRC
  "${DELTA_2B_LIDAR_SDK_PATH}/src/*.cpp"
)

include_directories(
  ${DELTA_2B_LIDAR_SDK_PATH}/include
  ${DELTA_2B_LIDAR_SDK_PATH}/src
)
find_package(Boost 1.65 REQUIRED)
# Find the QtWidgets library
find_package(Qt5 REQUIRED Widgets)

find_package(VTK REQUIRED)
find_package(PCL 1.9.1 REQUIRED)

# Fix a compilation bug under ubuntu 16.04 (Xenial)
list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4")

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


add_executable(gviewer main.cpp gviewer.cpp gviewer.h gviewer.ui radar.cpp radar.h gmesh.cpp gmesh.h ${DELTA_2B_LIDAR_SDK_SRC})


target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} -lboost_system -lboost_thread -lpthread -lrt)

qt5_use_modules(${PROJECT_NAME} Widgets)
