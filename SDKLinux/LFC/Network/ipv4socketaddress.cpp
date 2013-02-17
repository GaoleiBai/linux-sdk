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
   
   
#include "ipv4socketaddress.h"
#include "../Text/text.h"
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

IPV4SocketAddress::IPV4SocketAddress()
{
	hostname = NULL;
	port = 0;
}

IPV4SocketAddress::IPV4SocketAddress(const IPV4SocketAddress &addr)
{
	hostname = new Text(addr.hostname);
	port = addr.port;
}

IPV4SocketAddress::IPV4SocketAddress(struct sockaddr_in *s)
{
	s->sin_port;
	hostname = new Text(inet_ntoa(s->sin_addr));
}

IPV4SocketAddress::IPV4SocketAddress(const Text &hostname, int port)
{
	this->hostname = new Text(hostname);
	this->port = port;
}

IPV4SocketAddress::~IPV4SocketAddress()
{
	if (hostname != NULL) delete hostname;
}

Text IPV4SocketAddress::Hostname()
{
	return *hostname;
}

int IPV4SocketAddress::Port()
{
	return port;
}

struct sockaddr *IPV4SocketAddress::GetAddressData()
{
	static sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	if (hostname == NULL) {
		addr.sin_addr.s_addr = INADDR_ANY;
	} else {
		char name[1000];
		hostname->GetAnsiString(name, 1000);
		addr.sin_addr.s_addr = *((in_addr_t *)gethostbyname(name)->h_addr_list[0]);
	}
	addr.sin_port = hostname == NULL ? 0 : htons(port);
	return (struct sockaddr*)&addr;
}

socklen_t IPV4SocketAddress::GetAddressLen()
{
	return sizeof(sockaddr_in);
}

