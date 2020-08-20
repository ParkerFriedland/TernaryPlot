#include "SingleDistributedVote.h"

SingleDistributedVote::SingleDistributedVote(double delta, bool oneSeatPerWinner) :
	_delta(delta), _select(ScoreSelection()) {}

unsigned SingleDistributedVote::CalculateNextWinner(
	std::vector<ScoreBallot>& ballots, const Domain& domain, const Outcome& winners)
{
	unsigned numCandidates = ballots[0].GetNumCandidates();

	for (ScoreBallot& ballot : ballots)
		ballot.SetDivisor(ballot.GetTotalRawScore(winners));

	unsigned currWinner = 0;
	double highScore = 0;
	for (unsigned potentialWinner = 0; potentialWinner < numCandidates; ++potentialWinner)
	{
		double squaredSum = 0;
		for (ScoreBallot& ballot : ballots)
		{
			double rawScore = ballot.GetRawScore(potentialWinner);
			if (rawScore)
				squaredSum += ballot.GetWeight() * (rawScore * rawScore) / ((ballot.GetDivisor() / _delta) + rawScore);
		}
		if (squaredSum > highScore)
		{
			highScore = squaredSum;
			currWinner = potentialWinner;
		}
	}
	return currWinner;
}