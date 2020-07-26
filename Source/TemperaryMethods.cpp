#include <vector>
#include <algorithm>
#include "MathFunctions.h"

/*

In the future, these methods will be seperate classes that inherit from VotingMethod,
take in OrdinalVotes instead of just taking in an array of 3 types of votes.
and return a Result instead of an int:

3 types of votes (T = approval threshold)
votes[0]: C>T>Y>M
votes[1]: M>C>T>Y
votes[2]: 50% Y>M>T>C and 50% Y>T>M>C

Though once the general cases of each method are coded into their own classes, 
these can be used to compare with the general cases to test whether 
they produce the same results.

*/

int TempIRV(double votes[3])
{
	if (votes[2] <= votes[0] && votes[2] <= votes[1])
	{
		votes[1] += votes[2];
		if (votes[0] >= votes[1])
			return 0;
		return 1;
	}
	else if (votes[1] <= votes[0])
	{
		votes[0] += votes[1];
		if (votes[0] >= votes[2])
			return 0;
		return 2;
	}
	else
	{
		votes[2] += votes[0];
		if (votes[1] >= votes[2])
			return 1;
		return 2;
	}
}

int TempBorda(double votes[3])
{
	if (2 * votes[0] + votes[2] >= 2 * votes[1] + votes[0] && 2 * votes[0] + votes[2] >= 2 * votes[2] + votes[1])
		return 0;
	else if (2 * votes[1] + votes[0] >= 2 * votes[2] + votes[1])
		return 1;
	else
		return 2;
}

int TempFPTP(double votes[3])
{
	if (votes[0] >= votes[1] && votes[0] >= votes[2])
		return 0;
	else if (votes[1] >= votes[2])
		return 1;
	else
		return 2;
}

int TempCoombs(double votes[3])
{
	if (votes[0] >= votes[1] + votes[2])
	{
		return 0;
	}
	if (votes[1] >= votes[0] + votes[2])
	{
		return 1;
	}
	if (votes[2] >= votes[0] + votes[1])
	{
		return 2;
	}

	if (votes[0] >= votes[1] && votes[0] >= votes[2])
	{
		votes[0] += votes[1];
		if (votes[0] >= votes[1])
			return 0;
		return 1;
	}
	else if (votes[1] >= votes[2])
	{
		votes[1] += votes[2];
		if (votes[0] >= votes[2])
			return 0;
		return 2;
	}
	else
	{
		votes[1] += votes[2];
		if (votes[1] >= votes[2])
			return 1;
		return 2;
	}
}

int TempMinimax(double votes[3])
{
	return TempFPTP(votes); // The two methods are equivalent when you only have A>B>C, B>C>A, and C>A>B votes
}

