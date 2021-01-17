#include "util.h"

float rand0to1()
{
	return rand() / (float)RAND_MAX;
}

int rand1to8()
{
	return rand() % 8 + 1;
}