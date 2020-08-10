#include "STARSelection.h"

STARSelection::STARSelection() : SelectionComponent() {}

unsigned STARSelection::SelectWinner(const std::vector<ScoreBallot>& ballots, const Domain& domain)
{
	// to-do: optimize this in the future to be more cash freindly

	double maxSum1 = -1;
	double maxSum2 = -1;
	unsigned scoreWinner1 = 0;
	unsigned scoreWinner2 = 0;
	unsigned candidate = ~0;

	while (domain.NextInDomain(candidate))
	{
		double sum = 0;
		for (const ScoreBallot& ballot : ballots)
			sum += ballot.GetCalculatedScore(candidate);

		if (sum > maxSum2)
		{
			if (sum > maxSum1)
			{
				maxSum2 = maxSum1;
				scoreWinner2 = scoreWinner1;

				maxSum1 = sum;
				scoreWinner1 = candidate;
			}
			else
			{
				maxSum2 = sum;
				scoreWinner2 = candidate;
			}
		}
	}

	double runoffMargin = 0;

	for (const ScoreBallot& ballot : ballots)
	{
		double diff = ballot.GetCalculatedScore(scoreWinner1) - ballot.GetCalculatedScore(scoreWinner2);
		if (diff > 0.0)
			runoffMargin += ballot.GetCurrentRoundWeight();
		else if (diff < 0.0)
			runoffMargin -= ballot.GetCurrentRoundWeight();
	}

	if (runoffMargin >= 0.0)
		return scoreWinner1;
	else
		return scoreWinner2;
}