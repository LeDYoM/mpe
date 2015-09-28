#ifndef GLOBALWRAPPERH_H
#define GLOBALWRAPPERH_H

#include <QtCore>

#define _USE_QT

#ifdef _USE_QT
    #define CLASS_NO_COPY Q_DISABLE_COPY
#else
#define CLASS_NO_COPY(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;
#endif

#endif // GLOBALWRAPPERH_H
