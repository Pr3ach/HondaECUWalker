#ifndef HEW_H
#define HEW_H

#define MAX_CANDIDATE 256

struct candidates 
{
	char desc[MAX_CANDIDATE];
	int offset[MAX_CANDIDATE];
	int count;
	int success;
};

void usage(char* self);
HANDLE open_rom(char* romfile);
struct candidates target_fuel(char* romfile);
boolean match_fuel_table(unsigned char buf[210]);
boolean match_fuel_row(unsigned char buf[210], int start, int end);
#endif
