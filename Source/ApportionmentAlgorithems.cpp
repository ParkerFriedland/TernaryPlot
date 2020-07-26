#include "ApportionmentAlgorithems.h"
#include <cmath>

int* Divisor(int seats[3], int numSeats, double votes[3], double k)
{
	for (int i = 0; i < numSeats; ++i)
	{
		if (i < 3 && k == 0)
		{
			if (votes[0] >= votes[1] && votes[0] >= votes[2])
				++seats[0];
			else if (votes[1] >= votes[2])
				++seats[1];
			else
				++seats[2];
		}
		else
		{
			double quotientA = votes[0] / (k + seats[0]);
			double quotientB = votes[1] / (k + seats[1]);
			double quotientC = votes[2] / (k + seats[2]);
			if (quotientA >= quotientB && quotientA >= quotientC)
				++seats[0];
			else if (quotientB >= quotientC)
				++seats[1];
			else
				++seats[2];
		}
	}
	return seats;
}

int* Remainder(int seats[3], int numSeats, double votes[3], double k)
{
	double totalA = votes[0];
	double totalB = votes[1];
	double totalC = votes[2];
	double quota = 1 / (k + numSeats);

	for (int i = 0; i < numSeats; ++i)
	{
		if (totalA >= totalB && totalA >= totalC)
		{
			++seats[0];
			totalA -= quota;
		}
		else if (totalB >= totalC)
		{
			++seats[1];
			totalB -= quota;
		}
		else
		{
			++seats[2];
			totalC -= quota;
		}
	}
	return seats;
}

int* Hill(int seats[3], int numSeats, double votes[3])
{
	for (int i = 0; i < numSeats; ++i)
	{
		if (i < 3)
		{
			if (votes[0] >= votes[1] && votes[0] >= votes[2])
				++seats[0];
			else if (votes[1] >= votes[2])
				++seats[1];
			else
				++seats[2];
		}
		else
		{
			double quotientA = votes[0] / sqrt(seats[0] * (1 + seats[0]));
			double quotientB = votes[1] / sqrt(seats[1] * (1 + seats[1]));
			double quotientC = votes[2] / sqrt(seats[2] * (1 + seats[2]));
			if (quotientA >= quotientB && quotientA >= quotientC)
				++seats[0];
			else if (quotientB >= quotientC)
				++seats[1];
			else
				++seats[2];
		}
	}
	return seats;
}