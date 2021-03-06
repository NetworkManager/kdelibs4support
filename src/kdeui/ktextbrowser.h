/*  This file is part of the KDE Libraries
 *  Copyright (C) 1999 Espen Sand (espensa@online.no)
 *  Copyright (C) 2006 Urs Wolfer <uwolfer at fwo.ch>
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
 */

#ifndef KTEXTBROWSER_H
#define KTEXTBROWSER_H

#include <kdelibs4support_export.h>

#include <QTextBrowser>

/**
 * @deprecated since 5.0, use QTextBrowser instead
 *
 * @brief Extended QTextBrowser.
 *
 * Porting from KTextBrowser to QTextBrowser:
 * - setNotifyClick becomes setOpenLinks, isNotifyClick is set to openLinks.
 * - use the signal QTextBrowser::anchorClicked for KTextBrowser::urlClick
 *
 * By default KTextBrowser will
 * invoke the system mailer or the system browser when a link is
 * activated, or it can emit the signal urlClick() or mailClick()
 * when a link is activated.
 *
 * If the link starts with the text "whatsthis:" a QWhatsThis
 * box will appear and then display the rest of the text.
 *
 * @warning The "whatsthis:" feature is considered deprecated: it is not
 *          available in KDE Frameworks 5, because KDE Frameworks 5 does
 *          not provide KTextBrowser anymore.
 *
 * \image html ktextbrowser.png "KDE Text Browser"
 *
 * @author Espen Sand (espensa@online.no)
 *
 * @see QTextBrowser
 */

class KDELIBS4SUPPORT_DEPRECATED_EXPORT KTextBrowser : public QTextBrowser
{
    Q_OBJECT
    Q_PROPERTY(bool notifyClick READ isNotifyClick WRITE setNotifyClick)

public:
    /**
     * Creates a new text browser.
     *
     * @param parent Parent of the widget.
     * @param notifyClick @p true causes signals to be emitted.
     */
    KDELIBS4SUPPORT_DEPRECATED explicit KTextBrowser(QWidget *parent = nullptr, bool notifyClick = false);

    /**
     * Destroys the text browser.
     */
    ~KTextBrowser();

    /**
     * Decide whether a click on a link should be handled internally
     * or if a signal should be emitted.
     *
     * @param notifyClick @p true causes signals to be emitted.
     */
    void setNotifyClick(bool notifyClick);

    /**
     * Returns whether a click on a link should be handled internally
     * or if a signal should be emitted.
     */
    bool isNotifyClick() const;

protected:
    /**
     * Reimplemented to NOT set the source but to do the special handling
     * of links being clicked. Do not call this.
     *
     * If you need to set an initial source url in the text browser, call
     * the QTextBrowser method KDELIBS4SUPPORT_DEPRECATED explicitly, like this:
     * <code>myTextBrowser->QTextBrowser::setSource(url)</code>
     */
    void setSource(const QUrl &name) Q_DECL_OVERRIDE;

    /**
     * Makes sure Key_Escape is ignored
     */
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

    /**
     * Reimplemented to support Qt2 behavior (Ctrl-Wheel = fast scroll)
     */
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

    /**
    * Re-implemented for internal reasons.  API not affected.
    *
    * See QLineEdit::createPopupMenu().
    */

    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

Q_SIGNALS:
    /**
     * Emitted when a mail link has been activated and the widget has
     * been configured to emit the signal.
     *
     * @param name The destination name. It is QString() at the moment.
     * @param address The destination address.
     */
    void mailClick(const QString &name, const QString &address);

    /**
     * Emitted if mailClick() is not emitted and the widget has been
     * configured to emit the signal.
     *
     * @param url The destination address.
     */
    void urlClick(const QString &url);

private:
    class Private;
    Private *const d;
};

#endif
