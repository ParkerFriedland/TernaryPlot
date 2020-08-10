#include "SequentiallySubtractedScore.h"

SequentiallySubtractedScore::SequentiallySubtractedScore()
	: _trans(NoTransform()), _select(ScoreSelection()), _reweight(UnitarySubtracting()),
	ComponentStructured(
		reinterpret_cast<TransformComponent&>(_trans),
		reinterpret_cast<SelectionComponent&>(_select),
		reinterpret_cast<ReweightingComponent&>(_reweight)) {}