#include "PSI.h"
#include "MathFunctions.h"

PSI::PSI(unsigned accuracy, bool oneSeatPerWinner) : _accuracy(accuracy), OptimalMethod(oneSeatPerWinner) {}

double PSI::CalculateOutcomeQuality(const std::vector<ScoreBallot>& ballots, const Outcome& outcome)
{
	double quality = 0;
	
	// todo: implement a much more efficiant way of doing this that reuses digamma values for
	// ballots that had the exact same total raw score. Or would that not be more efficiant because
	// it's much less cash freindly? Perhaps I should create a hashtable to store previously used
	// digamma values? IDK but this will do for now. Will probably be the most computationally expensive
	// method by far. If I ever test PSI in my ternary search plot I think I will do it manually, optimized
	// for that so optimizing this can wait until I have a use for it.
	for (ScoreBallot ballot : ballots)
		quality += NormalizedDigamma(ballot.GetTotalRawScore(outcome), _accuracy);

	return quality;
}