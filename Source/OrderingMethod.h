#include "SequentialMethod.h"

class OrderingMethod : public SequentialMethod<ScoreBallot>
{
public:
	virtual unsigned CalculateNextWinner(std::vector<ScoreBallot> &ballots, const Outcome &winners, bool oneSeatPerWinner) = 0;

private:
	unsigned CalculateNextWinner(std::vector<ScoreBallot> &ballots, const Outcome &winners, unsigned seats, bool oneSeatPerWinner);
};