#ifndef TTINSTVIEW_H
#define TTINSTVIEW_H

#include <QWidget>

class QLabel;
class QPushButton;
class QProgressBar;
class QLayout;
class QGroupBox;

class TTInstView : public QWidget
{
    Q_OBJECT
public:
    explicit TTInstView(QString iname, QWidget *parent = 0);
    
signals:
    
public slots:

private:
    void drawNameLabel(QString name);
    void drawChangeButton();
    void drawStatus();
    void drawSoundBar();

    QGroupBox* getStatusWidget();
    QGroupBox* getSoundBarWidget();

    void setLayout();

    QLabel* nameLabel;          // instance name

    QLabel* statusLabel;        // status lable
    QLabel* statusState;        // status state
    QPushButton* statusResolve; // resolve status button

    QLabel* soundLabel;         // sound label
    QProgressBar* soundBar;     // sound progress bar

    QPushButton* changeButton;  // change settings

    QLayout *layout;

};

#endif // TTINSTVIEW_H
