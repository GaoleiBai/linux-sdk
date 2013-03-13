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
#include "testnetwork.h"
#include "../LFC/LFC.h"

TestNetwork::TestNetwork()
{
}

TestNetwork::~TestNetwork()
{
}

int TestNetwork::Perform()
{
	class SimpleServerController : public IPV4GenericServerController {
	public:
		virtual void *OnManageClientConnection(IPV4SocketAddress *clientAddress) { 
			StdOut::PrintLine(clientAddress->ToText());
			
			// We will accept all connections
			int kk = 1;
			if (kk == 0) return NULL;
			return this;
		}
				
		virtual void *OnManageClientSocket(Socket *clientSocket) {
			int operation = 0;
			while (true) {
				clientSocket->Read((char *)&operation, sizeof(operation), -1);
				if (operation == 0) break;
				else if (operation == 1) clientSocket->WriteLine("GenericServer example");
				else StdOut::PrintLine((Text)"Unknown " + operation + " operation.");
			}
		}
	};
	
	try {
		SimpleServerController c;
		IPV4GenericServer server(30001);
		server.OnManageClientConnection(&c, (Delegate)&SimpleServerController::OnManageClientConnection);
		server.OnManageClientSocket(&c, (Delegate)&SimpleServerController::OnManageClientSocket);

		Thread::Sleep(1000000);
		Socket s(Socket::SockDomainInetV4, Socket::SockTypeStream, Socket::SockProtocolNone);
		s.Bind(IPV4SocketAddress("localhost", IPV4SocketAddress::PortAny));
		s.Connect(IPV4SocketAddress("localhost", 30001));
		
		for (int i = 0; i < 100; i++) {
			int operation = 1;
			s.Write((char *)&operation, sizeof(operation));
			Text t = s.ReadLine(5000000000);
			if (t != "GenericServer example")
				throw new Exception("Server not responding to the demanded operation", __FILE__, __LINE__, __func__);		
			StdOut::PrintLine((Text)"Client iteration " + (i + 1) + "/100");
		}
	} catch (Exception *e) {
		delete e;
		return -1;
	}
	
	int kk = 0;
}
