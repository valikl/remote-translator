#ifndef GROUPSETTINGS_H
#define GROUPSETTINGS_H

#include "BBTT/BB_ConfigMgr.h"
#include <QDialog>

class QGroupBox;
class QLayout;

class GroupSettings : public QDialog
{
    Q_OBJECT
public:
    explicit GroupSettings(QWidget *parent = 0);

private:
    void createGroupsSettings();
    void createGroupSettings(GroupType type, QString box_name, QGroupBox*& inst_group);
    void setLayout();

    QGroupBox *sourcesGroup;
    QGroupBox *receiversGroup;
    QGroupBox *restrictedGroup;
    QLayout *layout;

signals:
    
public slots:
    
};

#endif // GROUPSETTINGS_H
