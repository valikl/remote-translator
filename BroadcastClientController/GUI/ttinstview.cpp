#include "ttinstview.h"
#include "audiosettings.h"
#include "common_gui.h"

TTInstView::TTInstView(QString iname, QWidget *parent) :
    QWidget(parent), name(iname)
{
    drawNameLabel(iname);
    drawStatus();
    drawSoundBar();
    drawChangeButton();

    setLayout();
}

void TTInstView::drawNameLabel(QString name)
{
    nameLabel = new QLabel;
    nameLabel->setText(name);

    QFont font;
    font.setBold(true);
    nameLabel->setFont(font);
}

void TTInstView::drawStatus()
{
    statusLabel = new QLabel;
    statusLabel->setText("Status:");

    statusState = new QLabel;
    statusState->setText("OK");

    statusResolve = new QPushButton;
    statusResolve->setFixedSize(45, 30);
    statusResolve->setText("Resolve");
}

void TTInstView::drawChangeButton()
{
    changeButton = new QPushButton;

    changeButton->setFixedSize(90, 45);
    changeButton->setText("Change settings");

    QObject::connect(changeButton, SIGNAL(clicked()), this, SLOT(changeSettings()));
}

void TTInstView::drawSoundBar()
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

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);

    GRID(layout)->addWidget(line);

    QWidget::setLayout(layout);
}

void TTInstView::changeSettings()
{
    AudioSettings audio_settings(this);
    audio_settings.exec();
}

void TTInstViewSource::init()
{
    wstring wname = getName().toStdWString();
    BB_GroupElementConfig config = ConfigMgr.GetGroupElementConfig(getType(), wname);

    BB_GroupMgrSource& mgr = getType() == GROUP_TYPE_SOURCES ? SourcesMgr : RestrictedMgr;
    mgr.AddInstance(wname, config.m_InputSoundDevId, config.m_OutputSoundDevId);

    TRY_FUNC_WITH_RETURN(mgr.EnableDenoising(wname, config.m_noiseCancel));
    TRY_FUNC_WITH_RETURN(mgr.EnableEchoCancellation(wname, config.m_echoCancel));
    TRY_FUNC_WITH_RETURN(mgr.EnableVoiceActivation(wname, config.m_EnableVoiceActivation));
    TRY_FUNC_WITH_RETURN(mgr.SetAGCEnable(wname, config.m_AGC.m_enable, &(config.m_AGC)));
}

void TTInstViewReceiver::init()
{
    wstring wname = getName().toStdWString();
    BB_GroupElementConfig config = ConfigMgr.GetGroupElementConfig(GROUP_TYPE_RECEIVERS, wname);
    ReceiversMgr.AddInstance(wname, config.m_InputSoundDevId, config.m_OutputSoundDevId);

    TRY_FUNC_WITH_RETURN(ReceiversMgr.UpdateVolumeLevel(wname, config.m_SrcVolumeLevel));
}
