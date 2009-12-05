/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2000-12-05
 * Description : base class for sidebar widgets
 *
 * Copyright (C) 2009 by Johannes Wienke <languitar at semipol dot de>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

// QT includes
#include <qpixmap.h>
#include <qwidget.h>

// KDE includes
#include <kconfiggroup.h>
#include <kiconloader.h>

// Local includes
#include "album.h"
#include "imageinfo.h"

namespace Digikam
{

/**
 * Abstract base class for widgets that are use in one of digikams's sidebars.
 *
 * @author jwienke
 */
class SideBarWidget: public QWidget
{
Q_OBJECT
public:

    /**
     * Constructor.
     *
     * @param parent parent of this widget, may be null
     */
    SideBarWidget(QWidget *parent);

    /**
     * Destructor.
     */
    virtual ~SideBarWidget();

    /**
     * This method is called if the visible sidebar widget is changed.
     *
     * @param if true, this widget is the new active widget, if false another
     *        widget is active
     */
    virtual void setActive(bool active) = 0;

    /**
     * This method must be implemented to restore the last state of the sidebar
     * widget from the config.
     *
     * @param group config group to use to restore from
     */
    virtual void loadViewState(KConfigGroup &group) = 0;

    /**
     * This method must be implemented to store the current state.
     *
     * @param group config croup to store state to
     */
    virtual void saveViewState(KConfigGroup &group) = 0;

    /**
     * This method is invoked when the application settings should be (re-)
     * applied to this widget.
     */
    virtual void applySettings() = 0;

    /**
     * This is called on this widget when the history requires to move back to
     * the specified album
     */
    virtual void changeAlbumFromHistory(Album *album) = 0;

    /**
     * Must be implemented and return the icon that shall be visible for this
     * sidebar widget.
     *
     * @return pixmap icon
     */
    virtual QPixmap getIcon() = 0;

    /**
     * Must be implemented to return the title of this sidebar's tab.
     *
     * @return localized title string
     */
    virtual QString getCaption() = 0;

Q_SIGNALS:

    /**
     * This signal can be emitted if this sidebar widget wants to be the one
     * that is active.
     */
    void requestActiveTab(SideBarWidget*);

};

}

#endif /* SIDEBARWIDGET_H */
