#include "OrderingMethod.h"
#include "LinearDivisor.h"
#include "ScoreSelection.h"

class ReweightedRange : public OrderingMethod
{
public:
	ReweightedRange(double delta = 1, bool oneSeatPerWinner = false);
	unsigned CalculateNextWinner(std::vector<ScoreBallot>& ballots, 
		const Domain& domain, const Outcome& winners) override;

private:
	ScoreSelection _select;
	LinearDivisor _reweight;
};