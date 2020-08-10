#include "SequentiallyScaledScore.h"

SequentiallyScaledScore::SequentiallyScaledScore()
	: _trans(NoTransform()), _select(ScoreSelection()), _reweight(UnitaryScaling()),
	ComponentStructured(
		reinterpret_cast<TransformComponent&>(_trans),
		reinterpret_cast<SelectionComponent&>(_select),
		reinterpret_cast<ReweightingComponent&>(_reweight)) {}