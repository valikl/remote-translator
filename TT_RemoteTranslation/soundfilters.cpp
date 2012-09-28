#include "soundfilters.h"
#include "ui_soundfilters.h"

SoundFilters::SoundFilters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoundFilters)
{
    ui->setupUi(this);
}

SoundFilters::~SoundFilters()
{
    delete ui;
}
