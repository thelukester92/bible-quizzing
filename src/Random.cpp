#include "Random.h"
using namespace std;

Random::Random() : engine((random_device())())
{
	
}

int Random::nextInt(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(engine);
}

int Random::nextInt(int max)
{
	return nextInt(0, max);
}

double Random::normal(double maximum)
{
	normal_distribution<double> dist(0.0, 1.0);
	return min( maximum, max(-maximum, dist(engine) / maximum / 3.0) );
}
