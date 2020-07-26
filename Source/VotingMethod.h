#include "CardinalBallot.h"
#include "Outcome.h"

#pragma once

template<typename BallotType = CardinalBallot>
class VotingMethod
{
public:
	virtual Outcome &CalculateResults(std::vector<BallotType> &ballots) = 0;
};