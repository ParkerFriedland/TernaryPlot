#include "OptimalMethod.h"

class Monroe : public OptimalMethod
{
public:
	Monroe(bool oneSeatPerWinner = false);
	double CalculateOutcomeQuality(Outcome &outcome);
};