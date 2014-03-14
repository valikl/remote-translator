#ifndef AUDIOSETTINGS_H
#define AUDIOSETTINGS_H

#include "BBTT/BB_ConfigMgr.h"
#include <QDialog>

class QDialogButtonBox;
class InstSettingsView;

class AudioSettings : public QDialog
{
    Q_OBJECT
public:
    explicit AudioSettings(QString iname, GroupType itype, QWidget *parent);

private:
    void setLayout();

    QString name;               // instance name
    GroupType type;             // instance group type
    InstSettingsView* iview;
    QDialogButtonBox* saveButton;
    QLayout* layout;

signals:
    
public slots:
    
    void saveDetails();
};

#endif // AUDIOSETTINGS_H
