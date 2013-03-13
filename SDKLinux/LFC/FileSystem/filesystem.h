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
#ifndef FILESYSTEM_H
#define FILESYSTEM_H


// FileSystemObjectKind
#define	FSOK_File 1
#define FSOK_Directory 2
#define	FSOK_BlockDevice 4
#define	FSOK_CharacterDevice 8
#define	FSOK_NamedPipe 16
#define	FSOK_SymbolicLink 32
#define FSOK_DomainSocket 64
#define	FSOK_UnknownFileSystemObject 128


// File rights
#define	USER_READ 0400
#define	USER_WRITE 0200
#define	USER_EXEC 0100
#define	GROUP_READ 0040
#define	GROUP_WRITE 0020
#define	GROUP_EXEC 0010
#define	OTHERS_READ 0004
#define	OTHERS_WRITE 0002
#define	OTHERS_EXEC 0001

// File open modes
#define FO_Append O_APPEND
#define FO_Create O_CREAT
#define FO_Truncate O_TRUNC
#define FO_ReadWrite O_RDWR
#define FO_WriteOnly O_WRONLY
#define FO_ReadOnly O_RDONLY




#endif