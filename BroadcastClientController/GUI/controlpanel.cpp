#include "controlpanel.h"
#include "ttinstview.h"
#include <QtGui>

#define GRID(layout) ((QGridLayout*)(layout))

ControlPanel::ControlPanel(QWidget *parent) :
    QWidget(parent)
{
    createMenuBar();
    createSources();
    createReceivers();
    createRestricted();

    setLayout();
}

void ControlPanel::createMenuBar()
{
    menuBar = new QMenuBar(this);

    QMenu* menu1 = new QMenu("MENU1");
    menu1->addMenu(new QMenu("menu1_SubMenu1"));
    menu1->addMenu(new QMenu("menu1_SubMenu2"));

    QMenu* menu2 = new QMenu("MENU2");
    menu2->addMenu(new QMenu("menu2_SubMenu"));

    menuBar->addMenu(menu1);
    menuBar->addMenu(menu2);

    menuBar->setMaximumHeight(20);
}

void ControlPanel::createSources()
{
    createInstanceBox(5, sourcesGroup, "Sources");
}

void ControlPanel::createReceivers()
{
    createInstanceBox(3, receiversGroup, "Receivers");
}

void ControlPanel::createRestricted()
{
    createInstanceBox(4, restrictedGroup, "Restricted");
}

void ControlPanel::createInstanceBox(int num, QGroupBox*& inst_group, QString box_name)
{
    inst_group = new QGroupBox(box_name);

    QVBoxLayout* layout = new QVBoxLayout;

    for (int i = 0; i < num; ++i)
    {
        QString iname = "inst" + QString::number(i);
        TTInstView* iview = new TTInstView(iname);
        layout->addWidget(iview);
    }

    inst_group->setLayout(layout);
}

void ControlPanel::setLayout()
{
    layout = new QGridLayout;

    GRID(layout)->addWidget(menuBar, 0, 0);
    GRID(layout)->addWidget(sourcesGroup, 1, 0);
    GRID(layout)->addWidget(receiversGroup, 1, 1);
    GRID(layout)->addWidget(restrictedGroup, 1, 2);

    GRID(layout)->setAlignment(sourcesGroup, Qt::AlignTop);
    GRID(layout)->setAlignment(receiversGroup, Qt::AlignTop);
    GRID(layout)->setAlignment(restrictedGroup, Qt::AlignTop);

    GRID(layout)->setColumnStretch(0, 30);
    GRID(layout)->setColumnStretch(1, 30);
    GRID(layout)->setColumnStretch(2, 30);

    QWidget::setLayout(layout);
}
