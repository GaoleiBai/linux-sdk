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
		int operation = 1;
		s.Write((char *)&operation, sizeof(operation));
		Text t = s.ReadLine();
		if (t != "GenericServer example")
			throw new Exception("Server not responding to the demanded operation", __FILE__, __LINE__, __func__);		
	} catch (Exception *e) {
		delete e;
		return -1;
	}
}
