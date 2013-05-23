#ifndef AUDIOSETTINGS_H
#define AUDIOSETTINGS_H

#include <QDialog>

class QLabel;
class QSlider;
class QGroupBox;

class AudioSettings : public QDialog
{
    Q_OBJECT
public:
    explicit AudioSettings(QWidget *parent);

private:
    void drawSlider(QSlider* slider, QLabel* label, QString name, int min, int max, int val);
    void setLayout();

    QLabel* volumeLabel;
    QLabel* gainLabel;
    QSlider* volumeSlider;
    QSlider* gainSlider;
    QLayout *layout;

signals:
    
public slots:
    
};

#endif // AUDIOSETTINGS_H
