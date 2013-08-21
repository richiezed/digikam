/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 09-08-2013
 * Description : Showfoto icon view tool tip
 *
 *Copyright (C) 2013 by Mohamed Anwer <mohammed dot ahmed dot anwer at gmail dot com>
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


#include "showfototooltipfiller.h"

// Qt includes

#include <QDateTime>

// KDE includes

#include <klocale.h>
#include <kfileitem.h>
#include <kglobal.h>
#include <kdeversion.h>

// Local includes

#include "showfotosettings.h"
#include "ditemtooltip.h"
#include "showfotoiteminfo.h"

using namespace Digikam;

namespace ShowFoto
{

QString ShowfotoToolTipFiller::ShowfotoItemInfoTipContents(const ShowfotoItemInfo& info)
{
    QString str;
    ShowfotoSettings* const settings = ShowfotoSettings::instance();
    DToolTipStyleSheet cnt(settings->getToolTipsFont());

    PhotoInfoContainer photoInfo   = info.photoInfo;
    QString tip                    = cnt.tipHeader;

    // -- File properties ----------------------------------------------

    if (settings->getToolTipsShowFileName()  ||
        settings->getToolTipsShowFileDate()  ||
        settings->getToolTipsShowFileSize()  ||
        settings->getToolTipsShowImageType() ||
        settings->getToolTipsShowImageDim())
    {
        tip += cnt.headBeg + i18n("File Properties") + cnt.headEnd;

        if (settings->getToolTipsShowFileName())
        {
            tip += cnt.cellBeg + i18nc("filename",
                                       "Name:") + cnt.cellMid;
            tip += info.name + cnt.cellEnd;
        }

//        if (settings->getToolTipsShowFileDate())
//        {
//            QDateTime createdDate  = info.ctime;
//            str                     = KGlobal::locale()->formatDateTime(createdDate, KLocale::ShortDate, true);
//            tip                    += cnt.cellBeg + i18n("Date:") + cnt.cellMid + str + cnt.cellEnd;
//        }

        if (settings->getToolTipsShowFileSize())
        {
            tip += cnt.cellBeg + i18n("Size:") + cnt.cellMid;
            QString localeFileSize = KGlobal::locale()->formatNumber(info.size, 0);
            str = i18n("%1 (%2)", KIO::convertSize(info.size), localeFileSize);
            tip += str + cnt.cellEnd;
        }

        QSize dims;

        if (settings->getToolTipsShowImageType())
        {
            tip += cnt.cellBeg + i18n("Type:") + cnt.cellMid + info.mime + cnt.cellEnd;
        }

//        if (settings->getToolTipsShowImageDim())
//        {
//            if (info.width == 0 || info.height == 0 || info.width == -1 || info.height == -1)
//            {
//                str = i18nc("unknown / invalid image dimension",
//                            "Unknown");
//            }
//            else
//            {
//                QString mpixels;
//                mpixels.setNum(info.width*info.height/1000000.0, 'f', 2);
//                str = i18nc("width x height (megapixels Mpx)", "%1x%2 (%3Mpx)",
//                            info.width, info.height, mpixels);
//            }

//            tip += cnt.cellBeg + i18n("Dimensions:") + cnt.cellMid + str + cnt.cellEnd;
//        }
    }

    // -- Photograph Info -----------------------------------------------------------------------
    // NOTE: these info require \"Use File Metadata\" option from Camera Setup Behavior page.

    if (settings->getToolTipsShowPhotoMake()  ||
        settings->getToolTipsShowPhotoFocal() ||
        settings->getToolTipsShowPhotoExpo()  ||
        settings->getToolTipsShowPhotoFlash() ||
        settings->getToolTipsShowPhotoWB())
    {
        if (!photoInfo.isNull())
        {
            QString metaStr;
            tip += cnt.headBeg + i18n("Photograph Properties") + cnt.headEnd;

            if (settings->getToolTipsShowPhotoMake())
            {
                str = QString("%1 / %2").arg(photoInfo.make.isEmpty() ? cnt.unavailable : photoInfo.make)
                      .arg(photoInfo.model.isEmpty() ? cnt.unavailable : photoInfo.model);

                if (str.length() > cnt.maxStringLength)
                {
                    str = str.left(cnt.maxStringLength-3) + "...";
                }

                metaStr += cnt.cellBeg + i18n("Make/Model:") + cnt.cellMid + Qt::escape(str) + cnt.cellEnd;
            }

            if (settings->getToolTipsShowPhotoFocal())
            {
                str = photoInfo.aperture.isEmpty() ? cnt.unavailable : photoInfo.aperture;

                if (photoInfo.focalLength35mm.isEmpty())
                {
                    str += QString(" / %1").arg(photoInfo.focalLength.isEmpty() ? cnt.unavailable : photoInfo.focalLength);
                }
                else
                {
                    str += QString(" / %1").arg(i18n("%1 (35mm: %2)",photoInfo.focalLength, photoInfo.focalLength35mm));
                }

                if (str.length() > cnt.maxStringLength)
                {
                    str = str.left(cnt.maxStringLength-3) + "...";
                }

                metaStr += cnt.cellBeg + i18n("Aperture/Focal:") + cnt.cellMid + Qt::escape(str) + cnt.cellEnd;
            }

            if (settings->getToolTipsShowPhotoExpo())
            {
                str = QString("%1 / %2").arg(photoInfo.exposureTime.isEmpty() ? cnt.unavailable : photoInfo.exposureTime)
                      .arg(photoInfo.sensitivity.isEmpty() ? cnt.unavailable : i18n("%1 ISO",photoInfo.sensitivity));

                if (str.length() > cnt.maxStringLength)
                {
                    str = str.left(cnt.maxStringLength-3) + "...";
                }

                metaStr += cnt.cellBeg + i18n("Exposure/Sensitivity:") + cnt.cellMid + Qt::escape(str) + cnt.cellEnd;
            }

            if (settings->getToolTipsShowPhotoFlash())
            {
                str = photoInfo.flash.isEmpty() ? cnt.unavailable : photoInfo.flash;

                if (str.length() > cnt.maxStringLength)
                {
                    str = str.left(cnt.maxStringLength-3) + "...";
                }

                metaStr += cnt.cellBeg + i18nc("camera flash settings",
                                               "Flash:") + cnt.cellMid + Qt::escape(str) + cnt.cellEnd;
            }

            if (settings->getToolTipsShowPhotoWB())
            {
                str = photoInfo.whiteBalance.isEmpty() ? cnt.unavailable : photoInfo.whiteBalance;

                if (str.length() > cnt.maxStringLength)
                {
                    str = str.left(cnt.maxStringLength-3) + "...";
                }

                metaStr += cnt.cellBeg + i18n("White Balance:") + cnt.cellMid + Qt::escape(str) + cnt.cellEnd;
            }

            tip += metaStr;
        }
    }

    tip += cnt.tipFooter;

    return tip;
}

}  // namespace ShowFoto

