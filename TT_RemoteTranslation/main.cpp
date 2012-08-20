#include <QtGui/QApplication>
#include "remotetranslatorui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RemoteTranslatorUI w;
    w.show();
    
    return a.exec();
}
