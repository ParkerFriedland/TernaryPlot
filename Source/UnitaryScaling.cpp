#include "UnitaryScaling.h"
#include "MathFunctions.h"

UnitaryScaling::UnitaryScaling() : ReweightingComponent() {}

void UnitaryScaling::ReweightBallots(std::vector<ScoreBallot> &ballots, unsigned seats, unsigned lastWinner)
{
	double influenceSpent = 0;

	for (ScoreBallot &ballot : ballots)
		influenceSpent += ballot.GetCalculatedScore(lastWinner);

	double quota = 1.0 / static_cast<double>(seats);

	if (influenceSpent < quota)
	{
		for (ScoreBallot &ballot : ballots)
			ballot.SetCurrentWeight(ballot.GetCurrentRoundWeight() - ballot.GetCalculatedScore(lastWinner));
	}
	else
	{
		double scale = quota / influenceSpent;

		for (ScoreBallot &ballot : ballots)
			ballot.SetCurrentWeight(ballot.GetCurrentRoundWeight() - scale * ballot.GetCalculatedScore(lastWinner));
	}
}