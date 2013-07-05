#include "ttinstview.h"
#include "audiosettings.h"
#include "common_gui.h"

void TTInstView::setError()
{
    statusState->setText("Error");
}

void TTInstView::setOK()
{
    statusState->setText("OK");
}

void TTInstView::createNameLabel(QString name)
{
    nameLabel = new QLabel;
    nameLabel->setText(name);

    QFont font;
    font.setBold(true);
    nameLabel->setFont(font);
}

void TTInstView::init()
{
    setLayout();
    initAudio();
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

    QObject::connect(changeButton, SIGNAL(clicked()), this, SLOT(changeSettings()));
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

void TTInstView::changeSettings()
{
    AudioSettings audio_settings(getName(), getType(), this);
    audio_settings.exec();
}

void TTInstViewSource::setLayout()
{
    createNameLabel(getName());
    createStatus();
    createChangeButton();
    createSoundBar();
    QGroupBox* status_box = getStatusWidget();
    QGroupBox* sound_box = getSoundBarWidget();

    layout = new QGridLayout;
    GRID(layout)->addWidget(getNameLabel(), 0, 0);
    GRID(layout)->addWidget(status_box, 1, 0);
    GRID(layout)->addWidget(sound_box, 2, 0);
    GRID(layout)->addWidget(getChangeButton(), 3, 0);

    QWidget::setLayout(layout);
}

void TTInstViewSource::initAudio()
{
    //Timer for micophone progress bar
    microphone_timer = new QTimer(this);
    connect(microphone_timer, SIGNAL(timeout()), this, SLOT(on_MicrophoneTimeout()));
    microphone_timer->start(100);

    wstring wname = getName().toStdWString();
    BB_GroupElementConfig config = ConfigMgr.GetGroupElementConfig(getType(), wname);

    BB_GroupMgrSource& mgr = getType() == GROUP_TYPE_SOURCES ? SourcesMgr : RestrictedMgr;
    mgr.AddInstance(wname, config.m_InputSoundDevId, config.m_OutputSoundDevId, this);

    TRY_FUNC_WITH_RETURN(mgr.EnableDenoising(wname, config.m_noiseCancel));
    TRY_FUNC_WITH_RETURN(mgr.EnableEchoCancellation(wname, config.m_echoCancel));
    TRY_FUNC_WITH_RETURN(mgr.EnableVoiceActivation(wname, config.m_EnableVoiceActivation));
    TRY_FUNC_WITH_RETURN(mgr.SetAGCEnable(wname, config.m_AGC.m_enable, &(config.m_AGC)));
    TRY_FUNC_WITH_RETURN(mgr.UpdateMicrophoneGainLevel(wname, config.m_MicGainLevel));
}

void TTInstViewSource::createSoundBar()
{
    soundLabel = new QLabel;
    soundLabel->setText("Sound Level");

    soundBar = new QProgressBar;
    soundBar->setMinimumWidth(200);
}

QGroupBox* TTInstViewSource::getSoundBarWidget()
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

void TTInstViewSource::on_MicrophoneTimeout()
{
    BB_GroupMgrSource& mgr = getType() == GROUP_TYPE_SOURCES ? SourcesMgr : RestrictedMgr;

    int level;
    wstring wname = getName().toStdWString();
    TRY_FUNC(level = mgr.GetMicrophoneGainLevel(wname));
    soundBar->setValue(level);
}

void TTInstViewReceiver::setLayout()
{
    createNameLabel(getName());
    createStatus();
    createChangeButton();
    QGroupBox* status_box = getStatusWidget();

    layout = new QGridLayout;
    GRID(layout)->addWidget(getNameLabel(), 0, 0);
    GRID(layout)->addWidget(status_box, 1, 0);
    GRID(layout)->addWidget(getChangeButton(), 2, 0);

    QWidget::setLayout(layout);
}

void TTInstViewReceiver::initAudio()
{
    wstring wname = getName().toStdWString();
    BB_GroupElementConfig config = ConfigMgr.GetGroupElementConfig(GROUP_TYPE_RECEIVERS, wname);
    ReceiversMgr.AddInstance(wname, config.m_InputSoundDevId, config.m_OutputSoundDevId, this);

    TRY_FUNC_WITH_RETURN(ReceiversMgr.UpdateVolumeLevel(wname, config.m_SrcVolumeLevel));
}
