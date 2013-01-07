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
#define	USER_READ 400
#define	USER_WRITE 200
#define	USER_EXEC 100
#define	GROUP_READ 40
#define	GROUP_WRITE 20
#define	GROUP_EXEC 10
#define	OTHERS_READ 4
#define	OTHERS_WRITE 2
#define	OTHERS_EXEC 1

// File open modes
#define FO_Append O_APPEND
#define FO_Create O_CREAT
#define FO_Truncate O_TRUNC
#define FO_ReadWrite O_RDWR
#define FO_WriteOnly O_WRONLY
#define FO_ReadOnly O_RDONLY




#endif