#include "DerivedOrdering.h"

DerivedOrdering::DerivedOrdering(OptimalMethod<CardinalBallot> &engine) : OrderingMethod(), _engine(engine) {}

unsigned DerivedOrdering::CalculateNextWinner(std::vector<CardinalBallot> &ballots, const Outcome &winners, bool oneSeatPerWinner)
{
	return 0;
}