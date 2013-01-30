#include "serialport.h"
#include "../Text/text.h"

SerialPort::SerialPort(const Text &deviceName)
{
	portDeviceName = new Text(deviceName);
	fd = -1;
}

SerialPort::~SerialPort()
{
	Close();
	delete portDeviceName;
}

Text SerialPort::ToText()
{
	return *portDeviceName;
}

void SerialPort::Open()
{
	//if (fd != -1) throw 
}

void SerialPort::Close()
{
	
}
