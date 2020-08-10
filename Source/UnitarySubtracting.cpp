#include "UnitarySubtracting.h"
#include "MathFunctions.h"

UnitarySubtracting::UnitarySubtracting() : ReweightingComponent() {}

void UnitarySubtracting::ReweightBallots(std::vector<ScoreBallot> &ballots, unsigned seats, unsigned lastWinner)
{
	double influenceSpent = 0;

	for (ScoreBallot ballot : ballots)
		influenceSpent += ballot.GetCalculatedScore(lastWinner);

	double quota = 1.0 / static_cast<double>(seats);

	if (influenceSpent < quota)
	{
		for (ScoreBallot &ballot : ballots)
			ballot.SetSubtractor(ballot.GetSubtractor() + ballot.GetUnweightedCalculatedScore(lastWinner));
	}
	else
	{
		double scale = quota / influenceSpent;

		for (ScoreBallot &ballot : ballots)
			ballot.SetSubtractor(ballot.GetSubtractor() + scale * ballot.GetUnweightedCalculatedScore(lastWinner));
	}
}