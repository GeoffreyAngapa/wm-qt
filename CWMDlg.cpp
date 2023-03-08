#include "CWMDlg.h"
#include "CSettingsDlg.h"
#include "CAboutDlg.h"

#include "QtLibrary.h"

#include "Application.h"
#include "Library\Library.h"
#include "Library\Win32Library.h"
#include "Library\ResourceString.h"
#include "Library\Registry.h"
#include "Library\File.h"
#include "Library\Templates.h"

CWMDlg::CWMDlg(QWidget *Parent) : QDialog(Parent)
{
    Modes = new QComboBox;
    
    ValueList[0] = Value1 = new QLineEdit;
    ValueList[1] = Value2 = new QLineEdit;
    ValueList[2] = Value3 = new QLineEdit;
    ValueList[3] = Value4 = new QLineEdit;
    ValueList[4] = Value5 = new QLineEdit;
    ValueList[5] = Value6 = new QLineEdit;
    ValueList[6] = Value7 = new QLineEdit;
    ValueList[7] = Value8 = new QLineEdit;
    ValueList[8] = Value9 = new QLineEdit;

    for (int i = 0; i < TitleList.size(); i++)
    {
        TitleList[i] = new QLabel;
        AbrvList[i] = new QLabel;
    }
    
    // Create and add widgets to layout
    
    Layout = new QGridLayout;
    
    //Layout->addWidget(Modes, 0, 0);
    
    for (int j = 0; j < ValueList.size(); j++)
    {
        Layout->addWidget(ValueList[j], j + 1, 1);
        Layout->addWidget(TitleList[j], j + 1, 0);
        Layout->addWidget(AbrvList[j], j + 1, 2);
    }
    
    //Layout->setVerticalSpacing(5);
    Layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    
    // Setup Menu
    ActionToolsCalculator = new QAction(NULL);
    ActionToolsSettings = new QAction(NULL);
    ActionToolsQuit = new QAction(NULL);
    ActionHelpHelp = new QAction(NULL);
    ActionHelpLicence = new QAction(NULL);
    ActionHelpAbout = new QAction(NULL);
    
    ToolsMenu = new QMenu;
    ToolsMenu->addAction(ActionToolsCalculator);
    ToolsMenu->addSeparator();
    ToolsMenu->addAction(ActionToolsSettings);
    ToolsMenu->addSeparator();
    ToolsMenu->addAction(ActionToolsQuit);
    
    HelpMenu = new QMenu;
    HelpMenu->addAction(ActionHelpHelp);
    HelpMenu->addSeparator();
    HelpMenu->addAction(ActionHelpLicence);
    HelpMenu->addSeparator();
    HelpMenu->addAction(ActionHelpAbout);
    
    Menu = new QMenuBar;
    Menu->addMenu(ToolsMenu);
    Menu->addMenu(HelpMenu);
    
    
    
    
    //Layout->setMenuBar(Menu);
    
    Group = new QGroupBox;
    
    Group->setLayout(Layout);
    
    VLayout = new QVBoxLayout;
    
    VLayout->addWidget(Modes);
    
    VLayout->addWidget(Group);
    
    VLayout->setMenuBar(Menu);
    
    setLayout(VLayout);
    
    for (int k = 0; k < ValueList.size(); k++)
    {
        ValueList[k]->setAlignment(Qt::AlignRight);
    }
    
    //resize(420, height());
    //setFixedSize(sizeHint());
    
    setWindowFlags(Qt::WindowMinimizeButtonHint);

    connect(Modes,  SIGNAL(currentIndexChanged(int)), this, SLOT(OnChangeModes()));
    connect(Value1, SIGNAL(returnPressed()), this, SLOT(OnChangeValue1()));
    connect(Value2, SIGNAL(returnPressed()), this, SLOT(OnChangeValue2()));
    connect(Value3, SIGNAL(returnPressed()), this, SLOT(OnChangeValue3()));
    connect(Value4, SIGNAL(returnPressed()), this, SLOT(OnChangeValue4()));
    connect(Value5, SIGNAL(returnPressed()), this, SLOT(OnChangeValue5()));
    connect(Value6, SIGNAL(returnPressed()), this, SLOT(OnChangeValue6()));
    connect(Value7, SIGNAL(returnPressed()), this, SLOT(OnChangeValue7()));
    connect(Value8, SIGNAL(returnPressed()), this, SLOT(OnChangeValue8()));
    connect(Value9, SIGNAL(returnPressed()), this, SLOT(OnChangeValue9()));
    connect(ActionToolsCalculator, SIGNAL(triggered(bool)), this, SLOT(OnToolsCalculator()));
    connect(ActionToolsSettings, SIGNAL(triggered(bool)), this, SLOT(OnToolsSettings()));
    connect(ActionToolsQuit, SIGNAL(triggered(bool)), this, SLOT(OnToolsQuit()));
    connect(ActionHelpHelp, SIGNAL(triggered(bool)), this, SLOT(OnHelpHelp()));
    connect(ActionHelpLicence, SIGNAL(triggered(bool)), this, SLOT(OnHelpLicence()));
    connect(ActionHelpAbout, SIGNAL(triggered(bool)), this, SLOT(OnHelpAbout()));

    Initialise();
}

