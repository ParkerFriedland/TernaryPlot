#include "SequentialMethod.h"
#include "TransformComponent.h"
#include "SelectionComponent.h"
#include "ReweightingComponent.h"

#pragma once

class FinalRoundStructured : public SequentialMethod<ScoreBallot>
{
public:
	FinalRoundStructured(
		TransformComponent& transform, 
		SelectionComponent& selection, SelectionComponent& finalSelection,
		ReweightingComponent& reweighting);
	unsigned CalculateNextWinner(
		std::vector<ScoreBallot>& ballots, const Domain& domain, const Outcome& winners, unsigned round, unsigned seats) override;
	unsigned CalculateNextWinner(std::vector<ScoreBallot>& ballots, const Domain& domain, unsigned round, unsigned seats);

private:
	TransformComponent* _trans;
	SelectionComponent* _select;
	SelectionComponent* _final;
	ReweightingComponent* _reweight;
};