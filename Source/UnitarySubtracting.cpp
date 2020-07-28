#include "UnitarySubtracting.h"

UnitarySubtracting::UnitarySubtracting() : ReweightingComponent() {}

void UnitarySubtracting::ReweightBallots(std::vector<ScoreBallot> &ballots, unsigned lastWinner)
{
	for (ScoreBallot ballot : ballots)
		ballot.SetSubtractor(ballot.GetSubtractor() + ballot.GetRawScore(lastWinner));
}