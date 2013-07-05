#ifndef TTINSTVIEW_H
#define TTINSTVIEW_H

#include "BBTT/BB_ConfigMgr.h"
#include "iinststatus.h"
#include <QWidget>
#include <QPushButton>

class QLabel;
class QProgressBar;
class QLayout;
class QGroupBox;

class TTInstView : public QWidget, public IInstStatus
{
    Q_OBJECT
public:
    explicit TTInstView(QString iname, QWidget *parent = 0) :
        QWidget(parent), name(iname) {}
    QString getName() { return name; }
    QLabel* getNameLabel() { return nameLabel; }
    QPushButton* getChangeButton() { return changeButton; }
    virtual GroupType getType() = 0;

    // create widget components
    void createNameLabel(QString name);
    void createChangeButton();
    void createStatus();
    QGroupBox* getStatusWidget();

    void init();
    virtual void setLayout() = 0;
    virtual void initAudio() = 0;

    virtual void setError(int errcode);
    virtual void setOK();

signals:
    void ok();
    void error();

public slots:
    void changeSettings();

private:

    QString name;               // instance name
    QLabel* nameLabel;          // instance label
    QLabel* statusLabel;        // status lable
    QLabel* statusState;        // status state
    QPushButton* statusResolve; // resolve status button
    QPushButton* changeButton;  // change settings

private slots:
    void catchOK();
    void catchError();

};

class TTInstViewSource : public TTInstView
{
    Q_OBJECT
public:
    TTInstViewSource(QString iname, GroupType itype, QWidget *parent = 0) :
        TTInstView(iname, parent), type(itype) { init(); }
    virtual GroupType getType() { return type; }
    virtual void setLayout();
    virtual void initAudio();

private:
    void createSoundBar();
    QGroupBox* getSoundBarWidget();

    GroupType type;             // instance group type
    QTimer *microphone_timer;   // microphone timer
    QLabel* soundLabel;         // sound label
    QProgressBar* soundBar;     // sound progress bar
    QLayout *layout;

private slots:
    void on_MicrophoneTimeout();
};

class TTInstViewReceiver : public TTInstView
{
    Q_OBJECT
public:
    TTInstViewReceiver(QString iname, QWidget *parent = 0) :
        TTInstView(iname, parent) { init(); }
    virtual GroupType getType() { return GROUP_TYPE_RECEIVERS; }
    virtual void setLayout();
    virtual void initAudio();

private:

    QLayout *layout;
};

#endif // TTINSTVIEW_H
