#include "CardinalBallot.h"

class ReweightingComponent
{
public:
	virtual void ReweightBallots(std::vector<CardinalBallot> &ballots, unsigned lastWinner) = 0;
};