#ifndef INSTSETTINGS_H
#define INSTSETTINGS_H

#include "BBTT/BB_ConfigMgr.h"
#include <QDialog>

class QGroupBox;
class QDialogButtonBox;
class QLayout;

typedef std::map<QString, void*> InstDetailMap;
typedef std::map<std::wstring, InstDetailMap> InstsDetailMap;

class InstSettings : public QDialog
{
    Q_OBJECT
public:
    explicit InstSettings(QWidget *parent = 0);

private:
    void createInstsSettings();
    void createGroupInstsSettings(GroupType type, QString box_name, QGroupBox*& inst_group);
    void createSaveButton();
    void setLayout();

    bool saveGroupInstsDetails(GroupType type);

    QGroupBox *sourcesGroup;
    QGroupBox *receiversGroup;
    QGroupBox *restrictedGroup;
    QDialogButtonBox* saveButton;
    QLayout *layout;

    std::map<GroupType, InstsDetailMap> detail_map;

signals:
    
public slots:
    
    void saveDetails();
};

#endif // GROUPSETTINGS_H
