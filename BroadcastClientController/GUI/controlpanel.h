#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "BBTT/BB_ConfigMgr.h"
#include "iinststatus.h"
#include <QWidget>

class QMenuBar;
class QGroupBox;
class QLayout;
class QPlainTextEdit;

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = 0);
    void init();


private:
    void drawInstancesBox(GroupType type, QString box_name, QGroupBox*& inst_group);

    void drawMenuBar();
    void drawSources();
    void drawReceivers();
    void drawRestricted();
    void drawMsgConsole();

    void setLayout();

    QMenuBar *menuBar;
    QGroupBox *sourcesGroup;
    QGroupBox *receiversGroup;
    QGroupBox *restrictedGroup;

    QPlainTextEdit* msgConsole;

    QLayout *layout;

signals:
    
public slots:
    void callGroupSettings();
    void callInstSettings();
    void catchError(QString errstr);

};

#endif // CONTROLPANEL_H
