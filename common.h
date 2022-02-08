#ifndef COMMON_H
#define COMMON_H

#include <Windows.h>

#define MAX_CANDIDATE 256

#define VERSION "1.0.0"

struct candidates 
{
	char desc[512];
	int offset[MAX_CANDIDATE];
	int count;
	int success;
};


HANDLE open_rom(char* romfile);

#endif
