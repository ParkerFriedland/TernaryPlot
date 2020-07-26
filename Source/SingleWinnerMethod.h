#include "VotingMethod.h"

class SinlgeWinnerMethod : public VotingMethod<CardinalBallot>
{
public:
	SinlgeWinnerMethod();
	Outcome CalculateResults();
	virtual int CalculateWinner() = 0;

private:
	Outcome CalculateResults(int seats, int maxSeatsPerWinner);
};