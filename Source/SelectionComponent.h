#include "ScoreBallot.h"
#include "Domain.h"

#pragma once

class SelectionComponent
{
public:
	SelectionComponent();
	unsigned SelectWinner(const std::vector<ScoreBallot> &ballots, const Domain &domain, unsigned seats);
};