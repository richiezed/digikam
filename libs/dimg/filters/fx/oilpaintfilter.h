/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2005-05-25
 * Description : Oil Painting threaded image filter.
 *
 * Copyright (C) 2005-2010 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2006-2010 by Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
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

#ifndef OILPAINTFILTER_H
#define OILPAINTFILTER_H

// Local includes

#include "digikam_export.h"
#include "dimgthreadedfilter.h"
#include "globals.h"

namespace Digikam
{

class DIGIKAM_EXPORT OilPaintFilter : public DImgThreadedFilter
{

public:

    explicit OilPaintFilter(DImg* orgImage, QObject* parent=0, int brushSize=1, int smoothness=30);
    ~OilPaintFilter();

private:

    void filterImage();

    DColor MostFrequentColor(DImg& src, int X, int Y, int Radius, int Intensity);
    inline double GetIntensity(uint Red, uint Green, uint Blue);

private:

    uchar* m_intensityCount;

    int    m_brushSize;
    int    m_smoothness;

    uint*  m_averageColorR;
    uint*  m_averageColorG;
    uint*  m_averageColorB;
};

}  // namespace Digikam

#endif /* OILPAINTFILTER_H */
