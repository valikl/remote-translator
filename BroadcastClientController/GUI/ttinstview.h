#ifndef TTINSTVIEW_H
#define TTINSTVIEW_H

#include "BBTT/BB_ConfigMgr.h"
#include "iinststatus.h"
#include <QWidget>

class QLabel;
class QPushButton;
class QProgressBar;
class QLayout;
class QGroupBox;

class TTInstView : public QWidget, public IInstStatus
{
    Q_OBJECT
public:
    explicit TTInstView(QString iname, QWidget *parent = 0);
    QString getName() { return name; }
    virtual void setError();

signals:
    
public slots:
    void changeSettings();

private:

    virtual void init() = 0;
    virtual GroupType getType() = 0;

    void drawNameLabel(QString name);
    void drawChangeButton();
    void drawStatus();
    void drawSoundBar();

    QGroupBox* getStatusWidget();
    QGroupBox* getSoundBarWidget();

    void setLayout();

    QString name;               // instance name

    QLabel* nameLabel;          // instance lable

    QLabel* statusLabel;        // status lable
    QLabel* statusState;        // status state
    QPushButton* statusResolve; // resolve status button

    QLabel* soundLabel;         // sound label
    QProgressBar* soundBar;     // sound progress bar

    QPushButton* changeButton;  // change settings

    QLayout *layout;

private slots:

};

class TTInstViewSource : public TTInstView
{
public:
    TTInstViewSource(QString iname, GroupType itype, QWidget *parent = 0) : TTInstView(iname, parent), type(itype)
    {
        init();
    }
    GroupType getType() { return type; }

private:
    void init();
    GroupType type;             // instance group type
};

class TTInstViewReceiver : public TTInstView
{
public:
    TTInstViewReceiver(QString iname, QWidget *parent = 0) : TTInstView(iname, parent)
    {
        init();
    }
    GroupType getType() { return GROUP_TYPE_RECEIVERS; }

private:
    void init();
};

#endif // TTINSTVIEW_H
