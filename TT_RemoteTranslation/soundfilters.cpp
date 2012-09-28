#include "soundfilters.h"
#include "ui_soundfilters.h"

SoundFilters::SoundFilters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoundFilters)
{
    ui->setupUi(this);
    //Look for Min max at TT_SetAGCSettings function
//    ui->
}

SoundFilters::~SoundFilters()
{
    delete ui;
}

void SoundFilters::on_FiltersOK_accepted()
{
    int i = 123;
}
