#include <QtGui/QApplication>
#include "remotetranslatorui.h"
#include "BBTT/Utils.h"

int main(int argc, char *argv[])
{
    int ret = EXIT_SUCCESS;

    QApplication a(argc, argv);
    RemoteTranslatorUI w;

    CHECK_ret(w.init());
    w.show();
    
    return a.exec();
}
