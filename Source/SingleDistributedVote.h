#include "OrderingMethod.h"
#include "LinearDivisor.h"
#include "ScoreSelection.h"

class SingleDistributedVote : public OrderingMethod
{
public:
	SingleDistributedVote(double delta = 0.5, bool oneSeatPerWinner = false);
	unsigned CalculateNextWinner(std::vector<ScoreBallot>& ballots,
		const Domain& domain, const Outcome& winners) override;

private:
	ScoreSelection _select;
	double _delta;
};