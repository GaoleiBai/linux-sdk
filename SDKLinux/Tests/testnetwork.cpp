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
		void Read(Socket *s, char *buffer, int lonBuffer, long nanoseconds_timeout) {
			int leido = 0;
			while (leido < lonBuffer) {
				// All socket operations are unblocking, so wait and then read
				if (!s->WaitForDataComming(nanoseconds_timeout))
					throw new Exception("No data comming from buffer", __FILE__, __LINE__, __func__);
				leido += s->Read(buffer + leido, lonBuffer - leido);
			}
		}
		
	public:
		virtual void *OnManageClientConnection(IPV4SocketAddress *clientAddress) { 
			StdOut::PrintLine(clientAddress->ToText()); 
		}
				
		virtual void *OnManageClientSocket(Socket *clientSocket) {
			int operation = 0;
			while (true) {
				Read(clientSocket, (char *)&operation, sizeof(operation), -1);
				if (operation == 0) break;
				else if (operation == 1) clientSocket->WriteLine("GenericServer example");
				else StdOut::PrintLine((Text)"Unknown " + operation + " operation.");
			}
		}
	};
	
	SimpleServerController c;
	IPV4GenericServer server(30001);
	server.OnManageClientConnection(&c, (Delegate)&SimpleServerController::OnManageClientConnection);
	server.OnManageClientSocket(&c, (Delegate)&SimpleServerController::OnManageClientSocket);
}
