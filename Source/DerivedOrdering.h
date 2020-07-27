#include "OrderingMethod.h"
#include "OptimalMethod.h"

#pragma once

class DerivedOrdering : public OrderingMethod
{
public:
	DerivedOrdering(OptimalMethod<ScoreBallot> &engine);
	unsigned CalculateNextWinner(
		std::vector<ScoreBallot> &ballots, const Domain &domain, const Outcome &winners, 
		bool oneSeatPerWinner) override;

private:
	OptimalMethod<ScoreBallot> &_engine;
};