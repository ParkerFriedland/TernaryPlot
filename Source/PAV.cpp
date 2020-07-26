#include "PAV.h"

PAV::PAV(double oneSeatPerWinner) : OptimalMethod(oneSeatPerWinner) {}

double PAV::CalculateOutcomeQuality(const std::vector<ApprovalBallot> &ballots, const Outcome &outcome)
{
	double quality = 0;

	for (ApprovalBallot ballot : ballots)
		for (double numApprovals = ballot.GetNumApprovals(); numApprovals > 0; --numApprovals)
			quality += 1 / numApprovals;

	return quality;
}