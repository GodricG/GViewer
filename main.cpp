#include "gviewer.h"

#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GViewer w;
    w.show();
    return a.exec();
}
