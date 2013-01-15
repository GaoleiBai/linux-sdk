/* Copyright (C) 2012, 2013
   Daniel Mosquera Villanueva
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
   
#ifndef LFC_H
#define LFC_H

// Libraries needed to compile
// rt

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
#include "Administration/administration.h"
#include "Administration/administrationexception.h"
#include "Administration/groupinfo.h"
#include "Administration/userinfo.h"

void lfc_init();

#endif