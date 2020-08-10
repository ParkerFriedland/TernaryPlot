#include <vector>
#include <algorithm>
#include "MathFunctions.h"

/*

In the future, these methods will be seperate classes that inherit from VotingMethod,
take in OrdinalVotes instead of just taking in an array of 3 types of votes.
and return a Result instead of an int:

3 types of votes (T = approval threshold)
votes[0]: C>T>Y>M							or C=10/10, M=0/10,  Y=3/10
votes[1]: M>C>T>Y							or C=7/10,  M=10/10, Y=0/10
votes[2]: 50% Y>M>T>C and 50% Y>T>M>C		or C=0/10,  M=5/10,  Y=10/10

Or if using RGB:

votes[0]: R>T>B>G							or R=10/10, G=0/10,  B=3/10
votes[1]: G>R>T>B							or R=7/10,  G=10/10, B=0/10
votes[2]: 50% B>G>T>R and 50% B>T>G>R		or R=0/10,  G=5/10,  B=10/10

Or if using ABC:

votes[0]: A>T>C>B							or A=10/10, B=0/10,  C=3/10
votes[1]: B>A>T>C							or A=7/10,  B=10/10, C=0/10
votes[2]: 50% C>B>T>A and 50% C>T>B>A		or A=0/10,  B=5/10,  C=10/10

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

int Temp_CB_Merged_With_RP(double votes[3])
{
	double ABC[3], ACB[3], BAC[3], BCA[3], CAB[3], CBA[3], maxScores[3];
	int currWinner = 0;

	ABC[0] =  0.7 * votes[0] + 0.7 * votes[1] - 1.0 * votes[2]; // A normalized score - C normalized score
	ABC[1] = votes[0] - votes[1] - votes[2]; // A>B - B>A
	ABC[2] = votes[1] - votes[0] - votes[2]; // B>C - C>B
	Sort3(ABC); // ABC[0] should become min(A>B - B>A, B>C - C>B, A normalized score - C normalized score)

	maxScores[0] = ABC[0];
	maxScores[1] = ABC[1];
	maxScores[2] = ABC[2];

	ACB[0] =  1.0 * votes[0] - 0.3 * votes[1] - 0.5 * votes[2]; // A normalized score - B normalized score
	ACB[1] = votes[0] + votes[1] - votes[2]; // A>C - C>A
	ACB[2] = votes[0] + votes[2] - votes[1]; // C>B - B>C
	Sort3(ACB); // ACB[0] should become min(A>C - C>A, C>B - B>C, A normalized score - B normalized score)

	if (ACB[0] > maxScores[0])
	{
		maxScores[0] = ACB[0];
	}
	else if (ACB[0] == maxScores[0])
	{
		if (ACB[1] > maxScores[1])
		{
			maxScores[1] = ACB[1];
		}
		else if (ACB[1] == maxScores[1])
			if (ACB[2] > maxScores[2])
			{
				maxScores[2] = ACB[2];
			}
	}

	BAC[0] = -0.3 * votes[0] + 1.0 * votes[1] - 0.5 * votes[2]; // B normalized score - C normalized score
	BAC[1] = votes[1] + votes[2] - votes[0]; // B>A - A>B
	BAC[2] = votes[0] + votes[1] - votes[2]; // A>C - C>A
	Sort3(BAC); // BAC[0] shocurWinninguld become min(B>A - A>B, A>C - C>A, B normalized score - C normalized score)

	if (BAC[0] > maxScores[0])
	{
		maxScores[0] = BAC[0];
		currWinner = 1;
	}
	else if (BAC[0] == maxScores[0])
	{
		if (BAC[1] > maxScores[1])
		{
			maxScores[1] = BAC[1];
			currWinner = 1;
		}
		else if (BAC[1] == maxScores[1])
			if (BAC[2] > maxScores[2])
			{
				maxScores[2] = BAC[2];
				currWinner = 1;
			}
	}

	BCA[0] = -1.0 * votes[0] + 0.3 * votes[1] + 0.5 * votes[2]; // B normalized score - A normalized score
	BCA[1] = votes[2] - votes[0] - votes[1]; // C>A - A>C
	BCA[2] = votes[1] - votes[0] - votes[2]; // B>C - C>B
	Sort3(BCA); // BCA[0] should become min(B>C - C>B, C>A - A>C, B normalized score - A normalized score)

	if (BCA[0] > maxScores[0])
	{
		maxScores[0] = BCA[0];
		currWinner = 1;
	}
	else if (BCA[0] == maxScores[0])
	{
		if (BCA[1] > maxScores[1])
		{
			maxScores[1] = BCA[1];
			currWinner = 1;
		}
		else if (BCA[1] == maxScores[1])
			if (BCA[2] > maxScores[2])
			{
				maxScores[2] = BCA[2];
				currWinner = 1;
			}
	}

	CAB[0] =  0.3 * votes[0] - 1.0 * votes[1] + 0.5 * votes[2]; // C normalized score - B normalized score
	CAB[1] = votes[0] - votes[1] - votes[2]; // A>B - B>A
	CAB[2] = votes[2] - votes[0] - votes[1]; // C>A - A>C
	Sort3(CAB); // CAB[0] should become min(C>B - B>A, B>C - C>B, C normalized score - B normalized score)

	if (CAB[0] > maxScores[0])
	{
		maxScores[0] = CAB[0];
		currWinner = 2;
	}
	else if (CAB[0] == maxScores[0])
	{
		if (CAB[1] > maxScores[1])
		{
			maxScores[1] = CAB[1];
			currWinner = 2;
		}
		else if (CAB[1] == maxScores[1])
			if (CAB[2] > maxScores[2])
			{
				maxScores[2] = CAB[2];
				currWinner = 2;
			}
	}

	CBA[0] = -0.7 * votes[0] - 0.7 * votes[1] + 1.0 * votes[2]; // C normalized score - A normalized score
	CBA[1] = votes[1] + votes[2] - votes[0]; // B>A - A>B
	CBA[2] = votes[0] + votes[0] - votes[1]; // C>B - B>C
	Sort3(CBA); // CBA[0] should become min(C>B - B>A, B>C - C>B, C normalized score - A normalized score)

	if (CBA[0] > maxScores[0])
		currWinner = 2;
	else if (CBA[0] == maxScores[0])
	{
		if (CBA[1] > maxScores[1])
			currWinner = 2;
		else if (CBA[1] == maxScores[1])
			if (CBA[2] > maxScores[2])
				currWinner = 2;
	}

	return currWinner;
}

int Temp_CB_Merged_With_RP_V2(double votes[3])
{
	double ABC[4], ACB[4], BAC[4], BCA[4], CAB[4], CBA[4], maxScores[4];
	int currWinner = 0;

	ABC[0] = 0.7 * votes[0] + 0.7 * votes[1] - 1.0 * votes[2]; // A normalized score - C normalized score
	ABC[1] = votes[0] - votes[1] - votes[2]; // A>B - B>A
	ABC[2] = votes[1] - votes[0] - votes[2]; // B>C - C>B
	ABC[3] = votes[0] + votes[1] - votes[2]; // A>C - C>A
	Sort4(ABC); // ABC[0] should become min(A>B - B>A, B>C - C>B, A normalized score - C normalized score)

	maxScores[0] = ABC[0];
	maxScores[1] = ABC[1];
	maxScores[2] = ABC[2];
	maxScores[3] = ABC[3];

	ACB[0] = 1.0 * votes[0] - 0.3 * votes[1] - 0.5 * votes[2]; // A normalized score - B normalized score
	ACB[1] = votes[0] + votes[1] - votes[2]; // A>C - C>A
	ACB[2] = votes[0] + votes[2] - votes[1]; // C>B - B>C
	ACB[3] = votes[0] - votes[1] - votes[2]; // A>B - B>A
	Sort4(ACB); // ACB[0] should become min(A>C - C>A, C>B - B>C, A normalized score - B normalized score)

	if (ACB[0] > maxScores[0])
	{
		maxScores[0] = ACB[0];
	}
	else if (ACB[0] == maxScores[0])
	{
		if (ACB[1] > maxScores[1])
		{
			maxScores[1] = ACB[1];
		}
		else if (ACB[1] == maxScores[1])
		{
			if (ACB[2] > maxScores[2])
			{
				maxScores[2] = ACB[2];
			}
			else if (ACB[2] == maxScores[2])
				if (ACB[3] > maxScores[3])
					maxScores[3] = ACB[3];
		}
	}

	BAC[0] = -0.3 * votes[0] + 1.0 * votes[1] - 0.5 * votes[2]; // B normalized score - C normalized score
	BAC[1] = votes[1] + votes[2] - votes[0]; // B>A - A>B
	BAC[2] = votes[0] + votes[1] - votes[2]; // A>C - C>A
	BAC[3] = votes[1] - votes[0] - votes[2]; // B>C - C>B
	Sort4(BAC); // BAC[0] shocurWinninguld become min(B>A - A>B, A>C - C>A, B normalized score - C normalized score)

	if (BAC[0] > maxScores[0])
	{
		maxScores[0] = BAC[0];
		currWinner = 1;
	}
	else if (BAC[0] == maxScores[0])
	{
		if (BAC[1] > maxScores[1])
		{
			maxScores[1] = BAC[1];
			currWinner = 1;
		}
		else if (BAC[1] == maxScores[1])
		{
			if (BAC[2] > maxScores[2])
			{
				maxScores[2] = BAC[2];
				currWinner = 1;
			}
			else if (BAC[2] == maxScores[2])
				if (BAC[3] > maxScores[3])
				{
					maxScores[3] = BAC[3];
					currWinner = 1;
				}
		}
	}

	BCA[0] = -1.0 * votes[0] + 0.3 * votes[1] + 0.5 * votes[2]; // B normalized score - A normalized score
	BCA[1] = votes[2] - votes[0] - votes[1]; // C>A - A>C
	BCA[2] = votes[1] - votes[0] - votes[2]; // B>C - C>B
	BCA[3] = votes[1] + votes[2] - votes[0]; // B>A - A>B
	Sort4(BCA); // BCA[0] should become min(B>C - C>B, C>A - A>C, B normalized score - A normalized score)

	if (BCA[0] > maxScores[0])
	{
		maxScores[0] = BCA[0];
		currWinner = 1;
	}
	else if (BCA[0] == maxScores[0])
	{
		if (BCA[1] > maxScores[1])
		{
			maxScores[1] = BCA[1];
			currWinner = 1;
		}
		else if (BCA[1] == maxScores[1])
		{
			if (BCA[2] > maxScores[2])
			{
				maxScores[2] = BCA[2];
				currWinner = 1;
			}
			else if(BCA[2] == maxScores[2])
				if (BCA[3] > maxScores[3])
				{
					maxScores[3] > BCA[3];
					currWinner = 1;
				}
		}
	}

	CAB[0] = 0.3 * votes[0] - 1.0 * votes[1] + 0.5 * votes[2]; // C normalized score - B normalized score
	CAB[1] = votes[0] - votes[1] - votes[2]; // A>B - B>A
	CAB[2] = votes[2] - votes[0] - votes[1]; // C>A - A>C
	CAB[3] = votes[0] + votes[0] - votes[1]; // C>B - B>C
	Sort4(CAB); // CAB[0] should become min(C>B - B>A, B>C - C>B, C normalized score - B normalized score)

	if (CAB[0] > maxScores[0])
	{
		maxScores[0] = CAB[0];
		currWinner = 2;
	}
	else if (CAB[0] == maxScores[0])
	{
		if (CAB[1] > maxScores[1])
		{
			maxScores[1] = CAB[1];
			currWinner = 2;
		}
		else if (CAB[1] == maxScores[1])
		{
			if (CAB[2] > maxScores[2])
			{
				maxScores[2] = CAB[2];
				currWinner = 2;
			}
			else if (CAB[2] == maxScores[2])
				if (CAB[3] > maxScores[3])
				{
					maxScores[3] > CAB[3];
					currWinner = 3;
				}
		}
	}

	CBA[0] = -0.7 * votes[0] - 0.7 * votes[1] + 1.0 * votes[2]; // C normalized score - A normalized score
	CBA[1] = votes[1] + votes[2] - votes[0]; // B>A - A>B
	CBA[2] = votes[0] + votes[0] - votes[1]; // C>B - B>C
	CBA[3] = votes[2] - votes[0] - votes[1]; // C>A - A>C
	Sort4(CBA); // CBA[0] should become min(C>B - B>A, B>C - C>B, C normalized score - A normalized score)

	if (CBA[0] > maxScores[0])
		currWinner = 2;
	else if (CBA[0] == maxScores[0])
	{
		if (CBA[1] > maxScores[1])
			currWinner = 2;
		else if (CBA[1] == maxScores[1])
		{
			if (CBA[2] > maxScores[2])
				currWinner = 2;
			else if (CBA[2] == maxScores[2])
				if (CBA[3] > maxScores[3])
					currWinner = 2;
		}
	}

	return currWinner;
}

int Temp_CB_Merged_With_RP_V3(double votes[3])
{
	double ABC[3], ACB[3], BAC[3], BCA[3], CAB[3], CBA[3], maxScores[3];
	int currWinner = 0;

	ABC[0] = Min<double>(0.7 * votes[0] + 0.7 * votes[1] - 1.0 * votes[2], // A normalized score - C normalized score
			votes[0] + votes[1] - votes[2]); // A>C - C>A
	ABC[1] = votes[0] - votes[1] - votes[2]; // A>B - B>A
	ABC[2] = votes[1] - votes[0] - votes[2]; // B>C - C>B
	Sort3(ABC); // ABC[0] should become min(A>B - B>A, B>C - C>B, A normalized score - C normalized score)

	maxScores[0] = ABC[0];
	maxScores[1] = ABC[1];
	maxScores[2] = ABC[2];

	ACB[0] = Min<double>(1.0 * votes[0] - 0.3 * votes[1] - 0.5 * votes[2], // A normalized score - B normalized score
			votes[0] - votes[1] - votes[2]); // A>B - B>A
	ACB[1] = votes[0] + votes[1] - votes[2]; // A>C - C>A
	ACB[2] = votes[0] + votes[2] - votes[1]; // C>B - B>C
	Sort3(ACB); // ACB[0] should become min(A>C - C>A, C>B - B>C, A normalized score - B normalized score)

	if (ACB[0] > maxScores[0])
	{
		maxScores[0] = ACB[0];
	}
	else if (ACB[0] == maxScores[0])
	{
		if (ACB[1] > maxScores[1])
		{
			maxScores[1] = ACB[1];
		}
		else if (ACB[1] == maxScores[1])
			if (ACB[2] > maxScores[2])
			{
				maxScores[2] = ACB[2];
			}
	}

	BAC[0] = Min<double>(-0.3 * votes[0] + 1.0 * votes[1] - 0.5 * votes[2], // B normalized score - C normalized score
			votes[1] - votes[0] - votes[2]); // B>C - C>B
	BAC[1] = votes[1] + votes[2] - votes[0]; // B>A - A>B
	BAC[2] = votes[0] + votes[1] - votes[2]; // A>C - C>A
	Sort3(BAC); // BAC[0] shocurWinninguld become min(B>A - A>B, A>C - C>A, B normalized score - C normalized score)

	if (BAC[0] > maxScores[0])
	{
		maxScores[0] = BAC[0];
		currWinner = 1;
	}
	else if (BAC[0] == maxScores[0])
	{
		if (BAC[1] > maxScores[1])
		{
			maxScores[1] = BAC[1];
			currWinner = 1;
		}
		else if (BAC[1] == maxScores[1])
			if (BAC[2] > maxScores[2])
			{
				maxScores[2] = BAC[2];
				currWinner = 1;
			}
	}

	BCA[0] = Min<double>(-1.0 * votes[0] + 0.3 * votes[1] + 0.5 * votes[2], // B normalized score - A normalized score
			votes[1] + votes[2] - votes[0]); // B>A - A>B
	BCA[1] = votes[2] - votes[0] - votes[1]; // C>A - A>C
	BCA[2] = votes[1] - votes[0] - votes[2]; // B>C - C>B
	Sort3(BCA); // BCA[0] should become min(B>C - C>B, C>A - A>C, B normalized score - A normalized score)

	if (BCA[0] > maxScores[0])
	{
		maxScores[0] = BCA[0];
		currWinner = 1;
	}
	else if (BCA[0] == maxScores[0])
	{
		if (BCA[1] > maxScores[1])
		{
			maxScores[1] = BCA[1];
			currWinner = 1;
		}
		else if (BCA[1] == maxScores[1])
			if (BCA[2] > maxScores[2])
			{
				maxScores[2] = BCA[2];
				currWinner = 1;
			}
	}

	CAB[0] = Min<double>(0.3 * votes[0] - 1.0 * votes[1] + 0.5 * votes[2], // C normalized score - B normalized score
			votes[0] + votes[0] - votes[1]); // C>B - B>C
	CAB[1] = votes[0] - votes[1] - votes[2]; // A>B - B>A
	CAB[2] = votes[2] - votes[0] - votes[1]; // C>A - A>C
	Sort3(CAB); // CAB[0] should become min(C>B - B>A, B>C - C>B, C normalized score - B normalized score)

	if (CAB[0] > maxScores[0])
	{
		maxScores[0] = CAB[0];
		currWinner = 2;
	}
	else if (CAB[0] == maxScores[0])
	{
		if (CAB[1] > maxScores[1])
		{
			maxScores[1] = CAB[1];
			currWinner = 2;
		}
		else if (CAB[1] == maxScores[1])
			if (CAB[2] > maxScores[2])
			{
				maxScores[2] = CAB[2];
				currWinner = 2;
			}
	}

	CBA[0] = Min<double>(-0.7 * votes[0] - 0.7 * votes[1] + 1.0 * votes[2], // C normalized score - A normalized score
			votes[2] - votes[0] - votes[1]); // C>A - A>C
	CBA[1] = votes[1] + votes[2] - votes[0]; // B>A - A>B
	CBA[2] = votes[0] + votes[0] - votes[1]; // C>B - B>C
	Sort3(CBA); // CBA[0] should become min(C>B - B>A, B>C - C>B, C normalized score - A normalized score)

	if (CBA[0] > maxScores[0])
		currWinner = 2;
	else if (CBA[0] == maxScores[0])
	{
		if (CBA[1] > maxScores[1])
			currWinner = 2;
		else if (CBA[1] == maxScores[1])
			if (CBA[2] > maxScores[2])
				currWinner = 2;
	}

	return currWinner;
}

int Temp_CB_Merged_With_SB(double votes[3])
{
	double A_vs_B_no_C = votes[0] - votes[1] - votes[2];
	double A_vs_B_with_C = 1.0 * votes[0] - 0.3 * votes[1] - 0.5 * votes[2];

	double A_vs_C_no_B = votes[0] + votes[1] - votes[2];
	double A_vs_C_with_B = 0.7 * votes[0] + 0.7 * votes[1] - 1.0 * votes[2];

	double B_vs_C_no_A = votes[1] - votes[0] - votes[2];
	double B_vs_C_with_A = -0.3 * votes[0] + 1.0 * votes[1] - 0.5 * votes[2];

	double A_to_B = Max<double>( A_vs_B_no_C, Min<double>(Min<double>( A_vs_C_no_B, -B_vs_C_no_A),  A_vs_B_with_C));
	double B_to_A = Max<double>(-A_vs_B_no_C, Min<double>(Min<double>(-A_vs_C_no_B,  B_vs_C_no_A), -A_vs_B_with_C));

	double A_to_C = Max<double>( A_vs_C_no_B, Min<double>(Min<double>( A_vs_B_no_C,  B_vs_C_no_A),  A_vs_C_with_B));
	double C_to_A = Max<double>(-A_vs_C_no_B, Min<double>(Min<double>(-A_vs_B_no_C, -B_vs_C_no_A), -A_vs_C_with_B));

	double B_to_C = Max<double>( B_vs_C_no_A, Min<double>(Min<double>(-A_vs_B_no_C,  A_vs_C_no_B),  B_vs_C_with_A));
	double C_to_B = Max<double>(-B_vs_C_no_A, Min<double>(Min<double>( A_vs_B_no_C, -A_vs_C_no_B), -B_vs_C_with_A));

	if (A_to_B > B_to_A && A_to_C > C_to_A)
		return 0;

	if (B_to_A > A_to_B && B_to_C > C_to_B)
		return 1;

	if (C_to_A > A_to_C && C_to_B > B_to_C)
		return 2;

	return -1;
}

int Temp_CB_Merged_With_SB_V2(double votes[3])
{
	double A_vs_B_no_C = votes[0] - votes[1] - votes[2];
	double A_vs_B_with_C = 1.0 * votes[0] - 0.3 * votes[1] - 0.5 * votes[2];

	double A_vs_C_no_B = votes[0] + votes[1] - votes[2];
	double A_vs_C_with_B = 0.7 * votes[0] + 0.7 * votes[1] - 1.0 * votes[2];

	double B_vs_C_no_A = votes[1] - votes[0] - votes[2];
	double B_vs_C_with_A = -0.3 * votes[0] + 1.0 * votes[1] - 0.5 * votes[2];

	double A_to_B = Max<double>(A_vs_B_no_C, Min<double>(Min<double>(A_vs_C_no_B, -B_vs_C_no_A), A_vs_B_with_C));
	double B_to_A = Max<double>(-A_vs_B_no_C, Min<double>(Min<double>(-A_vs_C_no_B, B_vs_C_no_A), -A_vs_B_with_C));

	double A_to_C = Max<double>(A_vs_C_no_B, Min<double>(Min<double>(A_vs_B_no_C, B_vs_C_no_A), A_vs_C_with_B));
	double C_to_A = Max<double>(-A_vs_C_no_B, Min<double>(Min<double>(-A_vs_B_no_C, -B_vs_C_no_A), -A_vs_C_with_B));

	double B_to_C = Max<double>(B_vs_C_no_A, Min<double>(Min<double>(-A_vs_B_no_C, A_vs_C_no_B), B_vs_C_with_A));
	double C_to_B = Max<double>(-B_vs_C_no_A, Min<double>(Min<double>(A_vs_B_no_C, -A_vs_C_no_B), -B_vs_C_with_A));

	A_vs_B_no_C = A_to_B - B_to_A;
	A_vs_C_no_B = A_to_C - C_to_A;
	B_vs_C_no_A = B_to_C - C_to_B;

	A_to_B = Max<double>(A_vs_B_no_C, Min<double>(Min<double>(A_vs_C_no_B, -B_vs_C_no_A), A_vs_B_with_C));
	B_to_A = Max<double>(-A_vs_B_no_C, Min<double>(Min<double>(-A_vs_C_no_B, B_vs_C_no_A), -A_vs_B_with_C));

	A_to_C = Max<double>(A_vs_C_no_B, Min<double>(Min<double>(A_vs_B_no_C, B_vs_C_no_A), A_vs_C_with_B));
	C_to_A = Max<double>(-A_vs_C_no_B, Min<double>(Min<double>(-A_vs_B_no_C, -B_vs_C_no_A), -A_vs_C_with_B));

	B_to_C = Max<double>(B_vs_C_no_A, Min<double>(Min<double>(-A_vs_B_no_C, A_vs_C_no_B), B_vs_C_with_A));
	C_to_B = Max<double>(-B_vs_C_no_A, Min<double>(Min<double>(A_vs_B_no_C, -A_vs_C_no_B), -B_vs_C_with_A));

	if (A_to_B > B_to_A && A_to_C > C_to_A)
		return 0;

	if (B_to_A > A_to_B && B_to_C > C_to_B)
		return 1;

	if (C_to_A > A_to_C && C_to_B > B_to_C)
		return 2;

	return -1;
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