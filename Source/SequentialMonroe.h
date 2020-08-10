#include "SequentialMethod.h"

#pragma once

class SequentialMonroe : public SequentialMethod<ScoreBallot>
{
public:
	SequentialMonroe(unsigned seats = 2, bool oneSeatPerWinner = false);

	virtual unsigned CalculateNextWinner(
		std::vector<ScoreBallot>& ballots, const Domain& domain, const Outcome& winners, unsigned round, unsigned seats) override;

private:
	double badCode[3] {0};
};