#include "MonroeApproval.h"

MonroeApproval::MonroeApproval(bool oneSeatPerWinner) : OptimalMethod(oneSeatPerWinner) {}

unsigned MonroeApproval::CalculateOutcomeQuality(const std::vector<ApprovalBallot>& ballots, const Outcome& outcome)
{
	return 0;
}