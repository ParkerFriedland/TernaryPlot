#include "SequentialMonroe.h"
#include "MathFunctions.h"

SequentialMonroe::SequentialMonroe(unsigned seats, bool oneSeatPerWinner) : SequentialMethod(seats, oneSeatPerWinner) {}

unsigned SequentialMonroe::CalculateNextWinner(
	std::vector<ScoreBallot>& ballots, const Domain& domain, const Outcome& winners, unsigned round, unsigned seats)
{
	// Really really bad temperary code that I'm going to get rid of.
	//
	// This temperary code that knows that there are currently only 3 ballots.
	// I will refactor the VotingMethod class so this method can know in advance

	unsigned currCandidate = ~0;
	unsigned winningCandidate = 0;
	double maxHareScore = -1;
	double tiebreakerScore = -1;
	double quota = 1.0 / static_cast<double>(seats);

	while (domain.NextInDomain(currCandidate))
	{
		sortedScores[0] = ballots[0].GetRawScore(currCandidate);
		sortedScores[1] = ballots[1].GetRawScore(currCandidate);
		sortedScores[2] = ballots[2].GetRawScore(currCandidate);
		Sort3(sortedScores);

		double currHareScore = 0;
		double currTiebreaker = ballots[0].GetCalculatedScore(currCandidate)
							  + ballots[1].GetCalculatedScore(currCandidate)
							  + ballots[2].GetCalculatedScore(currCandidate);
		double quotaLeft = quota;

		for(unsigned i = 0; i < 3; ++i)
			currExaustionCoeficient[i] = 0.0;

		unsigned i = 2;
		while(true)
		{
			double nextWeightSum = 0;
			double nextScoreSum = 0;
			double currScore = sortedScores[i];
			double exaustionFactor = -1;

			for (unsigned ballot = 0; ballot < 3; ++ballot)
			{
				if (currScore == ballots[ballot].GetRawScore(currCandidate))
				{
					nextScoreSum += ballots[ballot].GetCalculatedScore(currCandidate);
					nextWeightSum += ballots[ballot].GetCurrentRoundWeight();

					if (i == 0 || currScore != sortedScores[--i])
					{
						if (quotaLeft >= nextWeightSum)
						{
							exaustionFactor = 1.0;
							quotaLeft -= nextWeightSum;
						}
						else
						{
							exaustionFactor = quotaLeft / nextWeightSum;
							quotaLeft = 0.0;
						}

						for(; ballot != -1; --ballot)
							if(currScore == ballots[ballot].GetRawScore(currCandidate))
								currExaustionCoeficient[ballot] = exaustionFactor;

						break;
					}
				}
			}

			/*if (exaustionFactor == -1)
				bool debug = true;*/

			if (!quotaLeft || i == 0)
			{
				nextScoreSum *= exaustionFactor;
				currHareScore += nextScoreSum;

				if (currHareScore > maxHareScore
				|| (currHareScore == maxHareScore && currTiebreaker > tiebreakerScore))
				{
					maxHareScore = currHareScore;
					tiebreakerScore = currTiebreaker;
					winningCandidate = currCandidate;

					for (unsigned i = 0; i < 3; ++i)
						finalExaustionCoeficient[i] = currExaustionCoeficient[i];

					if(maxHareScore == quota)
						goto winnerFound;
				}
				break;
			}
			else
				currHareScore += nextScoreSum;
		}
	}

	winnerFound:if (round < seats)
	{
		for (unsigned ballot = 0; ballot < 3; ++ballot)
			ballots[ballot].SetCurrentWeight(
				ballots[ballot].GetCurrentRoundWeight() 
				* (1.0 - finalExaustionCoeficient[ballot]));
	}

	return winningCandidate;
}

double SequentialMonroe::FindNextHighestScores(unsigned &i, const std::vector<ScoreBallot> &ballots,
	double &scoreSum, double &weightSum, double &quotaleft, unsigned currCandidate)
{
	for (unsigned ballot = 0; ballot < 3; ++ballot)
		if (sortedScores[i] == ballots[ballot].GetRawScore(currCandidate))
		{
			scoreSum += ballots[ballot].GetCalculatedScore(currCandidate);
			weightSum += ballots[ballot].GetCurrentRoundWeight();
			
			if (i != 0 && sortedScores[i] == sortedScores[--i])
				return currExaustionCoeficient[ballot] = FindNextHighestScores(
					i, ballots, scoreSum, weightSum, quotaleft, currCandidate);
			else
			{
				if (quotaleft >= weightSum)
				{
					currExaustionCoeficient[ballot] = 1.0;
					quotaleft -= weightSum;
				}
				else
				{
					currExaustionCoeficient[ballot] = quotaleft / weightSum;
					quotaleft = 0.0;
				}
				return currExaustionCoeficient[ballot];
			}
		}
}