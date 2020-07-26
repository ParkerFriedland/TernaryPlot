#include "LinearDivisor.h"

LinearDivisor::LinearDivisor(double delta) : _delta(delta) {}

void LinearDivisor::SetDelta(double delta)
{
	_delta = delta;
}

double LinearDivisor::GetDelta(double delta)
{
	return _delta;
}

void LinearDivisor::ReweightBallots(std::vector<ScoreBallot> &ballots, int lastWinner)
{
	for (ScoreBallot ballot : ballots)
		ballot.AddToDivisor(ballot.GetRawScore(lastWinner) / _delta);
}