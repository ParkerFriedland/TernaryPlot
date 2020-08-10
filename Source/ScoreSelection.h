#include "SelectionComponent.h"

#pragma once

class ScoreSelection : public SelectionComponent
{
public:
	ScoreSelection();
	unsigned SelectWinner(const std::vector<ScoreBallot> &ballots, const Domain &domain) override;
};