/********************************************************************
** @source JEEPS serial port low level functions
**
** @author Copyright (C) 1999,2000 Alan Bleasby
** @version 1.0
** @modified December 28th 1999 Alan Bleasby. First version
** @modified June 29th 2000 Alan Bleasby. NMEA additions
** @@
** 
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Library General Public
** License as published by the Free Software Foundation; either
** version 2 of the License, or (at your option) any later version.
** 
** This library is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Library General Public License for more details.
** 
** You should have received a copy of the GNU Library General Public
** License along with this library; if not, write to the
** Free Software Foundation, Inc., 59 Temple Place - Suite 330,
** Boston, MA  02111-1307, USA.
********************************************************************/
#include "gps.h"

#ifdef __LINUX__
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <sys/ioctl.h>
	#include <termios.h>
	#include <errno.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <time.h>
	#include <sys/time.h>

	static struct termios gps_ttysave;
#endif

/* @func GPS_Serial_Restoretty ***********************************************
**
** Save tty information for the serial post to be used
**
** @param [r] port [const char *] port e.g. ttyS1
**
** @return [int32] false upon error
************************************************************************/

int32 GPS_Serial_Savetty(const char *port)
{
#ifdef __LINUX__
    int32 fd;
    
    if((fd = open(port, O_RDWR|O_NDELAY))==-1)
    {
	perror("open");
	gps_errno = SERIAL_ERROR;
	GPS_Error("SERIAL: Cannot open serial port");
	return 0;
    }
    
    if(tcgetattr(fd,&gps_ttysave)==-1)
    {
	perror("tcgetattr");
	gps_errno = HARDWARE_ERROR;
	GPS_Error("SERIAL: tcgetattr error");
	return 0;
    }


    if(!GPS_Serial_Close(fd))
    {
	gps_errno = SERIAL_ERROR;
	GPS_Error("GPS_Serial_Savetty: Close error");
	return 0;
    }
#endif
    return 1;
}


/* @func GPS_Serial_Restoretty ***********************************************
**
** Restore serial post to condition before AJBGPS called
**
** @param [r] port [const char *] port e.g. ttyS1
**
** @return [int32] false upon error
************************************************************************/

int32 GPS_Serial_Restoretty(const char *port)
{
#ifdef __LINUX__
    int32 fd;
    
    if((fd = open(port, O_RDWR|O_NDELAY))==-1)
    {
	perror("open");
	gps_errno = HARDWARE_ERROR;
	GPS_Error("SERIAL: Cannot open serial port");
	return 0;
    }
    
    if(tcsetattr(fd, TCSAFLUSH, &gps_ttysave)==-1)
    {
	perror("ioctl");
	gps_errno = HARDWARE_ERROR;
	GPS_Error("SERIAL: tcsetattr error");
	return 0;
    }
#endif
    return 1;
}



/* @func GPS_Serial_Open ***********************************************
**
** Open a serial port 8bits 1 stop bit 9600 baud
**
** @param [w] fd [int32 *] file descriptor
** @param [r] port [const char *] port e.g. ttyS1
**
** @return [int32] false upon error
************************************************************************/

int32 GPS_Serial_Open(int32 *fd, const char *port)
{
#ifdef __LINUX__
    struct termios tty;
    

    if((*fd = open(port, O_RDWR | O_NDELAY | O_NOCTTY))==-1)
    {
	perror("open");
	GPS_Error("SERIAL: Cannot open serial port");
	gps_errno = SERIAL_ERROR;
	return 0;
    }


    if(tcgetattr(*fd,&tty)==-1)
    {
	perror("tcgetattr");
	GPS_Error("SERIAL: tcgetattr error");
	gps_errno = SERIAL_ERROR;
	return 0;
    }

    tty.c_cflag |= (CREAD | CS8 | CSIZE | CLOCAL);
    cfsetospeed(&tty,B9600);
    cfsetispeed(&tty,B9600);
    
    tty.c_lflag &= 0x0;
    tty.c_iflag &= 0x0;
    tty.c_oflag &= 0x0;
    
    
    if(tcsetattr(*fd,TCSANOW,&tty)==-1)
    {
	perror("tcsetattr");
	GPS_Error("SERIAL: tcsetattr error");
	return 0;
    }
#endif
    return 1;
}



/* @func GPS_Serial_Flush ***********************************************
**
** Flush the serial lines
**
** @param [w] fd [int32] file descriptor
**
** @return [int32] false upon error
************************************************************************/
int32 GPS_Serial_Flush(int32 fd)
{
#ifdef __LINUX__
    if(tcflush(fd,TCIOFLUSH))
    {
	perror("tcflush");
	GPS_Error("SERIAL: tcflush error");
	gps_errno = SERIAL_ERROR;
	return 0;
    }
#endif
    return 1;
}



/* @func GPS_Serial_Close ***********************************************
**
** Close serial port
**
** @param [r] fd [int32 ] file descriptor
** @param [r] port [const char *] port e.g. ttyS1
**
** @return [int32] false upon error
************************************************************************/

int32 GPS_Serial_Close(int32 fd)
{
#ifdef __LINUX__
    if(close(fd)==-1)
    {
	perror("close");
	GPS_Error("SERIAL: Error closing serial port");
	gps_errno = SERIAL_ERROR;
	return 0;
    }
#endif
    return 1;
}


