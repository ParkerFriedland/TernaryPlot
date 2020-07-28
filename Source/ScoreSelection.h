#include "SelectionComponent.h"

class ScoreSelection : public SelectionComponent
{
public:
	ScoreSelection();
	unsigned SelectWinner(const std::vector<ScoreBallot> &ballots, const Domain &domain, unsigned seats);
};