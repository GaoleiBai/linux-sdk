#include "serialport.h"
#include "../Text/text.h"

SerialPort::SerialPort(const Text &deviceName)
{
	portDeviceName = new Text(deviceName);
	f = -1;
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
	
}

void SerialPort::Close()
{
	
}
