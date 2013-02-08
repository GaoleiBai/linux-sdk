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
   
   
#ifndef SYSTEM_H
#define SYSTEM_H

#include "../Collections/collection.h"
#include <pwd.h>
#include <grp.h>
#include <sys/mount.h>

class UserInfo;
class GroupInfo;
class Text;

// Umount flags
#define	UMF_Force MNT_FORCE
#define UMF_Detach MNT_DETACH
#define UMF_Expire MNT_EXPIRE
#define UMF_NoFollow UMOUNT_NOFOLLOW

// Mount flags
#define MF_Bind MS_BIND
#define MF_SynchronousDirectoryChanges MS_DIRSYNC
#define MF_MandatoryLockingOnFiles MS_MANDLOCK
#define MF_MoveMountPoint MS_MOVE
#define MF_DontUpdateAccessTime MS_NOATIME
#define MF_PreventDeviceAccess MS_NODEV
#define MF_DontUpdateDirectoriesAccessTime MS_NODIRATIME
#define MF_PreventProgramsExecution MS_NOEXEC
#define MF_PreventGrantingCreatorPrivileges MS_NOSUID
#define MF_ReadOnly MS_RDONLY
#define MF_UpdateAtimeAfterMtime MS_RELATIME
#define MF_Remount MS_REMOUNT
#define MF_Silent MS_SILENT
#define MF_UpdateAtimeWhenAccessed MS_STRICTATIME
#define MF_Synchronous MS_SYNCHRONOUS


class System : public NObject{

public:
	System();
	virtual ~System();

	static Collection<UserInfo *> Users();
	static Collection<GroupInfo *> Groups();
	static uid_t GetRealUserID();
	static uid_t GetEffectiveUserID();
	static gid_t GetRealGroupID();
	static gid_t GetEffectiveGroupID();
	static UserInfo GetRealUser();
	static UserInfo GetEffectiveUser();
	static GroupInfo GetRealGroup();
	static GroupInfo GetEffectiveGroup();
	static void SetRealUserID(uid_t userID);
	static void SetEffectiveUserID(uid_t userID);
	static void SetRealGroupID(gid_t groupID);
	static void SetEffectiveGroupID(gid_t groupID);
	static void SetHostName(const Text &hostname);
	static Text GetHostName();
	static void Mount(
		const Text &deviceName, const Text &targetDirectory, 
		const Text &fileSystemName, unsigned long MF_MountFlags, 
		const Text &data);
	static void Umount(const Text &path);
	static void Umount(const Text &path, int UMF_UmountFlags);
	
};

#endif // ADMINISTRATION_H
