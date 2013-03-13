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
#ifndef ISOCKETADDRESS_H
#define ISOCKETADDRESS_H

#include "../n_object.h"
#include <sys/types.h>
#include <sys/socket.h>

class ISocketAddress : public NObject {

public:
	ISocketAddress();
	virtual ~ISocketAddress();
	
	virtual struct sockaddr *GetAddressData() = 0;
	virtual socklen_t GetAddressLen() = 0; 

};

#endif // ISOCKETADDRESS_H
