#include "FinalRoundStructured.h"

FinalRoundStructured::FinalRoundStructured(
	TransformComponent& transform, 
	SelectionComponent& selection, SelectionComponent &finalSelection, 
	ReweightingComponent& reweighting)
	: _trans(&transform), _select(&selection), _final(&finalSelection), _reweight(&reweighting) {}

unsigned FinalRoundStructured::CalculateNextWinner(
	std::vector<ScoreBallot>& ballots, const Domain& domain, const Outcome& winners, unsigned round, unsigned seats)
{
	return CalculateNextWinner(ballots, domain, round, seats);
}

unsigned FinalRoundStructured::CalculateNextWinner(
	std::vector<ScoreBallot>& ballots, const Domain& domain, unsigned round, unsigned seats)
{
	if (round < seats)
	{
		unsigned winner = _select->SelectWinner(ballots, domain, seats);
		_reweight->ReweightBallots(ballots, seats, winner);
		return winner;
	}
	else
		return _final->SelectWinner(ballots, domain, seats);
}