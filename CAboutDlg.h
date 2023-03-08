#ifndef __C_ABOUT_DLG_H__
#define __C_ABOUT_DLG_H__

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class CAboutDlg : public QDialog
{
Q_OBJECT

public:
    CAboutDlg(QWidget *parent = 0);
    //~CSettingsDlg();
    
    
    void Initialise();
    

public slots:
    void OnOK();
    
private:
    QLabel *LabelAbout;
    QPushButton *BtnOK;
    QGridLayout *Layout;
};

#endif
