/***************************************************************************
 *   Copyright (C) 2013 by Alex Graf                                       *
 *   grafal@sourceforge.net                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef FLIGHTPOINT_H
#define FLIGHTPOINT_H

#include <QTime>
#include "LatLng.h"

class FlightPoint
{
  public:
    FlightPoint();

    FlightPoint(const FlightPoint *pFp);

    FlightPoint(const LatLng &pos, double alt = 0);

    void setPos(const LatLng &pos);

    const LatLng& pos() const;

    void setTime(const QTime &time);

    const QTime& time() const;

    void setAlt(double alt);

    double alt() const;

    void setAltBaro(double alt);

    double altBaro() const;

    void setElevation(double &elevation);

    double elevation() const;

    void setTrueAirSpeed(double tas);

    double trueAirSpeed() const;

  private:
    QTime m_time;
		LatLng m_pos;
		double m_alt;
		double m_altBaro;
    double m_elevation;
    double m_tas;
};

#endif
