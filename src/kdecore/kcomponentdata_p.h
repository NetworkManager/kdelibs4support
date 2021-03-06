/*  This file is part of the KDE project
    Copyright (C) 2007 Matthias Kretz <kretz@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License version 2 as published by the Free Software Foundation.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

*/

#ifndef KERNEL_KCOMPONENTDATA_P_H
#define KERNEL_KCOMPONENTDATA_P_H

#include "kcomponentdata.h"
#include <QAtomicInt>
#include <QDebug>
#include <QCoreApplication>
#include <QString>

#include <kconfig.h>
#include <k4aboutdata.h>

class KComponentDataPrivate
{
public:
    KComponentDataPrivate(const K4AboutData &aboutData_)
        : aboutData(aboutData_),
          refCount(1)
    {
    }

    ~KComponentDataPrivate()
    {
        refCount.fetchAndStoreOrdered(-0x00FFFFFF); //prevent a reentering of the dtor

        sharedConfig = nullptr;   //delete the config object first, because it could access the standard dirs while syncing
    }

    inline void ref()
    {
        refCount.ref();
        //qDebug() << refCount - 1 << "->" << refCount << kBacktrace() << endl;
    }

    inline void deref()
    {
        const int refc = refCount.fetchAndAddOrdered(-1) - 1;
        //qDebug() << refCount + 1 << "->" << refCount << kBacktrace() << endl;
        if (refc == 0) {
            delete this;
        }
    }

    void lazyInit();
    void configInit();  //call this only from lazyInit()!

    K4AboutData aboutData;
    QString configName;
    KSharedConfig::Ptr sharedConfig;

private:
    QAtomicInt refCount;
    KComponentDataPrivate(const KComponentDataPrivate &);
    KComponentDataPrivate &operator=(const KComponentDataPrivate &);
};

#endif // KERNEL_KCOMPONENTDATA_P_H
