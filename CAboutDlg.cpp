#include "CAboutDlg.h"
#include "QtLibrary.h"

#include "Library\ResourceString.h"

CAboutDlg::CAboutDlg(QWidget *parent) : QDialog(parent)
{
    LabelAbout = new QLabel;    
    BtnOK = new QPushButton;
    
    Layout = new QGridLayout;
    Layout->addWidget(LabelAbout, 0, 0);
    Layout->addWidget(BtnOK, 1, 0);
    
    setLayout(Layout);
    
    connect(BtnOK,  SIGNAL(clicked(bool)), this, SLOT(OnOK()));
    
    Initialise();
}

void CAboutDlg::Initialise()
{
	setWindowTitle(ToQString(ResourceString(L"IDS_ABOUT")));
	LabelAbout->setText("About");

	BtnOK->setText(ToQString(ResourceString(L"IDS_OK")));
}

void CAboutDlg::OnOK()
{
	done(QDialog::Accepted);
}
