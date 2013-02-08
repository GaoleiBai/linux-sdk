/* Copyright (C) 2012, 2013
   Daniel Mosquera Villanueva (daniel.m.v@terra.es)
   This file is part of LFC Library.

   LFC Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   LFC Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with LFC Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA. or see http://www.gnu.org/licenses/. */
   
   
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
		char buffer[10000];
		
		// To test serial ports start a virtual serial loop with the command
		// socat -d -d PTY: PTY:
		SerialPort pstr("/dev/pts/3 9600 8N1 None");
		SerialPort pparam("/dev/pts/4", 9600, 8, SerialPort::ParityNone, 1, SerialPort::FlowControlNone);
		SerialPort pcpy = pparam;
		
		StdOut::PrintLine(pcpy.ToText());
		StdOut::PrintLine(pparam.ToText());
		if (pcpy.ToText() != pparam.ToText())
			throw new Exception("SerialPort::ToText error", __FILE__, __LINE__, __func__);
		
		pstr.Open();
		pparam.Open();
		
		pstr.Write("Hola\r\n", 6);
		memset(buffer, 0, sizeof(buffer));
		int leido = 0;
		while (leido < 6) {
			int res = pparam.Read(buffer + leido, 6 - leido);
			leido += res;
			if (res != 0) continue;
			pparam.WaitForDataComming(20000);
			int bytesAvaliable = pparam.GetBytesAvaliable();
			if (bytesAvaliable == 0) throw new Exception("SerialPort::WaitForDataComming", __FILE__, __LINE__, __func__);		
		}
		if (leido != 6) 
			throw new Exception("SerialPort::Read Write error", __FILE__, __LINE__, __func__);
		if (((Text)buffer) != "Hola\r\n") 
			throw new Exception("Serial port Read Write error", __FILE__, __LINE__, __func__);
			
		for (int i=0; i<256; i++) buffer[i] = i;
		pstr.Write(buffer, 256);
		memset(buffer, 0, sizeof(buffer));
		//usleep(1000000);
		leido = 0;
		while (leido < 256) {
			int res = pparam.Read(buffer, 10000);
			leido += res;
			if (res != 0) continue;
			pparam.WaitForDataComming(20000);
			int bytesAvaliable = pparam.GetBytesAvaliable();
			if (bytesAvaliable == 0) throw new Exception("SerialPort::WaitForDataComming", __FILE__, __LINE__, __func__);		
		}
		if (leido != 256) 
			throw new Exception("SerialPort::Read error", __FILE__, __LINE__, __func__);
		for (int i=0; i<256; i++) {
			char c = i;
			if (buffer[i] != c)
				throw new Exception("SerialPort::Read error", __FILE__, __LINE__, __func__);
		}
		
		Text strSerialize = "Serial port test\r\n";
		Serializator s(pstr);
		Serializator t(pparam);
		s.Put(strSerialize);
		Text *pStrDeserialize = (Text *)t.GetNObject();
		if (strSerialize != *pStrDeserialize) 
			throw new Exception("Serialization over SerialPort doesn't work", __FILE__, __LINE__, __func__);
		StdOut::PrintLine(*pStrDeserialize);
		
		
		pstr.Close();
		pparam.Close();
	
		int kk = 1;
	} 
	catch (Exception *e) 
	{
		delete e;
	}
	
	return 0;
}
