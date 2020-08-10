#include "ReweightingComponent.h"

#pragma once

class LinearDivisor : public ReweightingComponent
{
public:
	LinearDivisor(double delta = 1);
	void SetDelta(double delta);
	double GetDelta(double delta);
	void ReweightBallots(std::vector<ScoreBallot> &ballots, unsigned lastWinner) override;

private:
	double _delta;
};