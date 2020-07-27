#include "OrderingMethod.h"

unsigned OrderingMethod::CalculateNextWinner(
	std::vector<ScoreBallot> &ballots, const Domain &domain, const Outcome &winners, 
	unsigned seats, bool oneSeatPerWinner)
{
	return CalculateNextWinner(ballots, domain, winners, oneSeatPerWinner);
}