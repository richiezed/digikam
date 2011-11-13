/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2011-11-07
 * Description : Directory watch interface
 *
 * Copyright (C) 2011 by Marcel Wiesweg <marcel.wiesweg@gmx.de>
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

#ifndef ALBUMWATCH_H
#define ALBUMWATCH_H

// Qt includes

#include <QThread>
#include <QString>

// KDE includes

#include <kurl.h>

// Local includes

namespace Digikam
{

class Album;
class AlbumManager;
class DatabaseParameters;

class AlbumWatch : public QObject
{
    Q_OBJECT

public:

    AlbumWatch(AlbumManager* parent = 0);
    ~AlbumWatch();

    void clear();
    void setDatabaseParameters(const DatabaseParameters& params);

protected Q_SLOTS:
    
    void slotAlbumAdded(Album* album);
    void slotAlbumAboutToBeDeleted(Album* album);

    void slotFileMoved(const QString& path);
    void slotFileDeleted(const QString& urlString, bool isDir);
    void slotFileCreated(const QString& path, bool isDir);
    void slotFileClosedAfterWrite(const QString&);
    void slotInotifyWatchUserLimitReached();

    void slotDirWatchDirty(const QString& path);
    void slotKioFileMoved(const QString& urlFrom, const QString& urlTo);
    void slotKioFilesDeleted(const QStringList& urls);
    void slotKioFilesAdded(const QString& directory);

private:

    void rescanDirectory(const QString& dir);
    void rescanPath(const QString& path);

    void connectToKInotify();
    void connectToKDirWatch();
    void connectToKIO();
    void handleKioNotification(const KUrl& url);

    class AlbumWatchPriv;
    AlbumWatchPriv* const d;

};

}

#endif
