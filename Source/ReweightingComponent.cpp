#include "ReweightingComponent.h"

void ReweightingComponent::ReweightBallots(std::vector<ScoreBallot>& ballots, unsigned seats, unsigned lastWinner)
{
	ReweightBallots(ballots, lastWinner);
}

void ReweightingComponent::ReweightBallots(std::vector<ScoreBallot>& ballots, unsigned lastWinner)
{
	ReweightBallots(ballots, 1, lastWinner);
}