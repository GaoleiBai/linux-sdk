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
   
   
#include "ipv4genericserver.h"
#include "ipv4socketaddress.h"
#include "../Threading/thread.h"
#include "../Threading/mutexlock.h"
#include "../Text/text.h"

IPV4GenericServer::IPV4GenericServer(int port)
{
	mutex = new Mutex();
	clientSockets = new Collection<Socket *>();
	socket = new Socket(Socket::SockDomainInetV4, Socket::SockTypeStream, Socket::SockProtocolNone);
	socket->Bind(IPV4SocketAddress("127.0.0.1", port));
	socket->Listen(5);
	
	// Initialize delegations
	delegationOnManageNewConnection = NULL;
	delegationOnManageClient = NULL;
	
	// Launch server thread
	Thread *t = new Thread((Text)"Server thread", false);
	t->Launch(this, (Delegate)&IPV4GenericServer::serverAcceptFunction, t);
}

IPV4GenericServer::~IPV4GenericServer()
{
	// Server socket is closed to not accept more connections
	socket->Close();
	delete socket;
	
	// Kill all clients and wait for them to stop
	mutex->Lock();
	for (int i=0; i<clientSockets->Count(); i++) (*clientSockets)[i]->Close();
	mutex->Unlock();
	while (clientSockets->Count() != 0) Thread::Sleep(20000);
	
	delete clientSockets;
	delete mutex;
}

void IPV4GenericServer::OnNewCollection(NObject *object, Delegate delegate)
{
	MutexLock L(mutex);
	if (delegationOnManageNewConnection != NULL) delete delegationOnManageNewConnection;
	delegationOnManageNewConnection = new NDelegation(object, delegate);
}

void IPV4GenericServer::OnManageClient(NObject *object, Delegate delegate)
{
	MutexLock L(mutex);
	if (delegationOnManageClient != NULL) delete delegationOnManageClient;
	delegationOnManageClient = new NDelegation(object, delegate);
}

void *IPV4GenericServer::serverAcceptFunction(void *params)
{
	Thread *serverThread = (Thread *)params;
	IPV4SocketAddress address;
	
	while (true) {
		// Accept a new connection
		try {
			socket->WaitForDataGoing(-1);
			Socket *clientSocket = socket->Accept(address);
			
			try {
				// Manage the new connection
				if (delegationOnManageNewConnection != NULL)		
					if (delegationOnManageNewConnection->Execute(&address) == NULL)
						continue;
				
				// Check whether exists the client delegate
				if (delegationOnManageClient != NULL) continue;
				
				// Create a new thread to manage the client connection
				Thread *t = new Thread((Text)"Client " + address.ToText() + " thread", false);
				void *clientParams[3] = { t, new IPV4SocketAddress(address), clientSocket };
				t->Launch(this, (Delegate)&IPV4GenericServer::clientFunction, clientParams);
				
				// Add socket to clientSockets list
				mutex->Lock();
				clientSockets->Add(clientSocket);
				mutex->Unlock();
			} catch (Exception *e) {
				delete e;
			}
		} catch (Exception *e) {
			delete e;
			break;
		}
	}
	
	// Suicidal behavior
	delete serverThread;
}

void *IPV4GenericServer::clientFunction(void *params)
{
	void **vparams = (void **) params;
	Thread *clientThread = (Thread *)vparams[0];
	IPV4SocketAddress *address = (IPV4SocketAddress *)vparams[1];
	Socket *clientSocket = (Socket *)vparams[2];
	
	// Execute the client delegate passing the address to it
	delegationOnManageClient->Execute(address);
	
	// Remove clientSocket from clientSockets list
	mutex->Lock();
	clientSockets->Remove(clientSocket);
	mutex->Unlock();
	
	// Removing resources;
	delete clientSocket;
	delete address;
	delete clientThread;
}
