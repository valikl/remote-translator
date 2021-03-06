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
    void createReconnectButton();
    void createStatus();
    void showStatusState(bool is_ok);
    QGroupBox* getStatusWidget();
    QLabel* statusState;            // status state
    bool is_connected;

    void init();
    virtual void setLayout() = 0;
    virtual void initAudio() = 0;

    virtual void setError(int errcode);

signals:
    void fatal_error(QString errstr);
    void error(QString errstr);
    void warning(QString errstr);

public slots:
    void changeSettings();
    virtual void reconnect() = 0;

private:

    QString name;                   // instance name
    QLabel* nameLabel;              // instance label
    QLabel* statusLabel;            // status lable
    QPushButton* reconnectButton;   // reconnect button
    QPushButton* changeButton;      // change settings
    InstErrCode errcode;

private slots:
    void catchWarning(QString msg);
    void catchError(QString msg);

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

public slots:
    virtual void reconnect();
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

public slots:
    virtual void reconnect();

private:

    QLayout *layout;
};

#endif // TTINSTVIEW_H
