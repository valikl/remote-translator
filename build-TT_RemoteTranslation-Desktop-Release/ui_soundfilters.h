/********************************************************************************
** Form generated from reading UI file 'soundfilters.ui'
**
** Created: Fri May 3 10:10:05 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOUNDFILTERS_H
#define UI_SOUNDFILTERS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SoundFilters
{
public:
    QDialogButtonBox *FiltersOK;
    QSpinBox *AGCGainLvl;
    QSpinBox *AGCIncLvl;
    QSpinBox *AGCDecLvl;
    QSpinBox *AGCMaxGain;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QCheckBox *AGCEn;
    QLabel *label_5;
    QSpinBox *VoiceActLvl;
    QLabel *label_6;
    QCheckBox *VoiceActEn;
    QCheckBox *EchoEn;
    QCheckBox *DenoiseEn;
    QLabel *label_7;
    QLabel *label_8;

    void setupUi(QDialog *SoundFilters)
    {
        if (SoundFilters->objectName().isEmpty())
            SoundFilters->setObjectName(QString::fromUtf8("SoundFilters"));
        SoundFilters->resize(400, 300);
        FiltersOK = new QDialogButtonBox(SoundFilters);
        FiltersOK->setObjectName(QString::fromUtf8("FiltersOK"));
        FiltersOK->setGeometry(QRect(30, 240, 341, 32));
        FiltersOK->setOrientation(Qt::Horizontal);
        FiltersOK->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        AGCGainLvl = new QSpinBox(SoundFilters);
        AGCGainLvl->setObjectName(QString::fromUtf8("AGCGainLvl"));
        AGCGainLvl->setGeometry(QRect(300, 40, 46, 22));
        AGCIncLvl = new QSpinBox(SoundFilters);
        AGCIncLvl->setObjectName(QString::fromUtf8("AGCIncLvl"));
        AGCIncLvl->setGeometry(QRect(300, 70, 46, 22));
        AGCDecLvl = new QSpinBox(SoundFilters);
        AGCDecLvl->setObjectName(QString::fromUtf8("AGCDecLvl"));
        AGCDecLvl->setGeometry(QRect(300, 100, 46, 22));
        AGCMaxGain = new QSpinBox(SoundFilters);
        AGCMaxGain->setObjectName(QString::fromUtf8("AGCMaxGain"));
        AGCMaxGain->setGeometry(QRect(300, 130, 46, 22));
        label = new QLabel(SoundFilters);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 40, 71, 20));
        label_2 = new QLabel(SoundFilters);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 70, 71, 20));
        label_3 = new QLabel(SoundFilters);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 100, 81, 20));
        label_4 = new QLabel(SoundFilters);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(210, 130, 71, 20));
        AGCEn = new QCheckBox(SoundFilters);
        AGCEn->setObjectName(QString::fromUtf8("AGCEn"));
        AGCEn->setGeometry(QRect(300, 160, 81, 18));
        label_5 = new QLabel(SoundFilters);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(210, 10, 121, 20));
        VoiceActLvl = new QSpinBox(SoundFilters);
        VoiceActLvl->setObjectName(QString::fromUtf8("VoiceActLvl"));
        VoiceActLvl->setGeometry(QRect(140, 40, 46, 22));
        label_6 = new QLabel(SoundFilters);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 40, 111, 20));
        VoiceActEn = new QCheckBox(SoundFilters);
        VoiceActEn->setObjectName(QString::fromUtf8("VoiceActEn"));
        VoiceActEn->setGeometry(QRect(140, 70, 81, 18));
        EchoEn = new QCheckBox(SoundFilters);
        EchoEn->setObjectName(QString::fromUtf8("EchoEn"));
        EchoEn->setGeometry(QRect(60, 200, 91, 18));
        DenoiseEn = new QCheckBox(SoundFilters);
        DenoiseEn->setObjectName(QString::fromUtf8("DenoiseEn"));
        DenoiseEn->setGeometry(QRect(60, 170, 71, 18));
        label_7 = new QLabel(SoundFilters);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 10, 161, 20));
        label_8 = new QLabel(SoundFilters);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(50, 130, 121, 20));

        retranslateUi(SoundFilters);
        QObject::connect(FiltersOK, SIGNAL(accepted()), SoundFilters, SLOT(accept()));
        QObject::connect(FiltersOK, SIGNAL(rejected()), SoundFilters, SLOT(reject()));

        QMetaObject::connectSlotsByName(SoundFilters);
    } // setupUi

    void retranslateUi(QDialog *SoundFilters)
    {
        SoundFilters->setWindowTitle(QApplication::translate("SoundFilters", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SoundFilters", "   Gain Level", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SoundFilters", "Max Increment", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SoundFilters", "Max Decrement", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SoundFilters", "Max Gain", 0, QApplication::UnicodeUTF8));
        AGCEn->setText(QApplication::translate("SoundFilters", "AGC enable", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("SoundFilters", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">AGC levels</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SoundFilters", "  Voice activation level", 0, QApplication::UnicodeUTF8));
        VoiceActEn->setText(QApplication::translate("SoundFilters", "enable", 0, QApplication::UnicodeUTF8));
        EchoEn->setText(QApplication::translate("SoundFilters", "Cancel echo", 0, QApplication::UnicodeUTF8));
        DenoiseEn->setText(QApplication::translate("SoundFilters", "Denoise", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("SoundFilters", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Voice activation control</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("SoundFilters", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Noise control</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SoundFilters: public Ui_SoundFilters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOUNDFILTERS_H
