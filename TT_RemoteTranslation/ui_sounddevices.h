/********************************************************************************
** Form generated from reading UI file 'sounddevices.ui'
**
** Created: Fri Oct 12 04:06:30 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOUNDDEVICES_H
#define UI_SOUNDDEVICES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_SoundDevices
{
public:
    QDialogButtonBox *ActSDButton;
    QComboBox *InputDevicesBox;
    QComboBox *OutputDevicesBox;
    QRadioButton *DirectSoundButton;
    QRadioButton *WindowsStandardButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *SelfTestButton;

    void setupUi(QDialog *SoundDevices)
    {
        if (SoundDevices->objectName().isEmpty())
            SoundDevices->setObjectName(QString::fromUtf8("SoundDevices"));
        SoundDevices->resize(432, 350);
        ActSDButton = new QDialogButtonBox(SoundDevices);
        ActSDButton->setObjectName(QString::fromUtf8("ActSDButton"));
        ActSDButton->setGeometry(QRect(20, 290, 341, 32));
        ActSDButton->setOrientation(Qt::Horizontal);
        ActSDButton->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        InputDevicesBox = new QComboBox(SoundDevices);
        InputDevicesBox->setObjectName(QString::fromUtf8("InputDevicesBox"));
        InputDevicesBox->setGeometry(QRect(150, 80, 211, 22));
        OutputDevicesBox = new QComboBox(SoundDevices);
        OutputDevicesBox->setObjectName(QString::fromUtf8("OutputDevicesBox"));
        OutputDevicesBox->setGeometry(QRect(150, 160, 211, 22));
        DirectSoundButton = new QRadioButton(SoundDevices);
        DirectSoundButton->setObjectName(QString::fromUtf8("DirectSoundButton"));
        DirectSoundButton->setGeometry(QRect(150, 30, 82, 18));
        WindowsStandardButton = new QRadioButton(SoundDevices);
        WindowsStandardButton->setObjectName(QString::fromUtf8("WindowsStandardButton"));
        WindowsStandardButton->setGeometry(QRect(270, 30, 121, 18));
        label = new QLabel(SoundDevices);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 80, 101, 21));
        label_2 = new QLabel(SoundDevices);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 160, 101, 21));
        label_3 = new QLabel(SoundDevices);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 30, 101, 21));
        SelfTestButton = new QPushButton(SoundDevices);
        SelfTestButton->setObjectName(QString::fromUtf8("SelfTestButton"));
        SelfTestButton->setGeometry(QRect(270, 230, 91, 31));

        retranslateUi(SoundDevices);
        QObject::connect(ActSDButton, SIGNAL(accepted()), SoundDevices, SLOT(accept()));
        QObject::connect(ActSDButton, SIGNAL(rejected()), SoundDevices, SLOT(reject()));

        QMetaObject::connectSlotsByName(SoundDevices);
    } // setupUi

    void retranslateUi(QDialog *SoundDevices)
    {
        SoundDevices->setWindowTitle(QApplication::translate("SoundDevices", "Dialog", 0, QApplication::UnicodeUTF8));
        DirectSoundButton->setText(QApplication::translate("SoundDevices", "Direct Sound", 0, QApplication::UnicodeUTF8));
        WindowsStandardButton->setText(QApplication::translate("SoundDevices", "Windows Standard", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SoundDevices", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Input devices</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SoundDevices", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Output devices</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SoundDevices", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Sound system</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        SelfTestButton->setText(QApplication::translate("SoundDevices", "Test selected", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SoundDevices: public Ui_SoundDevices {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOUNDDEVICES_H
