#include "ComponentStructured.h"
#include "NoTransformation.h"
#include "ScoreSelection.h"
#include "UnitaryScaling.h"


class SequentiallyScaledScore : public ComponentStructured
{
public:
	SequentiallyScaledScore();

private:
	NoTransform _trans;
	ScoreSelection _select;
	UnitaryScaling _reweight;
};