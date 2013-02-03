#include "testserialport.h"

TestSerialPort::TestSerialPort()
{
}

TestSerialPort::~TestSerialPort()
{
}

int TestSerialPort::Perform()
{
	try 
	{
		SerialPort pstr("/dev/ttyS0 9600 8N1 None");
		SerialPort pparam("/dev/ttyS0", 9600, 8, SerialPort::ParityNone, 1, SerialPort::FlowControlNone);
		SerialPort pcpy = pstr;
	
		int kk = 1;
	} 
	catch (Exception *e) 
	{
		delete e;
	}
	
	return 0;
}