CWMDlg::~CWMDlg()
{
}

int CWMDlg::DoModal()
{
    show();
    
    return (0);
}

void CWMDlg::Initialise()
{
    UpdateWindowTitle();
    UpdateMenu();

    AddModes();

    RetrieveConfiguration();
    OnChangeModes();

    Value1->setFocus();
    Value1->selectAll();
}

void CWMDlg::RetrieveConfiguration()
{
/*
        ConvertorDlgCfg Cfg;
        ConvertorDlgCfgSerializer().Retrieve(Cfg, Registry(GetRegistryKey(), KEY_READ, false));

        SelectMode(Cfg.nConversionType);
        ::SetWindowPos(GetSafeHwnd(), NULL, Cfg.x, Cfg.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        */
}

void CWMDlg::SaveConfiguration()
{
/*
        ConvertorDlgCfg Cfg;

        Cfg.nConversionType = GetSelectedMode();
        Cfg.x = GetWindowLeft(GetSafeHwnd());
        Cfg.y = GetWindowTop(GetSafeHwnd());

        ConvertorDlgCfgSerializer().Save(Cfg, Registry(GetRegistryKey(), KEY_WRITE, true));
        */
}

void CWMDlg::OnBeforeClose()
{
    SaveConfiguration();
}

void CWMDlg::AddModes()
{
    Modes->clear();

    const ConversionInterfaceFactory::InterfaceListType &r = Factory.getInterfaces();

    for (ConversionInterfaceFactory::InterfaceListType::const_iterator i = r.begin(); i != r.end(); i++)
    {
        if (*i)
        {
            Modes->addItem(ToQString(ResourceString((*i)->getName())), QVariant::fromValue((*i)->getType()));
        }
    }
}

int CWMDlg::GetSelectedMode() const
{
    QVariant d = Modes->itemData(Modes->currentIndex());

    return ((d != QVariant::Invalid) ? d.toInt() : -1);
}

void CWMDlg::SelectMode(int nType)
{
    for (int i = 0; i < Modes->count(); i++)
    {
        QVariant d = Modes->itemData(i);
        
        if ((d != QVariant::Invalid) && (d.toInt() == nType))
        {
            Modes->setCurrentIndex(i);
            
            return;
        }
    }
}

ConversionInterface *CWMDlg::GetCurrentInterface() const
{
    return (pCurrentInterface);
}

void CWMDlg::SetCurrentInterface(ConversionInterface *p)
{
    pCurrentInterface = p;
}

bool CWMDlg::IsValidInterface() const
{
    return (GetCurrentInterface() != NULL);
}

void CWMDlg::UpdateWindowTitle()
{
#ifdef QT_NO_DEBUG
    setWindowTitle(ToQString(GetApplicationName()));
#else
    setWindowTitle(ToQString(GetApplicationName()) + " " + ToQString(GetApplicationVersion()) + " (Debug)");
#endif
}

void CWMDlg::UpdateMenu()
{
    ToolsMenu->setTitle(ToQString(ResourceString(L"IDS_MENU_TOOLS")));
    HelpMenu->setTitle(ToQString(ResourceString(L"IDS_MENU_HELP")));

    ActionToolsCalculator->setText(ToQString(ResourceString(L"IDS_TOOLS_CALCULATOR")));
    ActionToolsSettings->setText(ToQString(ResourceString(L"IDS_TOOLS_SETTINGS")));
    ActionToolsQuit->setText(ToQString(ResourceString(L"IDS_TOOLS_QUIT")));

    ActionHelpHelp->setText(ToQString(ResourceString(L"IDS_HELP_HELP")));
    ActionHelpLicence->setText(ToQString(ResourceString(L"IDS_HELP_LICENCE")));
    ActionHelpAbout->setText(ToQString(ResourceString(L"IDS_HELP_ABOUT")));
}

void CWMDlg::UpdateControls()
{
    if (IsValidInterface())
    {
        SetWindowFloat(Value1, GetCurrentInterface()->getValue1());
        SetWindowFloat(Value2, GetCurrentInterface()->getValue2());
        SetWindowFloat(Value3, GetCurrentInterface()->getValue3());
        SetWindowFloat(Value4, GetCurrentInterface()->getValue4());
        SetWindowFloat(Value5, GetCurrentInterface()->getValue5());
        SetWindowFloat(Value6, GetCurrentInterface()->getValue6());
        SetWindowFloat(Value7, GetCurrentInterface()->getValue7());
        SetWindowFloat(Value8, GetCurrentInterface()->getValue8());
        SetWindowFloat(Value9, GetCurrentInterface()->getValue9());
    }
}

