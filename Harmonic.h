#include "OptimalMethod.h"
#include "PAV.h"
#include "KPT.h"

class Harmonic : public OptimalMethod<CardinalBallot>
{
public:
	Harmonic(unsigned seats = 2, bool oneSeatPerWinner = false);
	double CalculateOutcomeQuality(const std::vector<CardinalBallot> &ballots, const Outcome &outcome) override;
};