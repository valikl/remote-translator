#ifndef MANCONNECT_H
#define MANCONNECT_H

#include <QDialog>

namespace Ui {
class ManConnect;
}

class ManConnect : public QDialog
{
    Q_OBJECT
    
public:
    explicit ManConnect(QWidget *parent = 0);
    ~ManConnect();

signals:
    void configChanged();

private slots:

    void on_ConnectAccept_accepted();

private:
    Ui::ManConnect *ui;
};

#endif // MANCONNECT_H
