#ifndef __QT_LIBRARY_H__
#define __QT_LIBRARY_H__

#include <QString>
#include <QLineEdit>

QString ToQString(const wchar_t *s);

template <class T>
void SetWindowFloat(T *pWidget, double x)
{
    if (pWidget)
    {
        pWidget->setText(QString::number(x));
    }
}

template <class T>
double GetWindowFloat(T *pWidget)
{
    if (pWidget)
    {
        return (pWidget->text().toDouble());
    }
    
    return (0.0);
}

#endif
