/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2012-10-03
 * Description : kipi loader implementation
 *
 * Copyright (C) 2012      by Supreet Pal Singh <supreetpal@gmail.com>
 * Copyright (C) 2004-2012 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef KIPIPLUGINLOADER_H
#define KIPIPLUGINLOADER_H

// Qt includes

#include <QObject>
#include <QList>
#include <QString>

// LibKIPI includes

#include <libkipi/plugin.h>

class QAction;

class KActionCollection;

namespace Digikam
{

class SplashScreen;

class KipiPluginLoader : public QObject
{
    Q_OBJECT

public:

    /** Standard constructor. Pass parent object instance and splashscreen
     *  instance. This last one can be null.
     */
    KipiPluginLoader(QObject* const parent, SplashScreen* const splash);

    /** Return a list of all plugin actions accordingly of plugin category.
     *  See KIPI::Category enum for details.
     */
    QList<QAction*> kipiActionsByCategory(KIPI::Category category) const;

    /** Return the instance of action collection for all KIPI plugins.
     */
    KActionCollection* pluginsActionCollection() const;

    /** Plug or unplug plugins actions list to application
     */
    void kipiPlugActions(bool unplug=false);

    /** Return the instance of this singleton plugin loader
     */
    static KipiPluginLoader* instance();

private Q_SLOTS:

    void slotKipiPluginPlug();

private:

    ~KipiPluginLoader();
    void loadPlugins();
    void checkEmptyCategory(KIPI::Category category);

private:

    static KipiPluginLoader* m_instance;

    class KipiPluginLoaderPriv;
    KipiPluginLoaderPriv* const d;
};

}  // namespace Digikam

#endif // KIPIPLUGINLOADER_H