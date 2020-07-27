#include "ScoreBallot.h"
#include "Outcome.h"

#pragma once

template<typename BallotType = ScoreBallot>
class VotingMethod
{
public:
	virtual void CalculateResults(std::vector<BallotType> &ballots, Domain &domain, Outcome &results) = 0;
};