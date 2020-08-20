#include "SequentialMethod.h"

#pragma once

class SequentialMonroe : public SequentialMethod<ScoreBallot>
{
public:
	SequentialMonroe(unsigned seats = 2, bool oneSeatPerWinner = false);

	virtual unsigned CalculateNextWinner(
		std::vector<ScoreBallot>& ballots, const Domain& domain, const Outcome& winners, unsigned round, unsigned seats) override;

private:
	double sortedScores[3]{ 0 }; // bad code
	double currExaustionCoeficient[3]{ 0 }; // also bad code
	double finalExaustionCoeficient[3]{ 0 }; // also bad code

	double FindNextHighestScores(unsigned &i, const std::vector<ScoreBallot> &ballots,
		double &scoreSum, double &weightSum, double &quotaleft, unsigned currCandidate);
};