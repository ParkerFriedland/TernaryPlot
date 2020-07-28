#include "ScoreBallot.h"
#include "Domain.h"

#pragma once

class SelectionComponent
{
public:
	SelectionComponent();

	// to-do: figure out how to return ties
	//
	// I need to figure out how to handel that without returning a full Outcome object.
	// Perhaps Outcome should be a base class for both single winner and multi winner outcomes?
	virtual unsigned SelectWinner(const std::vector<ScoreBallot> &ballots, const Domain &domain, unsigned seats) = 0;
};