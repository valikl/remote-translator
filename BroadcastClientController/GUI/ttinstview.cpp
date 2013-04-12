#include "ttinstview.h"
#include <QtGui>

#define GRID(layout) ((QGridLayout*)(layout))

TTInstView::TTInstView(QString iname, QWidget *parent) :
    QWidget(parent)
{
    createNameLabel(iname);
    createStatus();
    createSoundBar();
    createChangeButton();

    setLayout();
}

void TTInstView::createNameLabel(QString name)
{
    nameLabel = new QLabel;
    nameLabel->setText(name);

    QFont font;
    font.setBold(true);
    nameLabel->setFont(font);
}

void TTInstView::createStatus()
{
    statusLabel = new QLabel;
    statusLabel->setText("Status:");

    statusState = new QLabel;
    statusState->setText("OK");

    statusResolve = new QPushButton;
    statusResolve->setFixedSize(45, 30);
    statusResolve->setText("Resolve");
}

void TTInstView::createChangeButton()
{
    changeButton = new QPushButton;

    changeButton->setFixedSize(90, 45);
    changeButton->setText("Change settings");
}

void TTInstView::createSoundBar()
{
    soundLabel = new QLabel;
    soundLabel->setText("Sound Level");

    soundBar = new QProgressBar;
    soundBar->setMinimumWidth(200);
}

QGroupBox* TTInstView::getStatusWidget()
{
    QGroupBox* status_box = new QGroupBox;
    status_box->setStyleSheet("QGroupBox { border-style: inset; border-width: 0px; }");
    status_box->setMaximumWidth(120);

    QHBoxLayout* status_layout = new QHBoxLayout;
    status_layout->setSpacing(10);
    status_layout->setMargin(0);
    status_layout->addWidget(statusLabel);
    status_layout->addWidget(statusState);
    status_layout->addWidget(statusResolve);

    status_box->setLayout(status_layout);
    return status_box;
}

QGroupBox* TTInstView::getSoundBarWidget()
{
    QGroupBox* sound_box = new QGroupBox;
    sound_box->setStyleSheet("QGroupBox { border-style: inset; border-width: 0px; }");
    sound_box->setMaximumWidth(250);

    QHBoxLayout* sound_layout = new QHBoxLayout;
    sound_layout->setSpacing(10);
    sound_layout->setMargin(0);
    sound_layout->addWidget(soundLabel);
    sound_layout->addWidget(soundBar);

    sound_box->setLayout(sound_layout);
    return sound_box;
}

void TTInstView::setLayout()
{
    layout = new QGridLayout;

    GRID(layout)->addWidget(nameLabel, 0, 0);

    QGroupBox* status_box = getStatusWidget();
    GRID(layout)->addWidget(status_box, 1, 0);

    QGroupBox* sound_box = getSoundBarWidget();
    GRID(layout)->addWidget(sound_box, 2, 0);

    GRID(layout)->addWidget(changeButton, 3, 0);

    QWidget::setLayout(layout);
}
