#include "CSettingsDlg.h"
#include "QtLibrary.h"

#include "Library\Language.h"
#include "Library\ResourceString.h"
#include "Library\Win32Library.h"
//#include "Application.h"

CSettingsDlg::CSettingsDlg(QWidget *parent) : QDialog(parent)
{
    LabelLanguage = new QLabel;
    Languages = new QComboBox;
    BtnOK = new QPushButton;
    BtnCancel = new QPushButton;
    
    Layout = new QGridLayout;
    
    Layout->addWidget(LabelLanguage, 0, 0);
    Layout->addWidget(Languages, 1, 0);
    Layout->addWidget(BtnOK, 2, 0);
    Layout->addWidget(BtnCancel, 2, 1);
    
    setLayout(Layout);
    
    connect(BtnOK,  SIGNAL(clicked(bool)), this, SLOT(OnOK()));
    connect(BtnCancel, SIGNAL(clicked(bool)), this, SLOT(OnCancel()));
    
    Initialise();
}

void CSettingsDlg::Initialise()
{
	setWindowTitle(ToQString(ResourceString(L"IDS_SETTINGS")));
	LabelLanguage->setText(ToQString(ResourceString(L"IDS_LANGUAGE")));

	StringList s = LanguageManager::getInstance().getAvailableLanguages();

	for (StringList::const_iterator i = s.begin(); i != s.end(); i++)
	{
		Languages->addItem(ToQString((*i).c_str()));
	}

	Languages->setCurrentIndex(Languages->findText(ToQString(LanguageManager::getInstance().getCurrentLanguage().getName().c_str())));

	BtnOK->setText(ToQString(ResourceString(L"IDS_OK")));
	BtnCancel->setText(ToQString(ResourceString(L"IDS_CANCEL")));
}

void CSettingsDlg::OnOK()
{
	LanguageManager::getInstance().setCurrentLanguage(Languages->currentText().toStdWString().c_str());

	done(QDialog::Accepted);
}

void CSettingsDlg::OnCancel()
{
    done(QDialog::Rejected);
}
