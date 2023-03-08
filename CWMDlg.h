#ifndef __C_WM_DLG_H__
#define __C_WM_DLG_H__

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QGridLayout>

#include <QGroupBox>
#include <QVBoxLayout>

#include "Interfaces\ConversionInterfaceFactory.h"
#include "Library\array.h"
#include "Library\Configuration.h"

class CWMDlg : public QDialog
{
Q_OBJECT

public:
    CWMDlg(QWidget *parent = 0);
    ~CWMDlg();
    
    int DoModal();


    void Initialise();
    void UpdateWindowTitle();
    void UpdateMenu();
    
    void OnBeforeClose();

    void AddModes();
    int GetSelectedMode() const;
    void SelectMode(int nType);

    ConversionInterface *GetCurrentInterface() const;
    void SetCurrentInterface(ConversionInterface *p);
    bool IsValidInterface() const;

    void UpdateControls();
    
    void UpdateWindowPos();
    void UpdateWindowSize();
    
    void RetrieveConfiguration();
    void SaveConfiguration();

public slots:
    void OnChangeModes();
    void OnChangeValue1();
    void OnChangeValue2();
    void OnChangeValue3();
    void OnChangeValue4();
    void OnChangeValue5();
    void OnChangeValue6();
    void OnChangeValue7();
    void OnChangeValue8();
    void OnChangeValue9();
    void OnToolsCalculator();
	void OnToolsSettings();
	void OnToolsQuit();
	void OnHelpHelp();
	void OnHelpLicence();
	void OnHelpAbout();

private:
    ConversionInterfaceFactory Factory;
    ConversionInterface *pCurrentInterface;
    
    QComboBox *Modes;
    QGridLayout *Layout;
    
    QVBoxLayout *VLayout;
    
    QGroupBox *Group;
    
    QLineEdit *Value1;
    QLineEdit *Value2;
    QLineEdit *Value3;
    QLineEdit *Value4;
    QLineEdit *Value5;
    QLineEdit *Value6;
    QLineEdit *Value7;
    QLineEdit *Value8;
    QLineEdit *Value9;
    
    QMenuBar *Menu;
    QMenu *ToolsMenu;
    QMenu *HelpMenu;
    
    QAction *ActionToolsCalculator;
	QAction *ActionToolsSettings;
	QAction *ActionToolsQuit;
	QAction *ActionHelpHelp;
	QAction *ActionHelpLicence;
	QAction *ActionHelpAbout;
    

    array<QLineEdit *, 9> ValueList;
    array<QLabel *, 9> TitleList;
    array<QLabel *, 9> AbrvList;
};

#endif
