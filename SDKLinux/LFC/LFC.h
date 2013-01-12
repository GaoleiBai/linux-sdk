#ifndef LFC_H
#define LFC_H

// Libraries needed to compile
// rt


#include "n_object.h"
#include "exception.h"
#include "nobjectregistry.h"
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