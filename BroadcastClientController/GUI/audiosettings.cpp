#include "audiosettings.h"
#include "common_gui.h"
#include "TT_Include/TeamTalk4.h"

AudioSettings::AudioSettings(QWidget *parent) : QDialog(parent)
{
    volumeLabel = new QLabel;
    volumeSlider = new QSlider;
    gainLabel = new QLabel;
    gainSlider = new QSlider;

    int gainMax = 4000; /* real max: SOUND_LEVEL_MAX but it's too much */

    drawSlider(volumeSlider, volumeLabel, "volume level", SOUND_VOLUME_MIN, SOUND_VOLUME_MAX*(gainMax/SOUND_GAIN_DEFAULT), 0);
    drawSlider(gainSlider, gainLabel, "gain level", SOUND_GAIN_MIN, gainMax, 0);

    setLayout();
}

void AudioSettings::drawSlider(QSlider *slider, QLabel* label, QString name,
                               int min, int max, int val)
{
    label->setText(name);
    slider->setEnabled(true);
    slider->setRange(min, max);
    slider->setValue(val);
    slider->setOrientation(Qt::Horizontal);
}

void AudioSettings::setLayout()
{
    layout = new QGridLayout;

    GRID(layout)->addWidget(volumeLabel, 0, 0);
    GRID(layout)->addWidget(volumeSlider, 0, 1);
    GRID(layout)->addWidget(gainLabel, 1, 0);
    GRID(layout)->addWidget(gainSlider, 1, 1);

    QWidget::setLayout(layout);
}
