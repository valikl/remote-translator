#include "controlpanel.h"
#include "ttinstview.h"
#include "groupsettings.h"
#include "instsettings.h"
#include "common_gui.h"
#include <vector>

using namespace std;

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent)
{}

void ControlPanel::init()
{
    ConfigMgr.init(false);

    SourcesMgr.init();
    RestrictedMgr.init();
    ReceiversMgr.init();

    drawMenuBar();

    drawSources();
    drawReceivers();
    drawRestricted();

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
        BB_GroupElementConfig& inst = it->second;
        QString iname = QString::fromStdWString(inst.m_name);
        TTInstView* iview = new TTInstView(iname);
        layout->addWidget(iview);
    }

    inst_group->setLayout(layout);
}

void ControlPanel::drawMsgConsole()
{
    msgConsole = new QPlainTextEdit;
}

void ControlPanel::setLayout()
{
    layout = new QGridLayout;
    GRID(layout)->addWidget(menuBar, 0, 0);

    QGroupBox* groups_box = new QGroupBox;
    groups_box->setStyleSheet("QGroupBox { border-style: inset; border-width: 0px; }");

    QGridLayout* groups_layout = new QGridLayout;
    groups_layout->setMargin(0);

    groups_layout->addWidget(sourcesGroup, 0, 0);
    groups_layout->addWidget(receiversGroup, 0, 1);
    groups_layout->addWidget(restrictedGroup, 0, 2);
    groups_layout->addWidget(msgConsole, 1, 0);

    groups_layout->setAlignment(sourcesGroup, Qt::AlignTop);
    groups_layout->setAlignment(receiversGroup, Qt::AlignTop);
    groups_layout->setAlignment(restrictedGroup, Qt::AlignTop);

    groups_layout->setColumnStretch(0, 30);
    groups_layout->setColumnStretch(1, 30);
    groups_layout->setColumnStretch(2, 30);
    groups_box->setLayout(groups_layout);

    GRID(layout)->addWidget(groups_box, 1, 0);
    GRID(layout)->addWidget(msgConsole, 2, 0);

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
