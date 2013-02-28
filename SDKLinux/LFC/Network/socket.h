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
   
   
#ifndef SOCKET_H
#define SOCKET_H

#include "../n_object.h"
#include "../FileSystem/ifile.h"
#include "ipv4socketaddress.h"
#include <sys/types.h>
#include <sys/socket.h>

class Socket : public IFile, public NObject 
{	
	Socket(int socket);

public:

	static const int SockDomainLocal = AF_LOCAL;
	static const int SockDomainInetV4 = AF_INET;
	static const int SockDomainInetV6 = AF_INET6;
	static const int SockDomainInetIPX = AF_IPX;
	static const int SockDomainInetNetLink = AF_NETLINK;
	static const int SockDomainInetX25 = AF_X25;
	static const int SockDomainInetAX25 = AF_AX25;
	static const int SockDomainInetATMPVC = AF_ATMPVC;
	static const int SockDomainInetAppleTalk = AF_APPLETALK;
	static const int SockDomainInetPacket = AF_PACKET;
	
	static const int SockTypeStream = SOCK_STREAM;
	static const int SockTypeDatagram = SOCK_DGRAM;
	static const int SockTypeSeqPacket = SOCK_SEQPACKET;
	static const int SockTypeRaw = SOCK_RAW;
	static const int SockTypeRDM = SOCK_RDM;
	
	static const int SockProtocolNone = 0;
	
	Socket(int sock_domain, int sock_type, int sock_protocol);
	virtual ~Socket();
	
	void Bind(const ISocketAddress &address);
	void Connect(const ISocketAddress &address);
	void Connect(const ISocketAddress &address, long nanoseconds_timeout);
	void Listen(int backlog);
	Socket *Accept(ISocketAddress &address);
	void Close();
	
};

#endif // SOCKET_H
