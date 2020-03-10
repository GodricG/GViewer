# Important

Files in this(project_root/src/) directory are sdk files for 3irobotix radar, do not modify any files only if you know what you are doing.

# Introduction

The simple way to get radar data is discribed below, and only two classes, C3iroboticsLidar and CSerialConnection, are related.

## class CDeviceConnection

This class is abstract class for radar connection, which cannot be used directly.

## class CSerialConnection

This class is inherited from CDeviceConnection and used to establish connection between PC and radar device. At least, the baud rate and usb port are needed. Then, simplely call function openSimple() to establish connection.

## class C3iroboticsLidar

This class is used after connection established. The instance of the class accepts reference of connection instance to finish initialization and gets ready to read data from stream by calling member function getScanData().