void CWMDlg::UpdateWindowSize()
{
    
    
    
    //setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    
    
    
    resize(width(), 150);
    
/*
        for (int i = ValueList.size() - 1; i >= 0; i--)
        {
                if (ValueList[i]->IsWindowEnabled())
                {
                        const HWND hDlg = GetSafeHwnd();

                        const int LastValueBottom = GetWindowTop(ValueList[i]->GetSafeHwnd()) +
                                                                                GetWindowHeight(ValueList[i]->GetSafeHwnd());

                        const int h = LastValueBottom + 48 - GetWindowTop(hDlg);

                        SetWindowSize(hDlg, GetWindowWidth(hDlg), h);

                        const int h2 = GetWindowTop(ValueList[0]->GetSafeHwnd()) -
                                                   GetWindowTop(Group.GetSafeHwnd()) +
                                                   LastValueBottom -
                                                   GetWindowTop(Group.GetSafeHwnd());

                        SetWindowSize(Group.GetSafeHwnd(), GetWindowWidth(Group.GetSafeHwnd()), h2);

                        return;
                }
        }
        */
}

void CWMDlg::UpdateWindowPos()
{
    //const HWND hDlg = GetSafeHwnd();

    const int _x = x();
    const int _y = y();

    const int xMax = GetDesktopWidth() - frameGeometry().width();
    const int yMax = GetDesktopHeight() - frameGeometry().height();

    if (!InRange(0, xMax, _x) || !InRange(0, yMax, _y))
    {
        move(Clamp(0, xMax, _x), Clamp(0, yMax, _y));
    }
}

void CWMDlg::OnChangeModes()
{
    SetCurrentInterface(Factory.getConversionInterface(GetSelectedMode()));
    
    for (int i = 0; i < ValueList.size(); i++)
    {
        const bool bEnable = i < (IsValidInterface() ? GetCurrentInterface()->getValueCount() : 0);
        //const int nCmdShow = bEnable ? SW_SHOW : SW_HIDE;
        
        ValueList[i]->setEnabled(bEnable);
        ValueList[i]->setVisible(bEnable);
        
        //HWND hDlg = GetSafeHwnd();
        
        if (bEnable)
        {
            TitleList[i]->setText(ToQString(ResourceString(GetCurrentInterface()->getTitle(i))));
            AbrvList[i]->setText(ToQString(ResourceString(GetCurrentInterface()->getAbbreviation(i))));
        }
        
        TitleList[i]->setVisible(bEnable);
        AbrvList[i]->setVisible(bEnable);
    }

    UpdateControls();
    UpdateWindowSize();
    UpdateWindowPos();
}

void CWMDlg::OnChangeValue1()
{
    if (IsValidInterface())
    {
        GetCurrentInterface()->setValue1(GetWindowFloat(Value1));
        UpdateControls();
    }
}

void CWMDlg::OnChangeValue2()
{
    if (IsValidInterface())
    {
        GetCurrentInterface()->setValue2(GetWindowFloat(Value2));
        UpdateControls();
    }
}

void CWMDlg::OnChangeValue3()
{
    if (IsValidInterface())
    {
        GetCurrentInterface()->setValue3(GetWindowFloat(Value3));
        UpdateControls();
    }
}

void CWMDlg::OnChangeValue4()
{
    if (IsValidInterface())
    {
        GetCurrentInterface()->setValue4(GetWindowFloat(Value4));
        UpdateControls();
    }
}

void CWMDlg::OnChangeValue5()
{
    if (IsValidInterface())
    {
        GetCurrentInterface()->setValue5(GetWindowFloat(Value5));
        UpdateControls();
    }
}

void CWMDlg::OnChangeValue6()
{
    if (IsValidInterface())
    {
        GetCurrentInterface()->setValue6(GetWindowFloat(Value6));
        UpdateControls();
    }
}

void CWMDlg::OnChangeValue7()
{
    if (IsValidInterface())
    {
        GetCurrentInterface()->setValue7(GetWindowFloat(Value7));
        UpdateControls();
    }
}

void CWMDlg::OnChangeValue8()
{
    if (IsValidInterface())
    {
        GetCurrentInterface()->setValue8(GetWindowFloat(Value8));
        UpdateControls();
    }
}

void CWMDlg::OnChangeValue9()
{
    if (IsValidInterface())
    {
        GetCurrentInterface()->setValue9(GetWindowFloat(Value9));
        UpdateControls();
    }
}

///

void CWMDlg::OnToolsCalculator()
{
}

void CWMDlg::OnToolsSettings()
{
    if (CSettingsDlg(this).exec() == QDialog::Accepted)
    {
        const int m = GetSelectedMode();
        
        UpdateMenu();
        AddModes();
        SelectMode(m);
    }
}

void CWMDlg::OnToolsQuit()
{
    OnBeforeClose();
    
    done(QDialog::Accepted);
}

void CWMDlg::OnHelpHelp()
{
}

void CWMDlg::OnHelpLicence()
{
}

void CWMDlg::OnHelpAbout()
{
    CAboutDlg(this).exec();
}
