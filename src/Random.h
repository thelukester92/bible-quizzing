#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random
{
	std::mt19937 engine;
	
	public:
		Random();
		
		int nextInt(int min, int max);
		int nextInt(int max);
		double normal(double maximum = 0.999999);
};

#endif
