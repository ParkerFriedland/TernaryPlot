#include "OptimalMethod.h"
#include "ApprovalBallot.h"

class MonroeApproval : public OptimalMethod<ApprovalBallot, unsigned>
{
public:
	MonroeApproval(bool oneSeatPerWinner = false);
	unsigned CalculateOutcomeQuality(const std::vector<ApprovalBallot>& ballots, const Outcome &outcome);
};