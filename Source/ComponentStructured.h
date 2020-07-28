#include "SequentialMethod.h"
#include "TransformComponent.h"
#include "SelectionComponent.h"
#include "ReweightingComponent.h"

#pragma once

class ComponentStructured : public SequentialMethod<ScoreBallot>
{
public:
	ComponentStructured(TransformComponent &transform, SelectionComponent &selection, ReweightingComponent &reweighting);
	unsigned CalculateNextWinner(
		std::vector<ScoreBallot> &ballots, const Domain &domain, const Outcome &winners, 
		unsigned seats, bool oneSeatPerWinner) override;
	unsigned CalculateNextWinner(std::vector<ScoreBallot> &ballots, const Domain &domain, unsigned seats);
	
private:
	TransformComponent *_trans;
	SelectionComponent *_select;
	ReweightingComponent *_reweight;
};