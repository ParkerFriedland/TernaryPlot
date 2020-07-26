#include "SequentialMethod.h"
#include "TransformComponent.h"
#include "SelectionComponent.h"
#include "ReweightingComponent.h"

#pragma once

class ComponentStructured : public SequentialMethod<CardinalBallot>
{
public:
	ComponentStructured(TransformComponent &transform, SelectionComponent &selection, ReweightingComponent &reweighting);
	unsigned CalculateNextWinner(std::vector<CardinalBallot> &ballots, const Outcome &winners, unsigned seats, bool oneSeatPerWinner) override;
	unsigned CalculateNextWinner(std::vector<CardinalBallot> &ballots, unsigned seats);
	
private:
	TransformComponent *_transform;
	SelectionComponent *_selection;
	ReweightingComponent *_reweight;
};