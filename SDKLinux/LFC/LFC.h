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
#ifndef LFC_H
#define LFC_H

// Libraries needed to compile
// rt,libsqlite3,libx11,libcairo

// Linker options for backtrace at exceptions
// -rdynamic

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "n_object.h"
#include "exception.h"
#include "nobjectregistry.h"
#include "nchar.h"
#include "nshort.h"
#include "nint.h"
#include "nbool.h"
#include "nlong.h"
#include "nlonglong.h"
#include "nuchar.h"
#include "nushort.h"
#include "nuint.h"
#include "nulong.h"
#include "nulonglong.h"
#include "nfloat.h"
#include "ndouble.h"
#include "nlongdouble.h"
#include "nwchar.h"
#include "random.h"
#include "Delegations/ndelegation.h"
#include "Delegations/ndelegationmanager.h"
#include "Text/text.h"
#include "Text/text_buffer.h"
#include "Text/text_exception.h"
#include "Encoding/locale_encoding.h"
#include "Collections/collection.h"
#include "Collections/collection_exception.h"
#include "Collections/dictionary.h"
#include "Collections/nobjectcollection.h"
#include "Collections/nobjectdictionary.h"
#include "FileSystem/directory.h"
#include "FileSystem/filesystemexception.h"
#include "FileSystem/filesystemobjectinfo.h"
#include "FileSystem/file.h"
#include "FileSystem/ifile.h"
#include "FileSystem/serializator.h"
#include "FileSystem/buffer.h"
#include "Time/datetime.h"
#include "Time/timeexception.h"
#include "Devices/stdout.h"
#include "Devices/stdin.h"
#include "Devices/stderr.h"
#include "Devices/serialport.h"
#include "Devices/deviceexception.h"
#include "System/system.h"
#include "System/systemexception.h"
#include "System/groupinfo.h"
#include "System/userinfo.h"
#include "Math/math.h"
#include "Math/mathexception.h"
#include "Threading/thread.h"
#include "Threading/mutex.h"
#include "Threading/waitcondition.h"
#include "Threading/threadingexception.h"
#include "Threading/mutexlock.h"
#include "Network/ipv4socketaddress.h"
#include "Network/isocketaddress.h"
#include "Network/networkexception.h"
#include "Network/socket.h"
#include "Network/ipv4genericserver.h"
#include "Network/ipv4genericservercontroller.h"
#include "Data/dataexception.h"
#include "Data/sqlite3db.h"
#include "Data/sqlite3statement.h"
#include "Data/sqlite3recordset.h"
#include "XWidgets/xwindow.h"
#include "XWidgets/xdisplay.h"
#include "XWidgets/xexception.h"
#include "XWidgets/Graphics/xwindowgraphics.h"
#include "XWidgets/Graphics/pixmapgraphics.h"
#include "XWidgets/Graphics/nsize.h"
#include "XWidgets/Graphics/npoint.h"
#include "XWidgets/Graphics/nrectangle.h"
#include "XWidgets/Events/buttonevent.h"
#include "XWidgets/Events/enterleaveevent.h"
#include "XWidgets/Events/keyevent.h"
#include "XWidgets/Events/moveevent.h"
#include "XWidgets/Events/focusevent.h"
#include "XWidgets/Events/keymapevent.h"
#include "XWidgets/Events/drawevent.h"
#include "XWidgets/Events/visibilityevent.h"
#include "XWidgets/Events/showevent.h"
#include "XWidgets/Events/createevent.h"
#include "XWidgets/Events/destroyevent.h"
#include "XWidgets/Events/windowmoveevent.h"
#include "XWidgets/Events/windowresizeevent.h"
#include "XWidgets/Events/keyboardmappingevent.h"
#include "XWidgets/Events/colormapevent.h"

void lfc_init();

#endif