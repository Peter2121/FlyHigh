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
#include "Account.h"

Account::Account()
{
	m_id = -1;
  m_oLCType = Account::XCONTEST;
}

int Account::id()
{
	return m_id;
}

void Account::setId(int id)
{
	m_id = id;
}

Account::OLCType Account::type() const
{
  return m_oLCType;
}

void Account::setType(OLCType type)
{
  m_oLCType = type;
}

QString Account::username() const
{
  return m_username;
}

void Account::setUsername(QString username)
{
  m_username = username;
}

QString Account::password() const
{
  return m_password;
}

void Account::setPassword(QString password)
{
  m_password = password;
}

QString Account::description() const
{
  return m_description;
}

void Account::setDescription(QString description)
{
  m_description = description;
}

QString Account::typeAsString(OLCType type)
{
  QString res = "unknown";
  switch(type)
  {
  case Account::XCONTEST:
    res = "XContest";
    break;
  }
  return res;
}
