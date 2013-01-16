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
   
   
#include "nobjectregistry.h"
#include "Text/text.h"
#include "Devices/stdout.h"
#include <stdlib.h>
#include <typeinfo>

NObjectRegistry *NObjectRegistry::registry = NULL;

NObjectRegistry::NObjectRegistry()
{
	if (registry != NULL) 
		throw new Exception("Can only exist one registry at a time.", __FILE__, __LINE__, __func__);
	classes = new Dictionary<Text *, NObject *>(Text::COMPARER);
}

NObjectRegistry::~NObjectRegistry()
{
	delete classes;
}

void NObjectRegistry::Register(const NObject &o)
{
	if (registry == NULL) 
		registry = new NObjectRegistry();
		
	Text classname = typeid(o).name();
	if (!registry->classes->ExistsKey(&classname))
		registry->classes->SetKey(new Text(classname), ((NObject *)&o)->NewInstance());
}

NObject *NObjectRegistry::GetInstance(const Text &classname)
{
	if (registry == NULL)
		throw new Exception((Text)"Please call lfc_init() before using LFC library.", __FILE__, __LINE__, __func__);
	NObject *o = NULL;
	if (!registry->classes->GetKey((Text *)&classname, o))
		throw new Exception((Text)"Please call NObjectRegistry::Register(" + classname + ") to use LFC class serialization.", __FILE__, __LINE__, __func__);
	return o->NewInstance();
}

