/***************************************************************************
 *   Copyright (C) 2004 by grafal,,,                                       *
 *   grafal@spirit                                                         *
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

#ifndef IGCFileParser_h
#define IGCFileParser_h

#include <vector>
#include <qstring.h>
#include <qdatetime.h>
#include "WayPoint.h"
#include "FlightPointList.h"

class IGCFileParser
{
	public:
		IGCFileParser();

		void parse(const QByteArray &igcData);

		const QString& pilot();

		const QString& model();

		const QString& gliderId();

		const QDate& date();

		FlightPointList& flightPointList();

	private:
		QString m_pilot;
		QString m_model;
		QString m_gliderId;
		QDate m_date;
		FlightPointList m_flightPointList;
		int m_prevAlt;

		void parseHRecord(const char *record);

		void parseBRecord(const char *record, bool gpsAlt);

		void colonValue(const char *record, QString &str);
};

#endif
