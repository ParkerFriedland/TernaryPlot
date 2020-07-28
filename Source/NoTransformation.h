#include "TransformComponent.h"

#pragma once

class NoTransform : public TransformComponent
{
public:
	std::vector<ScoreBallot> TransformBallots(std::vector<ScoreBallot> ballots) override;
};