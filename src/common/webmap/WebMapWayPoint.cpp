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

#include <QObject>
#include <QWebFrame>
#include "WebMap.h"
#include "WebMapWayPoint.h"

#include <QDebug>

WebMapWayPoint::WebMapWayPoint(WebMap *pWebMap)
{
	QWebFrame *pFrame;

	m_pWebMap = pWebMap;
	pFrame = m_pWebMap->page()->mainFrame();
	QObject::connect(pFrame, SIGNAL(javaScriptWindowObjectCleared()), this,
                   SLOT(populateJavaScriptWindowObject()));
}

WebMapWayPoint::~WebMapWayPoint()
{
}

void WebMapWayPoint::populateJavaScriptWindowObject()
{
	m_pWebMap->page()->mainFrame()->addToJavaScriptWindowObject("WebMapWayPoint", this);
}
