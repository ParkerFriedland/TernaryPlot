#include "ScoreBallot.h"

class ReweightingComponent
{
public:
	virtual void ReweightBallots(std::vector<ScoreBallot> &ballots, unsigned lastWinner) = 0;
};