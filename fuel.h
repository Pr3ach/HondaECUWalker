#ifndef FUEL_H
#define FUEL_H

#include <stdbool.h>

struct candidates target_fuel(char* romfile);
boolean match_fuel_table(unsigned char buf[210]);
boolean match_fuel_row(unsigned char buf[210], int start, int end);

#endif FUEL_H
