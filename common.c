#include "common.h"

HANDLE open_rom(char* romfile)
{
	HANDLE rom = CreateFileA(romfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(rom, 0, 0, FILE_BEGIN);
	return rom;
}
