#include "OrderingMethod.h"
#include "OptimalMethod.h"

#pragma once

class DerivedOrdering : public OrderingMethod
{
public:
	DerivedOrdering(OptimalMethod<CardinalBallot> &engine);
	unsigned CalculateNextWinner(std::vector<CardinalBallot> &ballots, const Outcome &winners, bool oneSeatPerWinner) override;

private:
	OptimalMethod<CardinalBallot> &_engine;
};