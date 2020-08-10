#include "PAV.h"

PAV::PAV(bool oneSeatPerWinner) : OptimalMethod(oneSeatPerWinner) {}

double PAV::CalculateOutcomeQuality(const std::vector<ApprovalBallot> &ballots, const Outcome &outcome)
{
	double quality = 0;

	for (ApprovalBallot ballot : ballots)
	{
		double divisor = 0.0;

		for (unsigned candidate = 0; candidate < outcome.GetNumCandidates(); ++candidate)
			for (unsigned seats = 0; seats < ballot.GetOutcomeApprovalSum(outcome); ++seats)
				quality += 1 / ++divisor;
	}

	return quality;
}