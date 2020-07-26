#include "SequentialMethod.h"

class OrderingMethod : public SequentialMethod<CardinalBallot>
{
public:
	virtual unsigned CalculateNextWinner(std::vector<CardinalBallot> &ballots, const Outcome &winners, bool oneSeatPerWinner) = 0;

private:
	unsigned CalculateNextWinner(std::vector<CardinalBallot> &ballots, const Outcome &winners, unsigned seats, bool oneSeatPerWinner);
};