#ifndef INSTSETTINGS_H
#define INSTSETTINGS_H

#include "BBTT/BB_ConfigMgr.h"
#include <QDialog>

class QGroupBox;
class QLayout;

class InstSettings : public QDialog
{
    Q_OBJECT
public:
    explicit InstSettings(QWidget *parent = 0);

private:
    void createInstsSettings();
    void createGroupInstsSettings(GroupType type, QString box_name, QGroupBox*& inst_group);
    void setLayout();

    QGroupBox *sourcesGroup;
    QGroupBox *receiversGroup;
    QGroupBox *restrictedGroup;
    QLayout *layout;

signals:
    
public slots:
    
};

#endif // GROUPSETTINGS_H
