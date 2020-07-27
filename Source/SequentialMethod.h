#include "MultiWinnerMethod.h"

#pragma once

template<typename BallotType = ScoreBallot>
class SequentialMethod : public MultiWinnerMethod<BallotType>
{
public:
	SequentialMethod(unsigned seats = 2, bool oneSeatPerWinner = false);
	void CalculateResults(
		std::vector<BallotType> &ballots, Domain &domain, Outcome &results, 
		unsigned seats, bool oneSeatPerWinner) override;

	virtual unsigned CalculateNextWinner(
		std::vector<BallotType> &ballots, const Domain &domain, const Outcome &winners, 
		unsigned seats, bool oneSeatPerWinner) = 0;

private:
	Outcome results;
};

// If I wasn't working in Visual Studios, I would just include all of this code in the cpp file 
// (and include the cpp file in this header), but because VS loves to make it harder to use templates, 
// the code is here instead:

template<typename BallotType>
SequentialMethod<BallotType>::SequentialMethod(unsigned seats, bool oneSeatPerWinner) : results(0), MultiWinnerMethod(seats, oneSeatPerWinner) {}

template<typename BallotType>
void SequentialMethod<BallotType>::CalculateResults(
	std::vector<BallotType> &ballots, Domain &domain, Outcome &results,
	unsigned seats, bool oneSeatPerWinner)
{
	for (unsigned i = 0; i < seats; ++i)
		results.AddSeat(CalculateNextWinner(ballots, domain, results, seats, oneSeatPerWinner));
}