#include <QtGui/QApplication>
#include "CWMDlg.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CWMDlg w;
    w.show();

    return a.exec();
}
