#ifndef GROUPSETTINGS_H
#define GROUPSETTINGS_H

#include "BBTT/BB_ConfigMgr.h"
#include <QDialog>

class QGroupBox;
class QDialogButtonBox;
class QLineEdit;
class QLayout;

typedef std::map<QString, QLineEdit*> GroupDetailMap;

class GroupSettings : public QDialog
{
    Q_OBJECT
public:
    explicit GroupSettings(QWidget *parent = 0);

private:
    void createGroupsSettings();
    void createGroupSettings(GroupType type, QString box_name, QGroupBox*& inst_group);
    void createSaveButton();
    void setLayout();
    bool saveGroupDetails(GroupType type);

    QGroupBox* sourcesGroup;
    QGroupBox* receiversGroup;
    QGroupBox* restrictedGroup;
    QDialogButtonBox* saveButton;
    QLayout* layout;

    std::map<GroupType, GroupDetailMap> detail_map;

signals:
    
public slots:

    void saveDetails();
};

#endif // GROUPSETTINGS_H
