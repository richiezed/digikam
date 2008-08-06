/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2008-08-06
 * Description : Raw decoding settings for digiKam
 *               Standard libkdcraw parameters + few customized one.
 *
 * Copyright (C) 2008 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DRAW_DECODING_H
#define DRAW_DECODING_H

// LibKDcraw includes.

#include <libkdcraw/rawdecodingsettings.h>

// Local includes.

#include "digikam_export.h"

namespace Digikam
{

class DIGIKAM_EXPORT DRawDecoding : public KDcrawIface::RawDecodingSettings
{

public:

    /** Standard constructor with default settings */
    DRawDecoding()
    {
        gamma = 2.222222;
    };

    /** Standard destructor */
    virtual ~DRawDecoding(){};

    /** Method to use a settings to optimize time loading, for exemple to compute image histogram */
    void optimizeTimeLoading()
    {
        KDcrawIface::RawDecodingSettings::optimizeTimeLoading();
        gamma = 2.222222;
    };

public:

    /** Gamma correction value.
    */
    double gamma;
};

}  // namespace Digikam

#endif /* DRAW_DECODING_H */
