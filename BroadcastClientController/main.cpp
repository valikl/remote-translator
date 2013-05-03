#include <QtGui/QApplication>
#include <QMainWindow>
#include "GUI/controlpanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    ControlPanel panel;

    panel.init();

    window.setCentralWidget(&panel);
    window.show();

    return a.exec();
}
