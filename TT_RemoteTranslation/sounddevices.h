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
    explicit SoundDevices(QWidget *parent, std::vector<BB_SoundDevice>& soundDevList);
    ~SoundDevices();
    
private slots:
    void on_DirectSoundButton_toggled(bool checked);

    void on_ActSDButton_accepted();

    void on_SelfTestButton_clicked(bool checked);

    void on_ActSDButton_rejected();

private:
    Ui::SoundDevices *ui;
    vector<BB_SoundDevice> m_soundDevList;
    BB_Translator* translator;

    void setSystemDevice();
    void drawDevices();
};

#endif // SOUNDDEVICES_H
