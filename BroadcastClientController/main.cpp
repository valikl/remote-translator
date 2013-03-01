#include <QtGui/QApplication>
#include "broadcastcontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BroadcastController w;
    w.show();
    
    return a.exec();
}
