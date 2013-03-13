/* 
* LFC Library - Linux toolkit
* 
* Copyright (C) 2012, 2013 Daniel Mosquera Villanueva 
* (milkatoffeecuco@gmail.com)
* This file is part of LFC Library.
* 
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library. If not, see <http://www.gnu.org/licenses/>.
*
**/
#include "serialport.h"
#include "deviceexception.h"
#include "../Text/text.h"
#include "../Collections/collection.h"
#include "../nint.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>

void SerialPort::init(const Text &deviceName, int speed, int dataBits, int parity, int stopBits, int flowControl)
{
	if (!((Text *)&deviceName)->StartsWith("/dev/")) 
		throw new DeviceException("Serial device must be of the kind '/dev/X'", __FILE__, __LINE__, __func__);				
		
	speed_t s = -1;
	if (speed == 50) s = B50;
	else if (speed == 75) s = B75;
	else if (speed == 110) s = B110;
	else if (speed == 134) s = B134;
	else if (speed == 150) s = B150;
	else if (speed == 200) s = B200;
	else if (speed == 300) s = B300;
	else if (speed == 600) s = B600;
	else if (speed == 1200) s = B1200;
	else if (speed == 1800) s = B1800;
	else if (speed == 2400) s = B2400;
	else if (speed == 4800) s = B4800;
	else if (speed == 9600) s = B9600;
	else if (speed == 19200) s = B19200;
	else if (speed == 38400) s = B38400;
	else if (speed == 57600) s = B57600;
	else if (speed == 115200) s = B115200;
	else if (speed == 230400) s = B230400;
	else throw new Exception((Text)"Requested speed " + speed + " is not allowed", __FILE__, __LINE__, __func__);
	
	tcflag_t d = -1;
	if (dataBits == 8) d = CS8;
	else if (dataBits == 7) d = CS7;
	else if (dataBits == 6) d = CS6;
	else if (dataBits == 5) d = CS5;
	else throw new Exception((Text)"Requested data bits " + dataBits + " is not allowed", __FILE__, __LINE__, __func__);
	
	if (parity == 0) portParity = 0;		// None
	else if (parity == 1) portParity = 1;	// Odd
	else if (parity == 2) portParity = 2;	// Even
	else if (parity == 3) portParity = 3;	// Space
	else throw new Exception((Text)"Requested parity " + parity + " is not allowed", __FILE__, __LINE__, __func__);
	
	if (stopBits == 1) portStopBits = 1;
	else if (stopBits == 2) portStopBits = 2;
	else throw new Exception((Text)"Requested stop bits " + stopBits + " not allowed", __FILE__, __LINE__, __func__);
	
	if (flowControl == 0) portFlowControl = 0;
	else if (flowControl == 1) portFlowControl = 1;
	else if (flowControl == 2) portFlowControl = 2;
	else throw new Exception((Text)"Requested flow control " + flowControl + " not allowed", __FILE__, __LINE__, __func__);
	
	portSpeed = s;
	portDataBits = d;
	portDeviceName = new Text(deviceName);
	
	fd = -1;
}

SerialPort::SerialPort(const Text &deviceName, int speed, int dataBits, int parity, int stopBits, int flowControl)
{
	init(deviceName, speed, dataBits, parity, stopBits, flowControl);
}

