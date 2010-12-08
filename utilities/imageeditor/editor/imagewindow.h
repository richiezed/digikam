/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2004-02-12
 * Description : digiKam image editor GUI
 *
 * Copyright (C) 2004-2005 by Renchi Raju <renchi@pooh.tam.uiuc.edu>
 * Copyright (C) 2004-2010 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

// Qt includes

#include <QCloseEvent>
#include <QString>

// KDE includes

#include <kurl.h>

// Local includes

#include "editorwindow.h"
#include "imageinfo.h"

class QDragMoveEvent;
class QDropEvent;

namespace Digikam
{

class ImageWindowPriv;
class SlideShowSettings;
class CollectionImageChangeset;

class ImageWindow : public EditorWindow
{
    Q_OBJECT

public:

    ~ImageWindow();

    void loadImageInfos(const ImageInfoList& imageInfoList,
                        const ImageInfo& imageInfoCurrent, const QString& caption);

    static ImageWindow* imageWindow();
    static bool         imageWindowCreated();

    bool setup();
    bool setupICC();

    bool queryClose();
    virtual VersionManager* versionManager();

Q_SIGNALS:

    void signalFileDeleted(const KUrl& url);
    void signalURLChanged(const KUrl& url);
    void signalSavingDialogProgress(float value);

private:

    void loadIndex(const QModelIndex& index);
    void closeEvent(QCloseEvent* e);
    void showEvent(QShowEvent*);

    void dragMoveEvent(QDragMoveEvent* e);
    void dropEvent(QDropEvent* e);

    void setupActions();
    void setupConnections();
    void setupUserArea();

    bool save();
    bool saveAs();
    bool saveNewVersion();
    bool saveCurrentVersion();
    KUrl saveDestinationUrl();
    bool hasChangesToSave();
    bool hasOriginalToRestore();
    DImageHistory resolvedImageHistory(const DImageHistory& history);

    void prepareImageToSave();

    void saveIsComplete();
    void saveAsIsComplete();
    void saveVersionIsComplete();
    void setViewToURL(const KUrl& url);
    void deleteCurrentItem(bool ask, bool permanently);
    void removeCurrent();

    void slideShow(bool startWithCurrent, SlideShowSettings& settings);

    void assignRating(const ImageInfo& info, int rating);

    ThumbBarDock* thumbBar() const;
    Sidebar* rightSideBar() const;

    ImageWindow();

Q_SIGNALS: // private signals

    void loadCurrentLater();

private Q_SLOTS:

    void slotForward();
    void slotBackward();
    void slotFirst();
    void slotLast();
    void slotFilePrint();

    void slotToMainWindow();

    void slotThumbBarImageSelected(const ImageInfo&);
    void slotLoadCurrent();
    void slotDeleteCurrentItem();
    void slotDeleteCurrentItemPermanently();
    void slotDeleteCurrentItemPermanentlyDirectly();
    void slotTrashCurrentItemDirectly();

    void slotChanged();
    void slotUpdateItemInfo();

    void slotContextMenu();
    void slotRevert();
    void slotOpenOriginal();

    void slotAssignTag(int tagID);
    void slotRemoveTag(int tagID);

    void slotAssignRatingNoStar();
    void slotAssignRatingOneStar();
    void slotAssignRatingTwoStar();
    void slotAssignRatingThreeStar();
    void slotAssignRatingFourStar();
    void slotAssignRatingFiveStar();
    void slotAssignRating(int rating);
    void slotRatingChanged(const KUrl& url, int rating);

    void slotFileMetadataChanged(const KUrl&);
    //void slotCollectionImageChange(const CollectionImageChangeset&);
    //void slotRowsAboutToBeRemoved(const QModelIndex& parent, int start, int end);
    void slotDroppedOnThumbbar(const QList<ImageInfo>& infos);

    void slotChangeTheme(const QString& theme);

    void slotComponentsInfo();
    void slotDBStat();

    void slotSetupChanged();

private:

    ImageWindowPriv* const d;

    static ImageWindow* m_instance;
};

}  // namespace Digikam

#endif /* IMAGEWINDOW_H */
