#include "ReweightingComponent.h"

class UnitaryScaling : public ReweightingComponent
{
public:
	UnitaryScaling();
	void ReweightBallots(std::vector<ScoreBallot> &ballots, unsigned seats, unsigned lastWinner) override;
};