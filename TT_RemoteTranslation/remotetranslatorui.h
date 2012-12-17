#ifndef REMOTETRANSLATORUI_H
#define REMOTETRANSLATORUI_H

#include "common.h"
#include "BBTT/BB_Translator.h"

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>

#include <QMainWindow>

#define ConfigUI (BB_ClientConfigMgr::Instance().getConfig())
#define TRANSLATOR (BB_Translator::Instance())

using namespace std;

namespace Ui {
class RemoteTranslatorUI;
}

class RemoteTranslatorUI : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit RemoteTranslatorUI(QWidget *parent = 0);
    ~RemoteTranslatorUI();

    void init();
    void enableAudioFilters();

public slots:

    void changeMainConfig();
    
private slots:

    void on_NickName_editingFinished();

    // happa\ening slots
    void on_HapList_currentIndexChanged(const QString &arg1);

    // source/target language slots
    void on_SrcLangList_currentIndexChanged(const QString &arg1);
    void on_TrgLangList_currentIndexChanged(const QString &arg1);
    void on_LangConnect_clicked(bool checked);

    void on_MicGainSld_valueChanged(int val);
    void on_MicMuteBut_clicked(bool checked);
    void on_TrgMuteBut_clicked(bool checked);
    void on_TrgLvlSld_valueChanged(int val);
    void on_SrcLevelSld_valueChanged(int val);
    void on_VideoLvlSld_valueChanged(int val);

    void on_Timeout();
    void on_UserTimeout();

    void ActivateSoundDevices();
    void ActivateAudioFilters();
    void ActivateManConnect();
    void RestoreDefaultConfig();

    void on_LocalSelfTestEn_stateChanged(int checked);
    void on_ServerSelfTestEn_stateChanged(int checked);

    void on_showVideoButton_clicked(bool clicked);

private:

    void initMainConfig();
    void initTranslator();
    void activateButtons();

    void initHapsMenu();
    void setSliders();
    void setUserItems(bool is_source);

    void connectTranslator();
    void disconnectTranslator();
    void activateSliders();

    std::vector<Happening> happenings;

    Ui::RemoteTranslatorUI *ui;
    QTimer *timer;
    QTimer *user_timer;
};

#endif // REMOTETRANSLATORUI_H
