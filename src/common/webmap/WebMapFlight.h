/***************************************************************************
 *   Copyright (C) 2011 by Alex Graf                                       *
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

#ifndef WebMapFlight_h
#define WebMapFlight_h

#include <QObject>
#include "FlightPointList.h"
#include "Photo.h"

class WebMap;

class WebMapFlight: public QObject
{
  Q_OBJECT

  public:
    WebMapFlight(WebMap *pWebMap);

    ~WebMapFlight();

    void init();

    void setFlightPointList(const QDate &date, const FlightPointList *pFpList);

    void setSogList(const FlightPointList::SogListType &sogList,
                    uint begin, uint end);

    void setVarioList(const FlightPointList::VarioListType &varioList,
                      uint begin, uint end);

    void setPhotoList(const Photo::PhotoListType &photoList);

    void showPlot();

    void setPlotEnable(bool en);

  private:
    WebMap *m_pWebMap;
    uint m_plotEn;
};

#endif
