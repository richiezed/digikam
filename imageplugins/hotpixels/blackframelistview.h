/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2005-07-05
 * Description : a ListView to display black frames
 * 
 * Copyright (C) 2005-2008 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2005-2006 by Unai Garro <ugarro at users dot sourceforge dot net>
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

#ifndef BLACKFRAMELISTVIEW_H
#define BLACKFRAMELISTVIEW_H

// Qt includes.

#include <Q3ValueList>
#include <QImage>
#include <QString>
#include <QSize>
#include <QPoint>
#include <QPixmap>
#include <QTreeWidget>

// KDE includes.

#include <kurl.h>
#include <klocale.h>

// Local includes.

#include "blackframeparser.h"
#include "hotpixel.h"

namespace DigikamHotPixelsImagesPlugin
{

class BlackFrameListView : public QTreeWidget
{
    Q_OBJECT

public:

    BlackFrameListView(QWidget* parent=0);
    ~BlackFrameListView(){};

signals:

    void blackFrameSelected(Q3ValueList<HotPixel>, const KUrl&);

private slots:

    void slotParsed(Q3ValueList<HotPixel> hotPixels, const KUrl& blackFrameURL)
    {
       emit blackFrameSelected(hotPixels, blackFrameURL);
    };
};

//-----------------------------------------------------------------------------------

class BlackFrameListViewItem : public QObject, QTreeWidgetItem
{
Q_OBJECT

public:

    BlackFrameListViewItem(BlackFrameListView* parent, const KUrl &url);
    ~BlackFrameListViewItem(){};

signals:

    void parsed(Q3ValueList<HotPixel>, const KUrl&);

protected:

    void activate();

private:

    QPixmap thumb(const QSize& size);

private slots:

    void slotParsed(Q3ValueList<HotPixel>);

private:

    // Data contained within each listview item
    QImage                m_thumb;
    QImage                m_image;

    QSize                 m_imageSize;

    Q3ValueList<HotPixel> m_hotPixels;

    QString               m_blackFrameDesc;

    KUrl                  m_blackFrameURL;

    BlackFrameParser      m_parser;

    BlackFrameListView   *m_parent;
};

}  // NameSpace DigikamHotPixelsImagesPlugin

#endif  // BLACKFRAMELISTVIEW_H
