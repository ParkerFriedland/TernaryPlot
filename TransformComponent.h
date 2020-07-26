#include "CardinalBallot.h"

#pragma once

class TransformComponent
{
public:
	virtual std::vector<CardinalBallot> TransformBallots(std::vector<CardinalBallot> ballots) = 0;
};