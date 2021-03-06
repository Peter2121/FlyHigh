/***************************************************************************
 *   Copyright (C) 2004 by Alex Graf                                       *
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

#ifndef GliderFormImpl_h
#define GliderFormImpl_h

#include "ui_GliderForm.h"
#include <Glider.h>

class GliderFormImpl: public QDialog, public Ui::GliderForm
{
	Q_OBJECT

	public:
		GliderFormImpl(QWidget* parent, const QString &caption, Glider *pGlider,
                   const Glider::GliderListType& gliderList);

    void setGlider(Glider *pGlider);

	protected slots:
		void accept();

	private:
		Glider *m_pGlider;

	  void select(QComboBox *pCombo, const QString &text);

	private slots:
		void updateGlider(int index);

};

#endif
