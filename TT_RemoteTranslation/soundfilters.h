#ifndef SOUNDFILTERS_H
#define SOUNDFILTERS_H

#include <QDialog>

namespace Ui {
class SoundFilters;
}

class SoundFilters : public QDialog
{
    Q_OBJECT
    
public:
    explicit SoundFilters(QWidget *parent = 0);
    ~SoundFilters();
    
private:
    Ui::SoundFilters *ui;
};

#endif // SOUNDFILTERS_H
