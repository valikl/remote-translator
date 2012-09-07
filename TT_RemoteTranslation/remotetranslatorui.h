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
    int init();
    
private slots:

    void on_NickName_editingFinished();

    // happa\ening slots
    void on_HapList_currentIndexChanged(const QString &arg1);

    // source/target language slots
    void on_SrcLangList_currentIndexChanged(const QString &arg1);
    void on_TrgLangList_currentIndexChanged(const QString &arg1);
    void on_LangConnect_toggled(bool checked);

    void on_MicGainSld_valueChanged(int val);
    void on_MicMuteBut_clicked(bool checked);
    void on_TrgMuteBut_clicked(bool checked);
    void on_TrgLvlSld_valueChanged(int val);
    void on_SrcLevelSld_valueChanged(int val);


    void on_Timeout();
    void on_UserTimeout();

    void ActivateSoundDevices();

private:

    BB_Translator translator;
    std::vector<Happening> haps_from_mgr;

    Ui::RemoteTranslatorUI *ui;
    QTimer *timer;
    QTimer *user_timer;
};

#endif // REMOTETRANSLATORUI_H
