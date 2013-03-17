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
#include "ndelegationmanager.h"
#include "../ndelegation.h"

NDelegationManager::NDelegationManager()
{
	delegations = new Collection<NDelegation *>();
}

NDelegationManager::~NDelegationManager()
{
	delegations->DeleteAndClear();
	delete delegations;
}

void NDelegationManager::operator +=(const NDelegation &d)
{
	for (int i=0; i<delegations->Count(); i++)
		if (*(*delegations)[i] == d) return;
	delegations->Add(new NDelegation(d));
}

void NDelegationManager::operator -=(const NDelegation &d)
{
	int ix = -1;
	for (int i=0; i<delegations->Count(); i++) {
		if (*(*delegations)[i] != d) continue;
		ix = i;
		break;
	}
	if (ix == -1) return;
	delegations->DeleteAndRemoveAt(ix);
}

void NDelegationManager::Execute(void *params)
{
	for (int i=0; i<delegations->Count(); i++) {
		try {
			(*delegations)[i]->Execute(params);
		} catch (Exception *e) {
			delete e;
		}
	}
}
