#include "ComponentStructured.h"

ComponentStructured::ComponentStructured(
	TransformComponent &transform, SelectionComponent &selection, ReweightingComponent &reweighting)
	: _transform(&transform), _selection(&selection), _reweight(&reweighting) {}

unsigned ComponentStructured::CalculateNextWinner(std::vector<CardinalBallot> &ballots, const Outcome &winners, unsigned seats, bool oneSeatPerWinner)
{
	return CalculateNextWinner(ballots, seats);
}

unsigned ComponentStructured::CalculateNextWinner(std::vector<CardinalBallot> &ballots, unsigned seats)
{
	unsigned winner = _selection->SelectWinner(ballots, seats);
	_reweight->ReweightBallots(ballots, winner);
	return winner;
}