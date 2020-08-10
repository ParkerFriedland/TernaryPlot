#include "ScoreSelection.h"

ScoreSelection::ScoreSelection() : SelectionComponent() {}

unsigned ScoreSelection::SelectWinner(const std::vector<ScoreBallot> &ballots, const Domain &domain)
{
	// to-do: optimize this in the future to be more cash freindly

	double maxSum = 0;
	unsigned currWinner = 0;
	unsigned candidate = ~0;

	while(domain.NextInDomain(candidate))
	{
		double sum = 0;
		for (const ScoreBallot &ballot : ballots)
			sum += ballot.GetCalculatedScore(candidate);

		if (sum > maxSum)
		{
			maxSum = sum;
			currWinner = candidate;
		}
	}

	return currWinner;
}