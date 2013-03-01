#ifndef BROADCASTCONTROLLER_H
#define BROADCASTCONTROLLER_H

#include <QMainWindow>

namespace Ui {
class BroadcastController;
}

class BroadcastController : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit BroadcastController(QWidget *parent = 0);
    ~BroadcastController();
    
private:
    Ui::BroadcastController *ui;
};

#endif // BROADCASTCONTROLLER_H
