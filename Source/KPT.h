#include "TransformComponent.h"

#pragma once

class KPT : public TransformComponent
{
public:
	std::vector<ScoreBallot> TransformBallots(std::vector<ScoreBallot> ballots) override;
};