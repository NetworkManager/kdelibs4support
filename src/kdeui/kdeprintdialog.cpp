/*
 *  This file is part of the KDE libraries
 *  Copyright (c) 2007 Alex Merry <alex.merry@kdemail.net>
 *  Copyright (c) 2007 Thomas Zander <zander@kde.org>
 *  Copyright (c) 2008 John Layt <john@layt.net>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 **/

#include "kdeprintdialog.h"

#include "klocalizedstring.h"

#include <QPrintDialog>
#include <QLabel>

QPrintDialog *KdePrint::createPrintDialog(QPrinter *printer, const QList<QWidget *> &customTabs, QWidget *parent)
{
    QPrintDialog *dialog = new QPrintDialog(printer, parent);
#if defined(Q_OS_UNIX) && !defined(Q_OS_DARWIN)
    dialog->setOptionTabs(customTabs);
#else //Not Unix modulo Mac
    foreach (QWidget *w, customTabs) { // reparent to avoid leaks
        w->setParent(dialog);
    }
#endif
    dialog->setWindowTitle(i18nc("@title:window", "Print"));
    return dialog;
}

QPrintDialog *KdePrint::createPrintDialog(QPrinter *printer, QWidget *parent)
{
    return KdePrint::createPrintDialog(printer, QList<QWidget *>(), parent);
}
