#include "ReweightingComponent.h"

class LinearDivisor : public ReweightingComponent
{
public:
	LinearDivisor(double delta = 1);
	void SetDelta(double delta);
	double GetDelta(double delta);
	void ReweightBallots(std::vector<ScoreBallot> &ballots, int lastWinner);

private:
	double _delta;
};