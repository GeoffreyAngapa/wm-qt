#ifndef __C_SETTINGS_DLG_H__
#define __C_SETTINGS_DLG_H__

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>

class CSettingsDlg : public QDialog
{
Q_OBJECT

public:
    CSettingsDlg(QWidget *parent = 0);
    //~CSettingsDlg();
    
    
    void Initialise();
    

public slots:
    void OnOK();
    void OnCancel();
    
private:
    QLabel *LabelLanguage;
    QComboBox *Languages;
    QPushButton *BtnOK;
    QPushButton *BtnCancel;
    QGridLayout *Layout;
};

#endif
