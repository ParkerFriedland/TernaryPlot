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

void LinearDivisor::ReweightBallots(std::vector<CardinalBallot> &ballots, int lastWinner)
{
	for (CardinalBallot ballot : ballots)
		ballot.AddToDivisor(ballot.GetRawScore(lastWinner) / _delta);
}