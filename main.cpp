#include "mainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("DSM tool");
    a.setApplicationVersion("1405.1");
    mainWindow w;
    w.show();
    
    return a.exec();
}
