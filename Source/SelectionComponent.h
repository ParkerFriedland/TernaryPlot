#include "CardinalBallot.h"

#pragma once

class SelectionComponent
{
public:
	SelectionComponent();
	unsigned SelectWinner(const std::vector<CardinalBallot> &ballots, unsigned seats);
};