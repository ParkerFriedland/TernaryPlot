#include "ComponentStructured.h"

ComponentStructured::ComponentStructured(
	TransformComponent &transform, SelectionComponent &selection, ReweightingComponent &reweighting)
	: _trans(&transform), _select(&selection), _reweight(&reweighting) {}

unsigned ComponentStructured::CalculateNextWinner(
	std::vector<ScoreBallot> &ballots, const Domain &domain, const Outcome &winners, 
	unsigned seats, bool oneSeatPerWinner)
{
	return CalculateNextWinner(ballots, domain, seats);
}

unsigned ComponentStructured::CalculateNextWinner(std::vector<ScoreBallot> &ballots, const Domain &domain, unsigned seats)
{
	unsigned winner = _select->SelectWinner(ballots, domain, seats);
	_reweight->ReweightBallots(ballots, winner);
	return winner;
}