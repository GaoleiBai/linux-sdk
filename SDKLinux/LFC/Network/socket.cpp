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
#include "socket.h"
#include "isocketaddress.h"
#include "networkexception.h"
#include "../Text/text.h"
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <typeinfo>

Socket::Socket(int socket)
{
	fd = socket;
}

Socket::Socket(int sock_domain, int sock_type, int sock_protocol)
{
	fd = ::socket(sock_domain, sock_type | SOCK_NONBLOCK, sock_protocol);
	if (fd == -1)
		throw new NetworkException(Text::FromErrno(), __FILE__, __LINE__, __func__);
		
	int keepAlive = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(keepAlive)) == -1)
		throw new NetworkException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

Socket::~Socket()
{
	Close();
}

void Socket::Close()
{
	if (fd == -1) return;		
	if (close(fd) == -1)
		throw new NetworkException(Text::FromErrno(), __FILE__, __LINE__, __func__);
		
	fd = -1;
}

void Socket::Bind(const ISocketAddress &address)
{
	if (fd == -1)
		throw new NetworkException("Cannot Bind a closed socket", __FILE__, __LINE__, __func__);
		
	if (typeid(address) == typeid(IPV4SocketAddress)) {
		IPV4SocketAddress *a = (IPV4SocketAddress *)&address;
		if (bind(fd, a->GetAddressData(), a->GetAddressLen()) == -1)
			throw new NetworkException(Text::FromErrno(), __FILE__, __LINE__, __func__);		
	} else {
		throw new NetworkException("Not implemented", __FILE__, __LINE__, __func__);
	}
}

void Socket::Connect(const ISocketAddress &address)
{
	Connect(address, 60000000000L);
}

void Socket::Connect(const ISocketAddress &address, long nanoseconds_timeout)
{
	if (fd == -1)
		throw new NetworkException("Cannot Connect a closed socket", __FILE__, __LINE__, __func__);
		
	if (typeid(address) == typeid(IPV4SocketAddress)) {
		IPV4SocketAddress *a = (IPV4SocketAddress *)&address;
		if (connect(fd, a->GetAddressData(), a->GetAddressLen()) == -1 && errno != EINPROGRESS)
			throw new NetworkException(Text::FromErrno(), __FILE__, __LINE__, __func__);
		if (errno == EINPROGRESS && !WaitForDataGoing(nanoseconds_timeout)) {
			Close();
			throw new NetworkException("Connection timeout. Socket closed.", __FILE__, __LINE__, __func__);
		}
	} else {
		throw new NetworkException("Not implemented", __FILE__, __LINE__, __func__);
	}
}

void Socket::Listen(int backlog)
{
	if (fd == -1)
		throw new NetworkException("Cannot Listen a closed socket", __FILE__, __LINE__, __func__);
		
	if (listen(fd, backlog) == -1)
		throw new NetworkException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

Socket *Socket::Accept(ISocketAddress &address)
{
	if (fd == -1)
		throw new NetworkException("Cannot Accept a closed socket", __FILE__, __LINE__, __func__);
		
	if (typeid(address) == typeid(IPV4SocketAddress)) {
		struct sockaddr_in addr;
		socklen_t socklen = sizeof(addr);
		
		// El socket se crea como no bloqueante, por lo que se espera a que lleguen los datos de la nueva conexión
		int clientSocket = -1;
		while (clientSocket == -1) {
			clientSocket = accept(fd, (sockaddr *)&addr, &socklen);
			if (clientSocket == -1 && errno != EAGAIN && errno != EWOULDBLOCK) {
				Close();
				throw new NetworkException(Text::FromErrno(), __FILE__, __LINE__, __func__);
			}
			if (clientSocket == -1 && !WaitForDataComming(-1)) {
				Close();
				throw new NetworkException("Error accepting connection", __FILE__, __LINE__, __func__);
			}
		}
			
		// Return results
		(IPV4SocketAddress &)address = (IPV4SocketAddress)&addr;
		return new Socket(clientSocket);
	} else {
		throw new NetworkException("Not implemented", __FILE__, __LINE__, __func__);
	}
}
