#include "ScoreBallot.h"

#pragma once

class TransformComponent
{
public:
	virtual std::vector<ScoreBallot> TransformBallots(std::vector<ScoreBallot> ballots) = 0;
};