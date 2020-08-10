#include "RRV.h"

ReweightedRange::ReweightedRange(double delta, bool oneSeatPerWinner) : 
	_select(ScoreSelection()), _reweight(LinearDivisor(delta)) {}

unsigned ReweightedRange::CalculateNextWinner(
	std::vector<ScoreBallot>& ballots, const Domain& domain, const Outcome& winners)
{
	unsigned winner = _select.SelectWinner(ballots, domain);
	_reweight.ReweightBallots(ballots, winner);
	return winner;
}