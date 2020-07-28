#include "UnitaryCapping.h"

UnitaryCapping::UnitaryCapping() : ReweightingComponent() {}

void UnitaryCapping::ReweightBallots(std::vector<ScoreBallot> &ballots, unsigned lastWinner)
{
	for (ScoreBallot ballot : ballots)
		ballot.SetScoreCap(ballot.GetScoreCap() - ballot.GetRawScore(lastWinner));
}