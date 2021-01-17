#include "util.h"

float rand0to1()
{
	return rand() / (float)RAND_MAX;
}

int rand1to8()
{
	return rand() % 8 + 1;
}

int rand1to3()
{
	return rand() % 3 + 1;
}
