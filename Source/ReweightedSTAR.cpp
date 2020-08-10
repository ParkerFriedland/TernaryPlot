#include "ReweightedSTAR.h"

ReweightedSTAR::ReweightedSTAR()
	: _trans(NoTransform()), _select(ScoreSelection()), _final(STARSelection()), _reweight(LinearDivisor(0.5)),
	FinalRoundStructured(
		reinterpret_cast<TransformComponent&>(_trans),
		reinterpret_cast<SelectionComponent&>(_select),
		reinterpret_cast<SelectionComponent&>(_final),
		reinterpret_cast<ReweightingComponent&>(_reweight)) {}