int TempBucklin(double votes[3])
{
	if (votes[0] >= votes[1] + votes[2])
	{
		return 0;
	}
	if (votes[1] >= votes[0] + votes[2])
	{
		return 1;
	}
	if (votes[2] >= votes[0] + votes[1])
	{
		return 2;
	}

	if (votes[0] + votes[1] >= votes[1] + votes[2] && votes[0] + votes[1] >= votes[2] + votes[0])
	{
		return 0;
	}
	else if (votes[1] + votes[2] >= votes[2] + votes[0])
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

int TempApproval(double votes[3])
{
	if (votes[0] + votes[1] >= votes[1] + 0.5 * votes[2] && votes[0] + votes[1] >= votes[2])
		return 0;
	else if (votes[1] + 0.5 * votes[2] >= votes[2])
		return 1;
	else
		return 2;
}

int TempScore(double votes[3])
{
	if (10 * votes[0] + 7 * votes[1] >= 10 * votes[1] + 5 * votes[2] && 10 * votes[0] + 7 * votes[1] >= 10 * votes[2] + 3 * votes[0])
		return 0;
	else if (10 * votes[1] + 5 * votes[2] >= 10 * votes[2] + 3 * votes[0])
		return 1;
	else
		return 2;
}

int TempApprovalRunoff(double votes[3])
{
	if (votes[2] <= votes[0] + votes[1] && votes[2] <= votes[1] + 0.5 * votes[2])
	{
		votes[1] += votes[2];
		if (votes[0] >= votes[1])
			return 0;
		return 1;
	}
	else if (10 * votes[1] + 5 * votes[2] <= 10 * votes[0] + 7 * votes[1])
	{
		votes[0] += votes[1];
		if (votes[0] >= votes[2])
			return 0;
		return 2;
	}
	else
	{
		votes[2] += votes[0];
		if (votes[1] >= votes[2])
			return 1;
		return 2;
	}
}

int TempSTAR(double votes[3])
{
	if (10 * votes[2] + 3 * votes[0] <= 10 * votes[0] + 7 * votes[1] && 10 * votes[2] + 3 * votes[0] <= 10 * votes[1] + 5 * votes[2])
	{
		votes[1] += votes[2];
		if (votes[0] >= votes[1])
			return 0;
		return 1;
	}
	else if (10 * votes[1] + 5 * votes[2] <= 10 * votes[0] + 7 * votes[1])
	{
		votes[0] += votes[1];
		if (votes[0] >= votes[2])
			return 0;
		return 2;
	}
	else
	{
		votes[2] += votes[0];
		if (votes[1] >= votes[2])
			return 1;
		return 2;
	}
}

int TempDistributed(double votes[3])
{
	if ((10.0 / 15.0) * votes[2] + (3.0 / 13.0) * votes[0] <= (10.0 / 13.0) * votes[0] + (7.0 / 17.0) * votes[1] && (10.0 / 15.0) * votes[2] + (3.0 / 13.0) * votes[0] <= (10.0 / 17.0) * votes[1] + (5.0 / 15.0) * votes[2])
	{
		if (votes[0] + (7.0 / 17.0) * votes[1] >= (10.0 / 17.0) * votes[1] + votes[2])
			return 0;
		return 1;
	}
	else if ((10.0 / 17.0) * votes[1] + (5.0 / 15.0) * votes[2] <= (10.0 / 13.0) * votes[0] + (7.0 / 17.0) * votes[1])
	{
		if ((10.0 / 13.0) * votes[0] + votes[1] >= (3.0 / 13.0) * votes[0] + votes[2])
			return 0;
		return 2;
	}
	else
	{
		if (votes[1] + (5.0 / 15.0) * votes[2] >= (10.0 / 15.0) * votes[2] + votes[0])
			return 1;
		return 2;
	}
}



int* TempPAV(int seats[3], double votes[3])
{
	double CC = 1.5 * votes[0] + 1.5 * votes[1];
	double CM = 1.0 * votes[0] + 1.5 * votes[1] + 0.5 * votes[2];
	double CY = 1.0 * votes[0] + 1.0 * votes[1] + 1.0 * votes[2];
	double MM = 1.5 * votes[1] + 0.75 * votes[2];
	double MY = 1.0 * votes[1] + 1.25 * votes[2];
	double YY = 1.5 * votes[2];
	std::vector<double> Qualities = { CC, CM, CY, MM, MY, YY };
	double max = Max(Qualities);
	if (max == CC)
	{
		seats[0] += 2;
	}
	else if (max == CM)
	{
		seats[0]++;
		seats[1]++;
	}
	else if (max == CY)
	{
		seats[0]++;
		seats[2]++;
	}
	else if (max == MM)
	{
		seats[1] += 2;
	}
	else if (max == MY)
	{
		seats[1]++;
		seats[2]++;
	}
	else
	{
		seats[2] += 2;
	}
	return seats;
}

int* TempSainteLaguePAV(int seats[3], double votes[3])
{
	double CC = (4.0 / 3.0) * votes[0] 
						+ (4.0 / 3.0) * votes[1];

	double CM = 1.0 * votes[0] 
						+ (4.0 / 3.0) * votes[1] 
						+ 0.5 * votes[2];

	double CY = 1.0 * votes[0] 
						+ 1.0 * votes[1] 
						+ 1.0 * votes[2];

	double MM = (4.0 / 3.0) * votes[1] 
						+ (4.0 / 6.0) * votes[2];

	double MY = 1.0 * votes[1] 
						+ (7.0 / 6.0) * votes[2];

	double YY = (4.0 / 3.0) * votes[2];

	std::vector<double> Qualities = { CC, CM, CY, MM, MY, YY };
	double max = Max(Qualities);
	if (max == CC)
	{
		seats[0] += 2;
	}
	else if (max == CM)
	{
		seats[0]++;
		seats[1]++;
	}
	else if (max == CY)
	{
		seats[0]++;
		seats[2]++;
	}
	else if (max == MM)
	{
		seats[1] += 2;
	}
	else if (max == MY)
	{
		seats[1]++;
		seats[2]++;
	}
	else
	{
		seats[2] += 2;
	}
	return seats;
}

int* TempEbert(int seats[3], double votes[3])
{
	double CC = 4.0 / (votes[0] + votes[1]);

	double CM = votes[0] / Square(votes[0] + votes[1]) 
						+ votes[1] * Square(1.0 / (votes[0] + votes[1]) + 1.0 / (votes[1] + 0.5 * votes[2]))
						+ 0.5 * votes[2] / Square(votes[1] + 0.5 * votes[2]);

	double CY = (votes[0] + votes[1]) / Square(votes[0] + votes[1]) 
						+ 1.0 / votes[2];

	double MM = 4.0 / (votes[0] + 0.5 * votes[1]);

	double MY = votes[1] / Square(votes[1] + 0.5 * votes[2])
						+ 0.5 * votes[2] * Square(1.0 / votes[2] + 1.0 / (votes[1] + 0.5 * votes[2]))
						+ 0.5 / votes[2];

	double YY = 4.0 / votes[2];

	std::vector<double> costs = { CC, CM, CY, MM, MY, YY };
	double min = Min(costs);

	std::vector<int> resultIDs = { 1, 2, 3, 4, 5, 6 };
	std::random_shuffle(resultIDs.begin(), resultIDs.end());

	int winningResultID = 0;
	if (min == CC)
		winningResultID = resultIDs[0];
	if (min == CM && winningResultID < resultIDs[1])
		winningResultID = resultIDs[1];
	if (min == CY && winningResultID < resultIDs[2])
		winningResultID = resultIDs[2];
	if (min == MM && winningResultID < resultIDs[3])
		winningResultID = resultIDs[3];
	if (min == MY && winningResultID < resultIDs[4])
		winningResultID = resultIDs[4];
	if (min == YY && winningResultID < resultIDs[5])
		winningResultID = resultIDs[5];

	if (winningResultID == resultIDs[0])
	{
		seats[0] += 2;
	}
	else if (winningResultID == resultIDs[1])
	{
		seats[0]++;
		seats[1]++;
	}
	else if (winningResultID == resultIDs[2])
	{
		seats[0]++;
		seats[2]++;
	}
	else if (winningResultID == resultIDs[3])
	{
		seats[1] += 2;
	}
	else if (winningResultID == resultIDs[4])
	{
		seats[1]++;
		seats[2]++;
	}
	else if (winningResultID == resultIDs[5])
	{
		seats[2] += 2;
	}

	return seats;
}

int* TempMonroeApproval(int seats[3], double votes[3])
{
	double CC = votes[0] + votes[1];

	double CM = Min<double>(votes[0], 0.5) 
						+ Min<double>(0.5 * votes[2], 0.5) 
						+ votes[1];

	double CY = Min<double>(votes[0] + votes[1], 0.5) 
						+ Min<double>(votes[2], 0.5);

	double MM = votes[1] + 0.5 * votes[2];

	double MY = Min<double>(votes[1], 0.5) 
						+ Min<double>(0.5 * votes[2], 0.5) + 0.5 * votes[2];

	double YY = votes[2];

	std::vector<double> qualities = { CC, CM, CY, MM, MY, YY };
	double max = Max(qualities);

	std::vector<int> resultIDs = { 1, 2, 3, 4, 5, 6 };
	std::random_shuffle(resultIDs.begin(), resultIDs.end());

	int winningResultID = 0;
	if (max == CC)
		winningResultID = resultIDs[0];
	if (max == CM && winningResultID < resultIDs[1])
		winningResultID = resultIDs[1];
	if (max == CY  && winningResultID < resultIDs[2])
		winningResultID = resultIDs[2];
	if (max == MM && winningResultID < resultIDs[3])
		winningResultID = resultIDs[3];
	if (max == MY && winningResultID < resultIDs[4])
		winningResultID = resultIDs[4];
	if(max == YY && winningResultID < resultIDs[5])
		winningResultID = resultIDs[5];

	if (winningResultID == resultIDs[0])
	{
		seats[0] += 2;
	}
	else if (winningResultID == resultIDs[1])
	{
		seats[0]++;
		seats[1]++;
	}
	else if (winningResultID == resultIDs[2])
	{
		seats[0]++;
		seats[2]++;
	}
	else if (winningResultID == resultIDs[3])
	{
		seats[1] += 2;
	}
	else if (winningResultID == resultIDs[4])
	{
		seats[1]++;
		seats[2]++;
	}
	else if (winningResultID == resultIDs[5])
	{
		seats[2] += 2;
	}

	return seats;
}

int* TempSPAV(int seats[3], int numSeats, double votes[3], double k)
{
	for (int i = 0; i < numSeats; ++i)
	{
		double quotientC = votes[0] / (k + seats[0]) + votes[1] / (k + seats[0] + seats[1]);
		double quotientM = votes[1] / (k + seats[0] + seats[1]) + 0.5 * votes[2] / (k + seats[1] + seats[2]);
		double quotientY = 0.5 * votes[2] / (k + seats[2]) + 0.5 * votes[2] / (k + seats[1] + seats[2]);
		if (quotientC >= quotientM && quotientC >= quotientY)
			++seats[0];
		else if (quotientM >= quotientY)
			++seats[1];
		else
			++seats[2];
	}
	return seats;
}

int* TempAllocatedApproval(int seats[3], int numSeats, double votes[3], double k)
{
	double YMvotes = 0.5 * votes[2];
	double Yvotes = 0.5 * votes[2];
	double quota = 1 / (k + numSeats);

	for (int i = 0; i < numSeats; ++i)
	{
		double totalC = votes[0] + votes[1];
		double totalM = votes[1] + YMvotes;
		double totalY = YMvotes + Yvotes;

		if (totalC >= totalM && totalC >= totalY)
		{
			++seats[0];
			votes[0] -= quota;
			if (votes[0] < 0)
				votes[0] = 0;
		}
		else if (totalM >= totalY)
		{
			++seats[1];
			votes[1] -= quota * (votes[1] / (votes[1] + YMvotes));
			YMvotes -= quota * (YMvotes / (votes[1] + YMvotes));
			if (votes[1] < 0)
				votes[1] = 0;
			if (YMvotes < 0)
				YMvotes = 0;
		}
		else
		{
			++seats[2];
			Yvotes -= quota * (Yvotes / (Yvotes + YMvotes));
			YMvotes -= quota * (YMvotes / (Yvotes + YMvotes));
			if (YMvotes < 0)
				YMvotes = 0;
			if (Yvotes < 0)
				Yvotes = 0;
		}
	}
	return seats;
}

int* TempSTV(int seats[3], int numSeats, double votes[3])
{
	double quota = 1.0 / (1.0 + numSeats);

	int totalSeats = 0;

	while (totalSeats < numSeats)
	{
		if (votes[0] >= quota && votes[0] != 69.0)
		{
			seats[0]++;
			votes[0] -= quota;
			totalSeats++;
		}
		else if (votes[1] >= quota && votes[1] != 69.0)
		{
			seats[1]++;
			votes[1] -= quota;
			totalSeats++;
		}
		else if (votes[2] >= quota && votes[2] != 69.0)
		{
			seats[2]++;
			votes[2] -= quota;
			totalSeats++;
		}
		else if (votes[2] <= votes[0] && votes[2] <= votes[1])
		{
			votes[1] += votes[2];
			votes[2] = 69.0;
		}
		else if (votes[1] <= votes[0])
		{
			votes[0] += votes[1];
			votes[1] = 69.0;
		}
		else
		{
			votes[2] += votes[0];
			votes[0] = 69.0;
		}
	}
	return seats;
}