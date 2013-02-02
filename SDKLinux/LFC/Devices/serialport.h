#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "../n_object.h"
#include "../FileSystem/ifile.h"
#include <termios.h>

class SerialPort : public NObject, public IFile {

public:
	SerialPort(const Text &deviceName, int speed, int dataBits, int parity, int stopBits, int flowControl);
	virtual ~SerialPort();
	
	static SerialPort FromTextConfiguration(const Text &config);

	void Open();
	void Close();

	Text ToText();
	
	virtual int Read(char *buffer, int lonBuffer);
	virtual int Write(const char *buffer, int lonBuffer);
	
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
	int fd;
	Text *portDeviceName;
	speed_t portSpeed;
	tcflag_t portDataBits;
	int portParity;
	int portStopBits;
	int portFlowControl;

};

#endif // SERIALPORT_H
