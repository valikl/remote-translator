#include <QtGui/QApplication>
#include "remotetranslatorui.h"
#include "BBTT/Utils.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RemoteTranslatorUI w;

    w.init();
    w.show();
    
    return a.exec();
}
