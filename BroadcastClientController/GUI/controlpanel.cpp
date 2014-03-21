#include "controlpanel.h"
#include "ttinstview.h"
#include "groupsettings.h"
#include "instsettings.h"
#include "common_gui.h"
#include <vector>

using namespace std;

#define TRY_INIT(init) \
try \
{ \
    (init); \
} \
catch(BB_Exception excp) \
{ \
    fatal_errlist.push_back(getErrStr(excp)); \
}

QString getErrStr(BB_Exception excp)
{
    QDateTime current = QDateTime::currentDateTime();
    QString errstr = QString::fromStdWString(excp.GetInfo());
    QMessageBox::critical(NULL, "Error:", errstr);
    errstr = current.toString() + " " + errstr;
    return errstr;
}

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent)
{}

void ControlPanel::catchError(QString errstr)
{
    QDateTime current = QDateTime::currentDateTime();
    errstr = current.toString() + " " + errstr;
    msgConsole->appendPlainText(errstr);
}

void ControlPanel::catchFatalError(QString errstr)
{
    QDateTime current = QDateTime::currentDateTime();
    errstr = current.toString() + " " + errstr;
    errConsole->appendPlainText(errstr);
}

void ControlPanel::init()
{
    // Initialize configuration manager and group managers
    TRY_INIT(ConfigMgr.init(false));
    TRY_INIT(SourcesMgr.init());
    TRY_INIT(RestrictedMgr.init());
    TRY_INIT(ReceiversMgr.init());

    // Draw widget elements
    drawMenuBar();
    drawSources();
    drawReceivers();
    drawRestricted();
    drawErrConsole();
    drawMsgConsole();
    setLayout();
}

void ControlPanel::drawMenuBar()
{
    menuBar = new QMenuBar(this);

    QMenu* menu = new QMenu("Settings");
    QAction* groupAct = menu->addAction("Groups settings");
    QAction* instAct = menu->addAction("Instances settings");

    menuBar->addMenu(menu);
    menuBar->setMaximumHeight(20);

    QObject::connect(groupAct, SIGNAL(triggered()), this, SLOT(callGroupSettings()));
    QObject::connect(instAct, SIGNAL(triggered()), this, SLOT(callInstSettings()));
}

void ControlPanel::drawSources()
{
    drawInstancesBox(GROUP_TYPE_SOURCES, "Sources", sourcesGroup);
}

void ControlPanel::drawReceivers()
{
    drawInstancesBox(GROUP_TYPE_RECEIVERS, "Receivers", receiversGroup);
}

void ControlPanel::drawRestricted()
{
    drawInstancesBox(GROUP_TYPE_RESTRICTED_SERVERS, "Restricted", restrictedGroup);
}

void ControlPanel::drawInstancesBox(GroupType type, QString box_name, QGroupBox*& inst_group)
{
    inst_group = new QGroupBox(box_name);
    inst_group->setStyleSheet("QGroupBox { border-style: inset; border-width: 1px; }");
    inst_group->setFlat(true);

    QVBoxLayout* layout = new QVBoxLayout;

    BB_GroupConfig config = ConfigMgr.GetGroupConfig(type);
    map<std::wstring, BB_GroupElementConfig>::iterator it;
    for (it = config.m_groupList.begin(); it != config.m_groupList.end(); ++it)
    {
        TTInstView* iview;
        BB_GroupElementConfig& inst = it->second;
        QString iname = QString::fromStdWString(inst.m_name);
        if (type == GROUP_TYPE_RECEIVERS)
            iview = new TTInstViewReceiver(iname);
        else
            iview = new TTInstViewSource(iname, type);
        layout->addWidget(iview);

        connect(iview, SIGNAL(warning(QString)), this, SLOT(catchError(QString)));
        connect(iview, SIGNAL(error(QString)), this, SLOT(catchError(QString)));
        connect(iview, SIGNAL(fatal_error(QString)), this, SLOT(catchFatalError(QString)));
    }

    inst_group->setLayout(layout);
}

void ControlPanel::drawErrConsole()
{
    ErrorList::iterator it;
    errConsole = new QPlainTextEdit;
    for (it = fatal_errlist.begin(); it != fatal_errlist.end(); ++it)
        errConsole->appendPlainText(*it);
}

void ControlPanel::drawMsgConsole()
{
    ErrorList::iterator it;
    msgConsole = new QPlainTextEdit;
}

void ControlPanel::setLayout()
{
    layout = new QGridLayout;
    GRID(layout)->addWidget(menuBar, 0, 0);

    QGridLayout* groups_layout = new QGridLayout;
    groups_layout->setMargin(0);

    groups_layout->addWidget(sourcesGroup, 0, 0);
    groups_layout->addWidget(receiversGroup, 0, 1);
    groups_layout->addWidget(restrictedGroup, 0, 2);

    groups_layout->setAlignment(sourcesGroup, Qt::AlignTop);
    groups_layout->setAlignment(receiversGroup, Qt::AlignTop);
    groups_layout->setAlignment(restrictedGroup, Qt::AlignTop);

    groups_layout->setColumnStretch(0, 30);
    groups_layout->setColumnStretch(1, 30);
    groups_layout->setColumnStretch(2, 30);

    QGroupBox* groups_box = new QGroupBox;
    groups_box->setStyleSheet("QGroupBox { border-style: inset; border-width: 0px; }");
    groups_box->setLayout(groups_layout);

    QGridLayout* console_layout = new QGridLayout;
    console_layout->setMargin(0);
    console_layout->addWidget(new QLabel("Permanent errors"), 0, 0);
    console_layout->addWidget(new QLabel("Fixed errors and warnings"), 0, 1);
    console_layout->addWidget(errConsole, 1, 0);
    console_layout->addWidget(msgConsole, 1, 1);

    QGroupBox* console_box = new QGroupBox;
    console_box->setStyleSheet("QGroupBox { border-style: inset; border-width: 0px; }");
    console_box->setLayout(console_layout);

    GRID(layout)->addWidget(groups_box, 1, 0);
    GRID(layout)->addWidget(console_box, 2, 0);

    QWidget::setLayout(layout);
}

void ControlPanel::callGroupSettings()
{
    GroupSettings group_settings(this);
    group_settings.exec();
}

void ControlPanel::callInstSettings()
{
    InstSettings inst_settings(this);
    inst_settings.exec();
}
