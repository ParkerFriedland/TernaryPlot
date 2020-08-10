#include "SequentialMonroe.h"
#include "MathFunctions.h"

SequentialMonroe::SequentialMonroe(unsigned seats, bool oneSeatPerWinner) : SequentialMethod(seats, oneSeatPerWinner) {}

unsigned SequentialMonroe::CalculateNextWinner(
	std::vector<ScoreBallot>& ballots, const Domain& domain, const Outcome& winners, unsigned, unsigned seats)
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
		badCode[0] = ballots[0].GetRawScore(currCandidate);
		badCode[1] = ballots[1].GetRawScore(currCandidate);
		badCode[2] = ballots[2].GetRawScore(currCandidate);
		Sort3(badCode);

		double currHareScore;
		double currTiebreaker = ballots[0].GetCalculatedScore(currCandidate)
							  + ballots[1].GetCalculatedScore(currCandidate)
							  + ballots[2].GetCalculatedScore(currCandidate);
		double weightInQuota;

		if (badCode[2] == ballots[0].GetRawScore(currCandidate))
		{
			currHareScore = ballots[0].GetCalculatedScore(currCandidate);
			weightInQuota = ballots[0].GetCurrentRoundWeight();
		}
		else if (badCode[2] == ballots[1].GetRawScore(currCandidate))
		{
			currHareScore = ballots[1].GetCalculatedScore(currCandidate);
			weightInQuota = ballots[1].GetCurrentRoundWeight();
		}
		else
		{
			currHareScore = ballots[2].GetCalculatedScore(currCandidate);
			weightInQuota = ballots[2].GetCurrentRoundWeight();
		}

		if (weightInQuota >= quota)
		{
			currHareScore *= (quota / weightInQuota);
			if (currHareScore > maxHareScore 
			|| (currHareScore == maxHareScore && currTiebreaker > tiebreakerScore))
			{
				maxHareScore = currHareScore;
				tiebreakerScore = currTiebreaker;
				winningCandidate = currCandidate;
				continue;
			}
		}

		double nextWeight;
		double nextScore;

		if (badCode[1] == ballots[0].GetRawScore(currCandidate))
		{
			nextScore = ballots[0].GetCalculatedScore(currCandidate);
			nextWeight = ballots[0].GetCurrentRoundWeight();
		}
		else if (badCode[1] == ballots[1].GetRawScore(currCandidate))
		{
			nextScore = ballots[1].GetCalculatedScore(currCandidate);
			nextWeight = ballots[1].GetCurrentRoundWeight();
		}
		else
		{
			nextScore = ballots[2].GetCalculatedScore(currCandidate);
			nextWeight = ballots[2].GetCurrentRoundWeight();
		}

		if ((weightInQuota + nextWeight) >= quota)
		{
			nextScore *= (quota - weightInQuota) / nextWeight;
			currHareScore += nextScore;

			if (currHareScore > maxHareScore
			|| (currHareScore == maxHareScore && currTiebreaker > tiebreakerScore))
			{
				maxHareScore = currHareScore;
				tiebreakerScore = currTiebreaker;
				winningCandidate = currCandidate;
				continue;
			}
		}

		if (badCode[0] == ballots[0].GetRawScore(currCandidate))
		{
			weightInQuota += ballots[0].GetCurrentRoundWeight();
		}
		else if (badCode[0] == ballots[1].GetRawScore(currCandidate))
		{
			weightInQuota += ballots[1].GetCurrentRoundWeight();
		}
		else
		{
			weightInQuota += ballots[2].GetCurrentRoundWeight();
		}
		
		if (currHareScore > maxHareScore
		|| (currHareScore == maxHareScore && currTiebreaker > tiebreakerScore))
		{
			maxHareScore = currHareScore;
			tiebreakerScore = currTiebreaker;
			winningCandidate = currCandidate;
		}
	}

	badCode[0] = ballots[0].GetRawScore(winningCandidate);
	badCode[1] = ballots[1].GetRawScore(winningCandidate);
	badCode[2] = ballots[2].GetRawScore(winningCandidate);
	Sort3(badCode);

	double weightInQuota;
	unsigned lastBallot;

	if (badCode[2] == ballots[0].GetRawScore(winningCandidate))
	{
		weightInQuota = ballots[0].GetCurrentRoundWeight();
		lastBallot = 0;
	}
	else if (badCode[2] == ballots[1].GetRawScore(winningCandidate))
	{
		weightInQuota = ballots[1].GetCurrentRoundWeight();
		lastBallot = 1;
	}
	else
	{
		weightInQuota = ballots[2].GetCurrentRoundWeight();
		lastBallot = 2;
	}

	if (weightInQuota > quota)
	{
		ballots[lastBallot].SetCurrentWeight(weightInQuota - quota);
		return winningCandidate;
	}
	else
	{
		ballots[lastBallot].SetCurrentWeight(0);
	}

	if (badCode[1] == ballots[0].GetRawScore(winningCandidate))
	{
		weightInQuota += ballots[0].GetCurrentRoundWeight();
		lastBallot = 0;
	}
	else if (badCode[1] == ballots[1].GetRawScore(winningCandidate))
	{
		weightInQuota += ballots[1].GetCurrentRoundWeight();
		lastBallot = 1;
	}
	else
	{
		weightInQuota += ballots[2].GetCurrentRoundWeight();
		lastBallot = 2;
	}

	if (weightInQuota > quota)
	{
		ballots[lastBallot].SetCurrentWeight(weightInQuota - quota);
		return winningCandidate;
	}
	else
	{
		ballots[lastBallot].SetCurrentWeight(0);
	}

	if (badCode[0] == ballots[0].GetRawScore(winningCandidate))
	{
		weightInQuota += ballots[0].GetCurrentRoundWeight();
		lastBallot = 0;
	}
	else if (badCode[0] == ballots[1].GetRawScore(winningCandidate))
	{
		weightInQuota += ballots[1].GetCurrentRoundWeight();
		lastBallot = 1;
	}
	else
	{
		weightInQuota += ballots[2].GetCurrentRoundWeight();
		lastBallot = 2;
	}

	if (weightInQuota > quota)
	{
		ballots[lastBallot].SetCurrentWeight(weightInQuota - quota);
		return winningCandidate;
	}
	else
	{
		ballots[lastBallot].SetCurrentWeight(0);
	}

	return winningCandidate;
}