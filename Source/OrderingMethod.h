#include "SequentialMethod.h"

class OrderingMethod : public SequentialMethod<ScoreBallot>
{
public:
	unsigned CalculateNextWinner(
		std::vector<ScoreBallot> &ballots, const Domain &domain, const Outcome &winners, unsigned round, unsigned seats) override;
	virtual unsigned CalculateNextWinner(
		std::vector<ScoreBallot> &ballots, const Domain &domain, const Outcome &winners) = 0;
};