SerialPort::SerialPort(const Text &config)
{
	Collection<Text *> params = ((Text *)&config)->Split(" ", false);
	
	if (params.Count() != 4) 
	{
		params.DeleteAndClear();
		throw new DeviceException("An example of accepted format is '/dev/X 115200 8N1 None'", __FILE__, __LINE__, __func__);		
	}
	if (!params[0]->StartsWith("/dev/")) 
	{
		params.DeleteAndClear();
		throw new DeviceException("Serial device must be of the kind '/dev/X'", __FILE__, __LINE__, __func__);				
	}
	
	int speed = NInt::Parse(*params[1]);
	if (speed != 50 && speed != 75 && speed != 110 && speed != 134 && speed != 150 && speed != 200 &&
		speed != 300 && speed != 600 && speed != 1200 && speed != 1800 && speed != 2400 && speed != 4800 &&
		speed != 9600 && speed != 19200 && speed != 38400 && speed != 57600 && speed != 115200 &&
		speed != 230400) 
	{
		params.DeleteAndClear();
		throw new DeviceException("Speed must be one of 50, 75, 110, 134, 150, 200, 300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400", __FILE__, __LINE__, __func__);
	}
	
	if (params[2]->Length() != 3) 
	{
		params.DeleteAndClear();
		throw new DeviceException("DataBits, Parity and Stop bits must be indicated like '8N1'", __FILE__, __LINE__, __func__);				
	}
	
	int dataBits = NInt::Parse(params[2]->SubText(0, 1));
	if (dataBits != 8 && dataBits != 7 && dataBits != 6 && dataBits != 5) 
	{
		params.DeleteAndClear();
		throw new DeviceException("Data bits must be 8, 7, 6 or 5", __FILE__, __LINE__, __func__);
	}
	
	Text strParity = params[2]->SubText(1, 1);
	if (strParity != "N" && strParity != "O" && strParity != "E" && strParity != "S") 
	{
		params.DeleteAndClear();
		throw new DeviceException("Parity must be N, O, E or S", __FILE__, __LINE__, __func__);
	}
	int parity = 0;
	if (strParity == "N") parity = 0;
	else if (strParity == "O") parity = 1;
	else if (strParity == "E") parity = 2;
	else if (strParity == "S") parity = 3;
	
	Text strStopBits = params[2]->SubText(2, 1);
	if (strStopBits != "1" && strStopBits != "2") 
	{
		params.DeleteAndClear();
		throw new DeviceException("Stop bits must be 1 or 2", __FILE__, __LINE__, __func__);
	}
	int stopBits = NInt::Parse(strStopBits);
	
	if (*params[3] != "None" && *params[3] != "Hardware" && *params[3] != "XON/XOFF") 
	{
		params.DeleteAndClear();
		throw new DeviceException("Flow control must be None, Hardware of XOF/XOFF", __FILE__, __LINE__, __func__);
	}
	int flowControl = 0;
	if (*params[3] == "None") flowControl = 0;
	else if (*params[3] == "Hardware") flowControl = 1;
	else if (*params[3] == "XON/XOFF") flowControl = 2;
	
	init(*params[0], speed, dataBits, parity, stopBits, flowControl);
	params.DeleteAndClear();
}

SerialPort::SerialPort(const SerialPort &port)
{
	portDeviceName = new Text(*port.portDeviceName);
	portSpeed = port.portSpeed;
	portDataBits = port.portDataBits;
	portParity = port.portParity;
	portStopBits = port.portStopBits;
	portFlowControl = port.portFlowControl;
	fd = -1;
}

SerialPort::~SerialPort()
{
	Close();
	delete portDeviceName;
}

