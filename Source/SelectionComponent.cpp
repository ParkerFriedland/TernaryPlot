#include "SelectionComponent.h"

SelectionComponent::SelectionComponent() {}

unsigned SelectionComponent::SelectWinner(
	const std::vector<ScoreBallot>& ballots, const Domain& domain, unsigned seats)
{
	return SelectWinner(ballots, domain);
}

unsigned SelectionComponent::SelectWinner(
	const std::vector<ScoreBallot>& ballots, const Domain& domain)
{
	return SelectWinner(ballots, domain, 1);
}