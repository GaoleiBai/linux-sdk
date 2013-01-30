#include "serialport.h"
#include "deviceexception.h"
#include "../Text/text.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

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
}

void SerialPort::Close()
{
	if (fd == -1) return;
	errno = 0;
	if (close(fd) == -1) 
		throw new DeviceException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}
