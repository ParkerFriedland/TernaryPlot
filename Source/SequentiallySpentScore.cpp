#include "SequentiallySpentScore.h"

SequentiallySpentScore::SequentiallySpentScore()
	: _trans(NoTransform()), _select(ScoreSelection()), _reweight(UnitaryCapping()),
	ComponentStructured(
		dynamic_cast<TransformComponent&>(_trans),
		dynamic_cast<SelectionComponent&>(_select),
		dynamic_cast<ReweightingComponent&>(_select)) {}