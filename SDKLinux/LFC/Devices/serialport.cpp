#include "serialport.h"
#include "deviceexception.h"
#include "../Text/text.h"
#include "../Collections/collection.h"
#include "../nint.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void SerialPort::init(const Text &deviceName, int speed, int dataBits, int parity, int stopBits, int flowControl)
{
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
		throw new DeviceException("An example of accepted format is '/dev/ttyX 115200 8N1 None'", __FILE__, __LINE__, __func__);		
	}
	if (!params[0]->StartsWith("/dev/tty")) 
	{
		params.DeleteAndClear();
		throw new DeviceException("Serial device must be of the kind '/dev/ttyX'", __FILE__, __LINE__, __func__);				
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
	
	if (!params[2]->Length() != 3) 
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
	
	Text strStopBits = params[2]->SubText(3, 1);
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

	return *portDeviceName + " " + portSpeed + " " + portDataBits + strPar + portStopBits + " " + strFlowControl;
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
}

int SerialPort::Read(char *buffer, int lonBuffer)
{
	
}

int SerialPort::Write(const char *buffer, int lonBuffer)
{
	
}