#include "SelectionComponent.h"

#pragma once

class STARSelection : public SelectionComponent
{
public:
	STARSelection();
	unsigned SelectWinner(const std::vector<ScoreBallot>& ballots, const Domain& domain) override;
};