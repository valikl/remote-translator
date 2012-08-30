#ifndef SOUNDDEVICES_H
#define SOUNDDEVICES_H

#include <QDialog>

namespace Ui {
class SoundDevices;
}

class SoundDevices : public QDialog
{
    Q_OBJECT
    
public:
    explicit SoundDevices(QWidget *parent = 0);
    ~SoundDevices();
    
private:
    Ui::SoundDevices *ui;
};

#endif // SOUNDDEVICES_H
