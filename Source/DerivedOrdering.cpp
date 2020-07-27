#include "DerivedOrdering.h"

DerivedOrdering::DerivedOrdering(OptimalMethod<ScoreBallot> &engine) : OrderingMethod(), _engine(engine) {}

unsigned DerivedOrdering::CalculateNextWinner(
	std::vector<ScoreBallot> &ballots, const Domain &domain, const Outcome &winners, 
	bool oneSeatPerWinner)
{
	return 0;
}