#include "SequentialMethod.h"

class OrderingMethod : public SequentialMethod<ScoreBallot>
{
public:
	unsigned CalculateNextWinner(
		std::vector<ScoreBallot> &ballots, const Domain &domain, const Outcome &winners, 
		unsigned seats, bool oneSeatPerWinner) override;
	virtual unsigned CalculateNextWinner(
		std::vector<ScoreBallot> &ballots, const Domain &domain, const Outcome &winners, 
		bool oneSeatPerWinner) = 0;
};