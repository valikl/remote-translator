#include "audiosettings.h"
#include "instsettings.h"
#include "common_gui.h"
#include "TT_Include/TeamTalk4.h"

AudioSettings::AudioSettings(QString iname, GroupType itype, QWidget *parent) :
    QDialog(parent), name(iname), type(itype)
{
    setLayout();
}

void AudioSettings::setLayout()
{
    layout = new QGridLayout;

    iview = new InstSettingsView(name, type);

    saveButton = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(saveButton, SIGNAL(accepted()), this, SLOT(saveDetails()));
    connect(saveButton, SIGNAL(rejected()), this, SLOT(reject()));

    GRID(layout)->addWidget(iview, 0, 0);
    GRID(layout)->addWidget(saveButton, 1, 0);

    QWidget::setLayout(layout);
}

void AudioSettings::saveDetails()
{
    if (iview->saveDetails())
        ConfigMgr.saveConfig();
    accept();
}
