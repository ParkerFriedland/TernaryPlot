#include "SequentiallySubtractedScore.h"

SequentiallySubtractedScore::SequentiallySubtractedScore()
	: _trans(NoTransform()), _select(ScoreSelection()), _reweight(UnitarySubtracting()),
	ComponentStructured(
		dynamic_cast<TransformComponent&>(_trans),
		dynamic_cast<SelectionComponent&>(_select),
		dynamic_cast<ReweightingComponent&>(_select)) {}