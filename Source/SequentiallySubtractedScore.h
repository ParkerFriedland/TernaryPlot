#include "ComponentStructured.h"
#include "NoTransformation.h"
#include "ScoreSelection.h"
#include "UnitarySubtracting.h"


class SequentiallySubtractedScore : public ComponentStructured
{
public:
	SequentiallySubtractedScore();

private:
	NoTransform _trans;
	ScoreSelection _select;
	UnitarySubtracting _reweight;
};