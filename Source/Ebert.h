#include "OptimalMethod.h"
#include "ApprovalBallot.h"

class Ebert : public OptimalMethod<ApprovalBallot, double>
{
public:
	Ebert(bool oneSeatPerWinner = false);
	double CalculateOutcomeQuality(const std::vector<ApprovalBallot>& ballots, const Outcome& outcome) override;
};