/* @func GPS_Serial_Chars_Ready *****************************************
**
** Query port to see if characters are waiting to be read
**
** @param [r] fd [int32 ] file descriptor
**
** @return [int32] true if chars waiting
************************************************************************/

int32 GPS_Serial_Chars_Ready(int32 fd)
{
#ifdef __LINUX__
    fd_set rec;
    struct timeval t;

    FD_ZERO(&rec);
    FD_SET(fd,&rec);

    t.tv_sec  = 0;
    t.tv_usec = 0;

    (void) select(fd+1,&rec,NULL,NULL,&t);
    if(FD_ISSET(fd,&rec))
	return 1;
#endif
    return 0;
}



/* @func GPS_Serial_Wait ***********************************************
**
** Wait 80 milliseconds before testing for input. The GPS delay
** appears to be around 40-50 milliseconds. Doubling the value is to
** allow some leeway. 
**
** @param [r] fd [int32 ] file descriptor
**
** @return [int32] true if serial chars waiting
************************************************************************/

int32 GPS_Serial_Wait(int32 fd)
{
#ifdef __LINUX__
    fd_set rec;
    struct timeval t;

    FD_ZERO(&rec);
    FD_SET(fd,&rec);

    t.tv_sec  = 0;
    t.tv_usec = usecDELAY;

    (void) select(fd+1,&rec,NULL,NULL,&t);
    if(FD_ISSET(fd,&rec))
	return 1;
#endif
    return 0;
}



/* @func GPS_Serial_On *****************************************
**
** Set up port
**
** @param [r] port [const char *] port
** @param [w] fd [int32 *] file descriptor
**
** @return [int32] success
************************************************************************/

int32 GPS_Serial_On(const char *port, int32 *fd)
{
#ifdef __LINUX__
    if(!GPS_Serial_Savetty(port))
    {
	GPS_Error("Cannot access serial port");
	gps_errno = SERIAL_ERROR;
	return 0;
    }
    
    if(!GPS_Serial_Open(fd,port))
    {
	GPS_Error("Cannot open serial port");
	gps_errno = SERIAL_ERROR;
	return 0;
    }
#endif
    return 1;
}



/* @func GPS_Serial_Off ***********************************************
**
** Done with port
**
** @param [r] port [const char *] port
** @param [r] fd [int32 ] file descriptor
**
** @return [int32] success
************************************************************************/

int32 GPS_Serial_Off(const char *port, int32 fd)
{
#ifdef __LINUX__
    if(!GPS_Serial_Close(fd))
    {
	GPS_Error("Error Closing port");
	gps_errno = HARDWARE_ERROR;
	return 0;
    }
    
    if(!GPS_Serial_Restoretty(port))
    {
	GPS_Error("Error restoring port");
	gps_errno = HARDWARE_ERROR;
	return 0;
    }
#endif
    return 1;
}







/* @func GPS_Serial_Open_NMEA ******************************************
**
** Open a serial port 8bits 1 stop bit 4800 baud
**
** @param [w] fd [int32 *] file descriptor
** @param [r] port [const char *] port e.g. ttyS1
**
** @return [int32] false upon error
************************************************************************/

int32 GPS_Serial_Open_NMEA(int32 *fd, const char *port)
{
#ifdef __LINUX__
    struct termios tty;
    

    if((*fd = open(port, O_RDWR | O_NDELAY | O_NOCTTY))==-1)
    {
	perror("open");
	GPS_Error("SERIAL: Cannot open serial port");
	gps_errno = SERIAL_ERROR;
	return 0;
    }


    if(tcgetattr(*fd,&tty)==-1)
    {
	perror("tcgetattr");
	GPS_Error("SERIAL: tcgetattr error");
	gps_errno = SERIAL_ERROR;
	return 0;
    }

    
    tty.c_cflag |= (CREAD | CS8 | CSIZE | CLOCAL);
    cfsetospeed(&tty,B4800);
    cfsetispeed(&tty,B4800);
    
    tty.c_lflag &= 0x0;
    tty.c_iflag &= 0x0;
    tty.c_oflag &= 0x0;
    
    
    if(tcsetattr(*fd,TCSANOW,&tty)==-1)
    {
	perror("tcsetattr");
	GPS_Error("SERIAL: tcsetattr error");
	return 0;
    }
#endif
    return 1;
}







/* @func GPS_Serial_On_NMEA ********************************************
**
** Set up port for NMEA
**
** @param [r] port [const char *] port
** @param [w] fd [int32 *] file descriptor
**
** @return [int32] success
************************************************************************/
int32 GPS_Serial_On_NMEA(const char *port, int32 *fd)
{
#ifdef __LINUX__
    if(!GPS_Serial_Savetty(port))
    {
	GPS_Error("Cannot access serial port");
	gps_errno = SERIAL_ERROR;
	return 0;
    }
    
    if(!GPS_Serial_Open_NMEA(fd,port))
    {
	GPS_Error("Cannot open serial port");
	gps_errno = SERIAL_ERROR;
	return 0;
    }
#endif
    return 1;
}
