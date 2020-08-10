#include "FinalRoundStructured.h"
#include "NoTransformation.h"
#include "ScoreSelection.h"
#include "STARSelection.h"
#include "LinearDivisor.h"


class ReweightedSTAR : public FinalRoundStructured
{
public:
	ReweightedSTAR();

private:
	NoTransform _trans;
	ScoreSelection _select;
	STARSelection _final;
	LinearDivisor _reweight;
};