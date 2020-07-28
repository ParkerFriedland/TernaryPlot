#include "Harmonic.h"

Harmonic::Harmonic(unsigned seats, bool oneSeatPerWinner) : OptimalMethod(seats, oneSeatPerWinner) {}

double Harmonic::CalculateOutcomeQuality(const std::vector<ScoreBallot> &ballots, const Outcome &outcome)
{
	double quality = 0;

	for (ScoreBallot ballot : ballots)
	{
		double score = 1.0, divisor = 0.0;
		unsigned currWinnerSeats;
		while ((currWinnerSeats = ballot.NextHighestScore(score, outcome)))
			for (unsigned seat = 0; seat < currWinnerSeats; ++seat)
				quality += score / ++divisor;
	}

	return quality;
}