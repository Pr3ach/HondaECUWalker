#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "HEW.h"
#include "common.h"
#include "fuel.h"

int main(int argc, char** argv)
{
	struct candidates cdt;
	char target[16] = { 0 };
	char rompath[32] = { 0 };

	if (argc < 3)
	{
		usage(*argv);
		exit(-1);
	}

	strncpy_s(target, 16, argv[2], 15);
	for (int i = 0; target[i]; target[i] = tolower(target[i]), i++);

	strncpy_s(rompath, 32, argv[1], 31);

	if (!strcmp(target, "fuel"))
	{
		cdt = target_fuel(rompath);
	}
	else
	{
		printf("[!] Unknown target '%s'\n", target);
		usage(argv[0]);
		exit(-1);
	}

	printf("[+] Success: %s\n", cdt.success ? "true" : "false");
	printf("[+] Candidates count for '%s': %d\n\n", cdt.desc, cdt.count);
	for (int i = 0; i < cdt.count; i++)
		printf("[+] Offset 0x%x\n", cdt.offset[i]);

	return 0;
}

void usage(char* self)
{
	printf("HondaECUWalker v%s\n\n", VERSION);
	printf("[!] Usage: %s <rom_file> <target>\n", self);
	printf("[+] <target>: \n\t\tfuel\tOpen loop fuel tables\n");
}
