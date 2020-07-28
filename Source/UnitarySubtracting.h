#include "ReweightingComponent.h"

class UnitarySubtracting : public ReweightingComponent
{
public:
	UnitarySubtracting();
	void ReweightBallots(std::vector<ScoreBallot> &ballots, unsigned lastWinner) override;
};