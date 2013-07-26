#ifndef INSTSETTINGS_H
#define INSTSETTINGS_H

#include "BBTT/BB_ConfigMgr.h"
#include <QDialog>

class QGroupBox;
class QDialogButtonBox;
class QGridLayout;
class QLayout;

class BB_SoundDevice;

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

class InstSettingsView : public QWidget
{
    Q_OBJECT
public:
    explicit InstSettingsView(QString iname, GroupType itype, QWidget *parent = 0) :
        name(iname), type(itype)
    {
        setLayout();
    }

    QString getName() { return name; }
    GroupType getType() { return type; }
    InstDetailMap& getDetailMap() { return dmap; }
    bool saveDetails();

signals:

public slots:

private:
    void setLayout();

    QString name;               // instance name
    GroupType type;             // instance group type
    InstDetailMap dmap;
    QLayout *layout;

private slots:
    void changeDevices(bool is_win);
};

#endif // GROUPSETTINGS_H
