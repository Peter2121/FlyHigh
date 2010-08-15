/***************************************************************************
 *   Copyright (C) 2004 by Alex Graf                                       *
 *   grafal@sourceforge.net                                                         *
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

#include <qcursor.h>
#include <qmessagebox.h>
#include <qtoolbox.h>
#include <qwidget.h>
#include <qwidgetstack.h>
#include <qstatusbar.h>
#include <qprogressbar.h>
#include <qfile.h>
#include <qfiledialog.h>

#include "CorrFrame6015Impl.h"
#include "VarioFrame6015Impl.h"
#include "AcousticFrame6015Impl.h"
#include "VelocityFrame6015Impl.h"
#include "GPSFrame6015Impl.h"
#include "DisplayFrame6015Impl.h"
#include "DeviceFrame6015Impl.h"
#include "IFlyHighRC.h"
#include "MemoryFrame6015Impl.h"
#include "ProgressDlg.h"
#include "UnitFrame6015Impl.h"
#include "Frame6015.h"
#include "MainFrame6015Impl.h"
#include "IGPSDevice.h"

MainFrame6015Impl::MainFrame6015Impl(QWidget* parent, const char* name, WFlags fl)
	:MainFrame6015(parent,name,fl)
{
	QWidget *pWidget;
	VelocityFrame6015Impl *pVelocityFrame6015;
	AcousticFrame6015Impl *pAcousticFrame6015;
	VarioFrame6015Impl *pVarioFrame6015;
	CorrFrame6015Impl *pCorrFrame6015;
	GPSFrame6015Impl *pGPSFrame6015;
	DisplayFrame6015Impl *pDisplayFrame6015;
	DeviceFrame6015Impl *pDeviceFrame6015;
	MemoryFrame6015Impl *pMemoryFrame6015;
	UnitFrame6015Impl *pUnitFrame6015;
	int pos = 0;
	
	m_fileName = "";
	
	// make a clean table
	pWidget = toolBox->item(0);
	toolBox->removeItem(pWidget);
	pWidget = widgetStack->widget(0);
	widgetStack->removeWidget(pWidget);
	
	// Correction
	pCorrFrame6015 = new CorrFrame6015Impl(widgetStack);
	addPage(pCorrFrame6015, &pos);
	pCorrFrame6015->setEnabled(true);
	m_frameList.push_back(pCorrFrame6015);
	
	// Vario
	pVarioFrame6015 = new VarioFrame6015Impl(widgetStack);
	addPage(pVarioFrame6015, &pos);
	m_frameList.push_back(pVarioFrame6015);

	// Acoustic
	pAcousticFrame6015 = new AcousticFrame6015Impl(widgetStack);
	addPage(pAcousticFrame6015, &pos);
	m_frameList.push_back(pAcousticFrame6015);
	
	// Velocity
	pVelocityFrame6015 = new VelocityFrame6015Impl(widgetStack);
	addPage(pVelocityFrame6015, &pos);
	m_frameList.push_back(pVelocityFrame6015);
	
	// GPS
	pGPSFrame6015 = new GPSFrame6015Impl(widgetStack);
	addPage(pGPSFrame6015, &pos);
	m_frameList.push_back(pGPSFrame6015);

	// Device
	pDeviceFrame6015 = new DeviceFrame6015Impl(widgetStack);
	addPage(pDeviceFrame6015, &pos);
	m_frameList.push_back(pDeviceFrame6015);
	
	// Memory
	pMemoryFrame6015 = new MemoryFrame6015Impl(widgetStack);
	addPage(pMemoryFrame6015, &pos);
	m_frameList.push_back(pMemoryFrame6015);
	
	// Display
	pDisplayFrame6015 = new DisplayFrame6015Impl(widgetStack);
	addPage(pDisplayFrame6015, &pos);
	m_frameList.push_back(pDisplayFrame6015);
	
	// Unit
	pUnitFrame6015 = new UnitFrame6015Impl(widgetStack);
	addPage(pUnitFrame6015, &pos);
	m_frameList.push_back(pUnitFrame6015);
	
/*	m_pProgressBar = new QProgressBar(statusBar());
	m_pProgressBar->setProgress(0, ft_MemSize/ft_PageSize);
	m_pProgressBar->setShown(false);
	statusBar()->addWidget(m_pProgressBar, 1, true);*/
}

void MainFrame6015Impl::addPage( QWidget * pFrame6015, int * pPos)
{
	QWidget *pWidget;
	
	widgetStack->addWidget(pFrame6015, *pPos);
	(*pPos)++;
	pWidget = new QWidget(toolBox,  pFrame6015->caption());
	pWidget->setBackgroundMode(QWidget::PaletteBackground);
	toolBox->addItem(pWidget,  pFrame6015->caption());
}

void MainFrame6015Impl::read()
{
	ProgressDlg dlg(this);
	
	dlg.beginProgress("read memory...", IGPSDevice::pInstance());
	updateFrames();
	dlg.endProgress();
}

void MainFrame6015Impl::write()
{
	ProgressDlg dlg(this);
		
	if(QMessageBox::question(this, tr("write configuration"),
		tr("Write current configuration to the device?"), 1, 2) == 1)
	{
		dlg.beginProgress("write memory...", IGPSDevice::pInstance());
		storeFrames();
		dlg.endProgress();
	}
}

void MainFrame6015Impl::storeFrames()
{
	FrameListType::iterator it;
	
	// update Frames
	for(it=m_frameList.begin(); it!=m_frameList.end(); it++)
	{
		(*it)->store();
	}
}

void MainFrame6015Impl::updateFrames()
{
	FrameListType::iterator it;
	
	// update Frames
	for(it=m_frameList.begin(); it!=m_frameList.end(); it++)
	{
		(*it)->update();
	}
}

#include "MainFrame6015Impl.moc"
