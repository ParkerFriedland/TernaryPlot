#include "ScoreBallot.h"
#include "Outcome.h"

#pragma once

template<typename BallotType = ScoreBallot>
class VotingMethod
{
public:
	virtual Outcome &CalculateResults(std::vector<BallotType> &ballots) = 0;
};