Text SerialPort::ToText()
{
	Text strPar;
	if (portParity == 0) strPar = "N";
	else if (portParity == 1) strPar = "O";
	else if (portParity == 2) strPar = "E";
	else if (portParity == 3) strPar = "S";
	
	Text strFlowControl;
	if (portFlowControl == 0) strFlowControl = "None";
	else if (portFlowControl == 1) strFlowControl = "Hardware";
	else if (portFlowControl == 2) strFlowControl = "XON/XOFF";
	
	Text strSpeed;
	if (portSpeed == B50) strSpeed = "50";
	else if (portSpeed == B75) strSpeed = "75";
	else if (portSpeed == B110) strSpeed = "110";
	else if (portSpeed == B134) strSpeed = "134";
	else if (portSpeed == B150) strSpeed = "150";
	else if (portSpeed == B200) strSpeed = "200";
	else if (portSpeed == B300) strSpeed = "300";
	else if (portSpeed == B600) strSpeed = "600";
	else if (portSpeed == B1200) strSpeed = "1200";
	else if (portSpeed == B1800) strSpeed = "1800";
	else if (portSpeed == B2400) strSpeed = "2400";
	else if (portSpeed == B4800) strSpeed = "4800";
	else if (portSpeed == B9600) strSpeed = "9600";
	else if (portSpeed == B19200) strSpeed = "19200";
	else if (portSpeed == B38400) strSpeed = "38400";
	else if (portSpeed == B57600) strSpeed = "57600";
	else if (portSpeed == B115200) strSpeed = "115200";
	else if (portSpeed == B230400) strSpeed = "230400";
	
	Text strDataBits;
	if (portDataBits == CS8) strDataBits = "8";
	else if (portDataBits == CS7) strDataBits = "7";
	else if (portDataBits == CS6) strDataBits = "6";
	else if (portDataBits == CS5) strDataBits = "5";

	return *portDeviceName + " " + strSpeed + " " + strDataBits + strPar + portStopBits + " " + strFlowControl;
}

void SerialPort::Open()
{
	if (fd != -1) return;
	
	char cadena[1001];
	portDeviceName->GetAnsiString(cadena, 1000);
	
	// Se abre el dispositivo
	errno = 0;
	fd = open(cadena, O_RDWR | O_NOCTTY | O_NDELAY ); 
	if (fd == -1) throw new DeviceException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	
	// Se configura el puerto serie para no bloquearse si no hay datos en el buffer de entrada
	if (fcntl(fd, F_SETFL, FNDELAY) == -1) {
		close(fd);
		fd = -1;
		throw new DeviceException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	}	
	
	// Se configura el puerto serie
	struct termios pattr;
	if (tcgetattr(fd, &pattr) == -1) {
		close(fd);
		fd = -1;
		throw new DeviceException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	}
	
	// Port parity
	if (portParity == 0) {				// None
		pattr.c_cflag &= ~PARENB;
	} else if (portParity == 1) {		// Odd
		pattr.c_cflag |= PARENB;
		pattr.c_cflag |= PARODD;
		// Also activate input parity checking
		pattr.c_iflag |= (INPCK | ISTRIP);			
	} else if (portParity == 2) {		// Even
		pattr.c_cflag |= PARENB;
		pattr.c_cflag &= ~PARODD;
		// Also activate input parity checking
		pattr.c_iflag |= (INPCK | ISTRIP);			
	} else if (portParity == 3) {		// Space
		pattr.c_cflag &= ~PARENB;
	}
	
	// Stop bits
	if (portStopBits == 1) {
		pattr.c_cflag &= ~CSTOPB;		
	} else if (portStopBits == 2) {
		pattr.c_cflag |= CSTOPB;		
	}
	
	pattr.c_cflag |= (CLOCAL | CREAD);
    pattr.c_cflag &= ~CSIZE; 		// Port data bits
	pattr.c_cflag |= portDataBits;
	pattr.c_cflag &= ~CBAUD;		// Port speed
    pattr.c_cflag |= portSpeed;
	cfsetispeed(&pattr, portSpeed);
	cfsetospeed(&pattr, portSpeed);
	pattr.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);	// Raw input mode
	pattr.c_oflag &= ~OPOST;							// Raw output mode
	
	// Flow control
	if (portFlowControl == 0) {
		pattr.c_iflag &= ~(IXON | IXOFF | IXANY);	// Disable software port control
		pattr.c_cflag &= ~CRTSCTS;					// Disable hardware flow control
	} else if (portFlowControl == 1) {
		pattr.c_iflag &= ~(IXON | IXOFF | IXANY);	// Disable software port control
		pattr.c_cflag |= CRTSCTS;					// Enable hardware flow control
	} else if (portFlowControl == 2) {
		pattr.c_iflag |= (IXON | IXOFF | IXANY);	// Enable software port control
		pattr.c_cflag &= ~CRTSCTS;					// Disable hardware flow control		
	}
	
	// Input parity
	if (portParity == 1 || portParity == 2) {
		pattr.c_iflag |= (INPCK | ISTRIP);
	}
	
	// Don't map input CR to NL
	pattr.c_iflag &= ~ICRNL;
	
	// Minimum characters to read = 0
	pattr.c_cc[VMIN] = 0;
	pattr.c_cc[VTIME] = 0;
	
	// Set port attributes
	if (tcsetattr(fd, TCSANOW, &pattr) == -1) {
		close(fd);
		fd = -1;
		throw new DeviceException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	}
}

