#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>

class QMenuBar;
class QGroupBox;
class QLayout;

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = 0);


private:
    void createInstanceBox(int num, QGroupBox*& inst_group, QString box_name);

    void createMenuBar();
    void createSources();
    void createReceivers();
    void createRestricted();

    void setLayout();

    QMenuBar *menuBar;
    QGroupBox *sourcesGroup;
    QGroupBox *receiversGroup;
    QGroupBox *restrictedGroup;

    QLayout *layout;

signals:
    
public slots:
    
};

#endif // CONTROLPANEL_H
