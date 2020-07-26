#include "Random.h"
#include <random>
#include <time.h>

Random::Random()
{
	srand(time(NULL));
}

int Random::Range(int range) const
{
	return rand() % range;
}

double Random::Double() const
{
	return (double)rand() / (double)RAND_MAX;
}