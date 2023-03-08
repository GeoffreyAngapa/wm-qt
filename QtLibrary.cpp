#include "QtLibrary.h"

QString ToQString(const wchar_t *s)
{
    return QString::fromWCharArray(s);
}
