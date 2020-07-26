#include "ScoreBallot.h"

#pragma once

class SelectionComponent
{
public:
	SelectionComponent();
	unsigned SelectWinner(const std::vector<ScoreBallot> &ballots, unsigned seats);
};