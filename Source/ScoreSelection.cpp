#include "ScoreSelection.h"

ScoreSelection::ScoreSelection() : SelectionComponent() {}

unsigned ScoreSelection::SelectWinner(const std::vector<ScoreBallot> &ballots, const Domain &domain, unsigned seats)
{
	// to-do: optimize this in the future to be more cash freindly

	double maxSum;
	unsigned currWinner;
	unsigned candidate = ~0;

	while(domain.NextInDomain(candidate))
	{
		double sum = 0;
		for (ScoreBallot ballot : ballots)
			sum += ballot.GetRawScore(candidate);

		if (sum > maxSum)
		{
			maxSum = sum;
			currWinner = candidate;
		}
	}

	return currWinner;
}