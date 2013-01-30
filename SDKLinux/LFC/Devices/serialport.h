#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "../n_object.h"
#include "../FileSystem/ifile.h"

class SerialPort : public NObject, public IFile {

public:
	SerialPort(const Text &deviceName);
	virtual ~SerialPort();
	
	void Open();
	void Close();

	Text ToText();

private:
	int f;
	Text *portDeviceName;
	int portSpeed;
	int portDataBits;
	int portParity;
	int portStopBits;

};

#endif // SERIALPORT_H
