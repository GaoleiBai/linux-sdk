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
   
   
#include "socket.h"
#include "isocketaddress.h"
#include "networkexception.h"
#include "../Text/text.h"
#include <unistd.h>
#include <netinet/in.h>
#include <typeinfo>

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
	if (fd == -1)
		throw new NetworkException("Cannot close an unexisting socket", __FILE__, __LINE__, __func__);
		
	if (close(fd) == -1)
		throw new NetworkException(Text::FromErrno(), __FILE__, __LINE__, __func__);
		
	fd = -1;
}

void Socket::Bind(const ISocketAddress &address)
{
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
	if (typeid(address) == typeid(IPV4SocketAddress)) {
		IPV4SocketAddress *a = (IPV4SocketAddress *)&address;
		if (connect(fd, a->GetAddressData(), a->GetAddressLen()) == -1)
			throw new NetworkException(Text::FromErrno(), __FILE__, __LINE__, __func__);
	} else {
		throw new NetworkException("Not implemented", __FILE__, __LINE__, __func__);
	}
}

void Socket::Listen(int backlog)
{
	if (listen(fd, backlog) == -1)
		throw new NetworkException(Text::FromErrno(), __FILE__, __LINE__, __func__);
}

void Socket::Accept(ISocketAddress &address)
{
	if (typeid(address) == typeid(IPV4SocketAddress)) {
		struct sockaddr_in addr;
		socklen_t socklen = sizeof(addr);
		int clientSocket = accept(fd, (sockaddr *)&addr, &socklen);
		if (clientSocket == -1)
			throw new NetworkException(Text::FromErrno(), __FILE__, __LINE__, __func__);
		(IPV4SocketAddress &)address = &addr;
	} else {
		throw new NetworkException("Not implemented", __FILE__, __LINE__, __func__);
	}
}