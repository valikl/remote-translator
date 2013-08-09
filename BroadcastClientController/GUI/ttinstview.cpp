#include "ttinstview.h"
#include "audiosettings.h"
#include "common_gui.h"

void TTInstView::setError(int errcode)
{
    code = (InstErrCode)errcode;
    QString  type = getType() == GROUP_TYPE_SOURCES ?
                "SOURCES " : getType() == GROUP_TYPE_RECEIVERS ? "RECEIVERS " : "RESTRICTED ";
    QString errstr = type + name + ": ";

    switch(code)
    {
    case INST_ERR_NONE:
        emit warning("");
        break;
    case INST_ERR_DENOISING:
        errstr += "Denoising error";
        emit error(errstr);
        break;
    case INST_ERR_ECHO_CANCEL:
        errstr += "Echo cancellation error";
        emit error(errstr);
        break;
    case INST_ERR_VOICE_ACTIVE:
        errstr += "Voice activation error";
        emit error(errstr);
        break;
    case INST_ERR_AGC:
        errstr += "AGC error";
        emit error(errstr);
        break;
    case INST_ERR_VOICE_USER:
        errstr += "User error";
        emit error(errstr);
        break;
    case INST_ERR_VOL_LEVEL:
        errstr += "Volume level error";
        emit error(errstr);
        break;
    case INST_ERR_TRANSMIT_ENABLED:
        errstr += "Transmit enabled error";
        emit error(errstr);
        break;
    case INST_ERR_INST_NOT_FOUND:
        errstr += "Instance not found";
        emit error(errstr);
        break;
    case INST_ERR_USER_NOT_FOUND:
        errstr += "User not found";
        emit error(errstr);
        break;
    case INST_ERR_FIXED_DENOISING:
        errstr += "Denoising error fixed";
        emit warning(errstr);
        break;
    case INST_ERR_FIXED_ECHO_CANCEL:
        errstr += "Echo cancellation error fixed";
        emit warning(errstr);
        break;
    case INST_ERR_FIXED_VOICE_ACTIVE:
        errstr += "Voice activation error fixed";
        emit warning(errstr);
        break;
    case INST_ERR_FIXED_AGC:
        errstr += "AGC error fixed";
        emit warning(errstr);
        break;
    case INST_ERR_FIXED_VOICE_USER:
        errstr += "User error fixed";
        emit warning(errstr);
        break;
    case INST_ERR_FIXED_VOL_LEVEL:
        errstr += "Volume level error fixed";
        emit warning(errstr);
        break;
    case INST_ERR_FIXED_TRANSMIT_ENABLED:
        errstr += "Transmit enabled error fixed";
        emit warning(errstr);
        break;
    default:
        errstr += "Unknown error";
        emit error(errstr);
        break;
    }
}

void TTInstView::catchWarning(QString msg)
{
    statusState->setText("OK");
    statusState->setStyleSheet("QLabel { background-color : none; }");
}

void TTInstView::catchError(QString msg)
{
    statusState->setText("Error");
    statusState->setStyleSheet("QLabel { background-color : red; }");
    if (code == INST_ERR_INST_NOT_FOUND || code == INST_ERR_USER_NOT_FOUND)
        reconnect();
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
    TRY_FUNC_WITH_RETURN(initAudio());
}

void TTInstView::createStatus()
{
    statusLabel = new QLabel;
    statusLabel->setText("Status:");

    statusState = new QLabel;
    statusState->setText("OK");
    statusState->setStyleSheet("QLabel { background-color : none; }");

    QObject::connect(this, SIGNAL(warning(QString)), this, SLOT(catchWarning(QString)));
    QObject::connect(this, SIGNAL(error(QString)), this, SLOT(catchError(QString)));
}

void TTInstView::createChangeButton()
{
    changeButton = new QPushButton;
    changeButton->setFixedSize(90, 45);
    changeButton->setText("Change settings");

    QObject::connect(changeButton, SIGNAL(clicked()), this, SLOT(changeSettings()));
}

void TTInstView::changeSettings()
{
    AudioSettings audio_settings(getName(), getType(), this);
    audio_settings.exec();
}

void TTInstView::createReconnectButton()
{
    reconnectButton = new QPushButton;
    reconnectButton->setFixedSize(60, 45);
    reconnectButton->setText("Reconnect");

    QObject::connect(reconnectButton, SIGNAL(clicked()), this, SLOT(reconnect()));
}

QGroupBox* TTInstView::getStatusWidget()
{
    QGroupBox* status_box = new QGroupBox;
    status_box->setStyleSheet("QGroupBox { border-style: inset; border-width: 0px; }");
    status_box->setMaximumWidth(150);

    QHBoxLayout* status_layout = new QHBoxLayout;
    status_layout->setSpacing(10);
    status_layout->setMargin(0);
    status_layout->addWidget(statusLabel);
    status_layout->addWidget(statusState);
    status_layout->addWidget(reconnectButton);

    status_box->setLayout(status_layout);
    return status_box;
}

void TTInstViewSource::setLayout()
{
    createNameLabel(getName());
    createStatus();
    createChangeButton();
    createReconnectButton();
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
    wstring wname = getName().toStdWString();
    BB_GroupElementConfig config = ConfigMgr.GetGroupElementConfig(getType(), wname);

    BB_GroupMgrSource& mgr = getType() == GROUP_TYPE_SOURCES ? SourcesMgr : RestrictedMgr;
    TRY_FUNC_WITH_RETURN(mgr.AddInstance(wname, config.m_InputSoundDevId, config.m_OutputSoundDevId, this));

    TRY_FUNC_WITH_RETURN(mgr.EnableDenoising(wname, config.m_noiseCancel));
    TRY_FUNC_WITH_RETURN(mgr.EnableEchoCancellation(wname, config.m_echoCancel));
    TRY_FUNC_WITH_RETURN(mgr.EnableVoiceActivation(wname, config.m_EnableVoiceActivation));
    TRY_FUNC_WITH_RETURN(mgr.SetAGCEnable(wname, config.m_AGC.m_enable, &(config.m_AGC)));
    TRY_FUNC_WITH_RETURN(mgr.UpdateMicrophoneGainLevel(wname, config.m_MicGainLevel));

    //Timer for micophone progress bar
    microphone_timer = new QTimer(this);
    connect(microphone_timer, SIGNAL(timeout()), this, SLOT(on_MicrophoneTimeout()));
    microphone_timer->start(100);
}

void TTInstViewSource::reconnect()
{
    microphone_timer->stop();
    wstring wname = getName().toStdWString();
    BB_GroupMgrSource& mgr = getType() == GROUP_TYPE_SOURCES ? SourcesMgr : RestrictedMgr;
    TRY_FUNC_WITH_RETURN(mgr.RemoveInstance(wname));
    TRY_FUNC_WITH_RETURN(initAudio());
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
    createReconnectButton();
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
    TRY_FUNC_WITH_RETURN(ReceiversMgr.AddInstance(wname, config.m_InputSoundDevId, config.m_OutputSoundDevId, this));
    TRY_FUNC_WITH_RETURN(ReceiversMgr.UpdateVolumeLevel(wname, config.m_SrcVolumeLevel));
}

void TTInstViewReceiver::reconnect()
{
    wstring wname = getName().toStdWString();
    TRY_FUNC_WITH_RETURN(ReceiversMgr.RemoveInstance(wname));
    TRY_FUNC_WITH_RETURN(initAudio());
}
