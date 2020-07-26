#include "Harmonic.h"

Harmonic::Harmonic(unsigned seats, bool oneSeatPerWinner) : OptimalMethod(seats, oneSeatPerWinner) {}

double Harmonic::CalculateOutcomeQuality(const std::vector<CardinalBallot> &ballots, const Outcome &outcome)
{
	double quality = 0;

	for (CardinalBallot ballot : ballots)
	{
		// There's probably a more efficiant way of calculating this.
		double gap, threashold = 1.0;
		while((gap = ballot.NextHighestScore(threashold)))
			for (double numApprovals = ballot.GetTotalRawScore(); numApprovals > threashold; --numApprovals)
				quality += gap / numApprovals;
	}

	return quality;
}