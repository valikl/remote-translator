#ifndef SOUNDDEVICES_H
#define SOUNDDEVICES_H

#include "BBTT/BB_Translator.h"
#include <QDialog>
#include <vector>

using namespace std;

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
    vector<BB_SoundDevice> m_soundDevList;
    void setSystemDevice();
    void drawDevices();
};

#endif // SOUNDDEVICES_H
