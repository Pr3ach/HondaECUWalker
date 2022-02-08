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
	printf("[+] Success: %s\n", cdt.success ? "true" : "false");
	printf("[+] Candidates count: %d\n\n", cdt.count);
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
