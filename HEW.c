#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <stdbool.h>
#include "HEW.h"

int main(int argc, char** argv)
{
	struct candidates cdt;

	if (argc < 3)
	{
		usage(*argv);
		exit(-1);
	}

	if (!strcmp(argv[2], "fuel"))
	{
		cdt = target_fuel(argv[1]);
	}
	else
	{
		printf("[!] Unknown target '%s'\n", argv[2]);
		usage(argv[0]);
		exit(-1);
	}


	printf("[*] Target: %s\n", cdt.desc);
	printf("[+] Candidates count: %d\n\n", cdt.count);
	for (int i = 0; i < cdt.count; i++)
		printf("[+] Offset 0x%x\n", cdt.offset[i]);

	return 0;
}

void usage(char* self)
{
	printf("[!] Usage: %s <rom_file> <target>\n", self);
	printf("[+] <target>: \n\t\tfuel\n");
}

HANDLE open_rom(char* romfile)
{
	HANDLE rom = CreateFileA(romfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(rom, 0, 0, FILE_BEGIN);
	return rom;
}

// Assume fuel table is 10*20 bytes (raw fuel) + 10 bytes (fuel coeff) = 210bytes
struct candidates target_fuel(char* romfile)
{
	HANDLE rom = open_rom(romfile);
	struct candidates cdt;
	int rom_size = GetFileSize(rom, NULL);
	unsigned char buf[210] = { 0 };
	int read_count = 0;
	unsigned long int match_count = 0;
	unsigned long int offset = 0;

	strncpy_s(cdt.desc, MAX_CANDIDATE, "Fuel Tables", 11);
	cdt.count = 0;
	cdt.success = -1;

	SetFilePointer(rom, 0, 0, FILE_BEGIN);

	while (offset <= rom_size - 210)
	{
		if (!ReadFile(rom, &buf, 210, &read_count, NULL) || read_count != 210)
		{
			printf("[!] Error reading rom (1) at offset 0x%x\n", SetFilePointer(rom, 0, 0, FILE_CURRENT));
			CloseHandle(rom);
			return cdt;
		}

		if (match_fuel_table(buf))
			cdt.offset[cdt.count++] = offset;
		else
			SetFilePointer(rom, -209, 0, FILE_CURRENT);

		offset = SetFilePointer(rom, 0, 0, FILE_CURRENT);
	}

	CloseHandle(rom);

	return cdt;
}

boolean match_fuel_table(unsigned char buf[210])
{
	int i = 0;
	unsigned short fuel_cell1 = ((float)buf[200] / 4) * buf[0];
	unsigned short fuel_cell2 = ((float)buf[200] / 4) * buf[190];

	for (i = 0; i < 200; i += 10)
	{
		if (!match_fuel_row(buf, i, i + 10))
			return false;
	}

	return true;
}

boolean match_fuel_row(unsigned char buf[210], int start, int end)
{
	int i = start;
	unsigned short fuel_cell1 = 0;
	unsigned short fuel_cell2 = 0;

	for (; i < end - 1; i++)
	{
		fuel_cell1 = ((float)buf[200 + (i - start)] / 4) * buf[i];
		fuel_cell2 = ((float)buf[200 + (i + 1 - start)] / 4) * buf[i + 1];

		if (fuel_cell1 > fuel_cell2 || (fuel_cell1 == 0 && fuel_cell2 == 0) || (fuel_cell1 > 1024 || fuel_cell2 > 1024))
			return false;
	}

	return true;
}
