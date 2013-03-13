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
#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "../n_object.h"
#include "../FileSystem/ifile.h"
#include <termios.h>

class SerialPort : public NObject, public IFile {

public:
	SerialPort(const Text &deviceName, int speed, int dataBits, int parity, int stopBits, int flowControl);
	SerialPort(const Text &config);
	SerialPort(const SerialPort &port);
	virtual ~SerialPort();
	
	void Open();
	void Close();

	virtual Text ToText();
	
	void GetSignalBits(bool &DTR, bool &RTS, bool &DSR, bool &CTS, bool &DCD, bool &RING);
	void SetSignalBits(bool DTR, bool RTS, bool DSR, bool CTS, bool DCD, bool RING);
	void WaitForSignalBits(bool DTR, bool RTS, bool DSR, bool CTS, bool CDC, bool RING);
	int GetBytesAvaliable();
	
	static const int Speed50 = 50;
	static const int Speed75 = 75;
	static const int Speed110 = 110;
	static const int Speed134 = 134;
	static const int Speed150 = 150;
	static const int Speed200 = 200;
	static const int Speed300 = 300;
	static const int Speed600 = 600;
	static const int Speed1200 = 1200;
	static const int Speed1800 = 1800;
	static const int Speed2400 = 2400;
	static const int Speed4800 = 4800;
	static const int Speed9600 = 9600;
	static const int Speed19200 = 19200;
	static const int Speed38400 = 38400;
	static const int Speed57600 = 57600;
	static const int Speed115200 = 115200;
	static const int Speed230400 = 230400;
	
	static const int DataBits8 = 8;
	static const int DataBits7 = 7;
	static const int DataBits6 = 6;
	static const int DataBits5 = 5;
	
	static const int ParityNone = 0;
	static const int ParityOdd = 1;
	static const int ParityEven = 2;
	static const int ParitySpace = 3;
	
	static const int FlowControlNone = 0;
	static const int FlowControlHardware = 1;
	static const int FlowControlSoftware = 2;

private:
	void init(const Text &deviceName, int speed, int dataBits, int parity, int stopBits, int flowControl);

	Text *portDeviceName;
	speed_t portSpeed;
	tcflag_t portDataBits;
	int portParity;
	int portStopBits;
	int portFlowControl;

};

#endif // SERIALPORT_H