void SerialPort::Close()
{
	if (fd == -1) return;
	errno = 0;
	if (close(fd) == -1) 
		throw new DeviceException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	fd = -1;
}

void SerialPort::GetSignalBits(bool &DTR, bool &RTS, bool &DSR, bool &CTS, bool &DCD, bool &RING)
{
	if (fd == -1)
		throw new DeviceException("Can only perform actions on an open port", __FILE__, __LINE__, __func__);
		
	int status = 0;
	if (ioctl(fd, TIOCMGET, &status) == -1)
		throw new DeviceException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	DTR = status & TIOCM_DTR != 0;
	RTS = status & TIOCM_RTS != 0;
	DSR = status & TIOCM_LE != 0;
	CTS = status & TIOCM_CTS != 0;
	DCD = status & TIOCM_CAR != 0;
	RING = status & TIOCM_RI != 0;
}

void SerialPort::SetSignalBits(bool DTR, bool RTS, bool DSR, bool CTS, bool DCD, bool RING)
{
	if (fd == -1)
		throw new DeviceException("Can only perform actions on an open port", __FILE__, __LINE__, __func__);
		
	int status = 0;
	if (ioctl(fd, TIOCMGET, &status) == -1)
		throw new DeviceException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	if (DTR) status |= TIOCM_DTR;
	else status &= ~TIOCM_DTR;
	if (RTS) status |= TIOCM_RTS;
	else status &= ~TIOCM_RTS;
	if (DSR) status |= TIOCM_LE;
	else status &= ~TIOCM_LE;
	if (CTS) status |= TIOCM_CTS;
	else status &= ~TIOCM_LE;
	if (DCD) status |= TIOCM_CAR;
	else status &= ~TIOCM_CAR;
	if (RING) status |= TIOCM_RI;
	else status &= ~TIOCM_RI;
	if (ioctl(fd, TIOCMSET, &status) == -1)
		throw new DeviceException(Text::FromErrno(), __FILE__, __LINE__, __func__);
		
	// Syncing changes
	tcdrain(fd);
}

void SerialPort::WaitForSignalBits(bool DTR, bool RTS, bool DSR, bool CTS, bool DCD, bool RING)
{
	if (fd == -1)
		throw new DeviceException("Can only perform actions on an open port", __FILE__, __LINE__, __func__);
		
	int waitfor = 0;
	if (DTR) waitfor |= TIOCM_DTR;
	if (RTS) waitfor |= TIOCM_RTS;
	if (DSR) waitfor |= TIOCM_LE;
	if (CTS) waitfor |= TIOCM_CTS;
	if (DCD) waitfor |= TIOCM_CAR;
	if (RING) waitfor |= TIOCM_RI;
	if (ioctl(fd, TIOCMIWAIT, waitfor) == -1)
		throw new DeviceException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

int SerialPort::GetBytesAvaliable()
{
	if (fd == -1)
		throw new DeviceException("Can only perform actions on an open port", __FILE__, __LINE__, __func__);
		
	int avaliable = 0;
	if (ioctl(fd, FIONREAD, &avaliable) == -1)
		throw new DeviceException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	return avaliable;
}


