#include "ScoreBallot.h"

#pragma once

class ReweightingComponent
{
public:
	virtual void ReweightBallots(std::vector<ScoreBallot> &ballots, unsigned seats, unsigned lastWinner);
	virtual void ReweightBallots(std::vector<ScoreBallot>& ballots, unsigned lastWinner);
};