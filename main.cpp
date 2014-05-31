#include "mainWindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("DSM tool");
    mainWindow w;
    w.show();
    
    return a.exec();
}
