/***************************************************************************
 *   Copyright (C) 2005 by Alex Graf                                       *
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

#ifndef Account_h
#define Account_h

#include <QString>
#include <QList>

class Account
{
	public:
    typedef QList<Account> AccountListType;

    typedef enum OLCType { XCONTEST } OLCType;

    Account();

		int id();
		void setId(int id);

    OLCType type() const;
    void setType(OLCType type);

    QString username() const;
    void setUsername(QString username);

    QString password() const;
    void setPassword(QString password);

    QString description() const;
    void setDescription(QString description);

    static QString typeAsString(OLCType type);

	private:
		int m_id;
    QString m_username;
    QString m_password;
    QString m_description;
    OLCType m_oLCType;
};

#endif
