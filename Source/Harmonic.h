#include "OptimalMethod.h"
#include "PAV.h"
#include "KPT.h"

class Harmonic : public OptimalMethod<ScoreBallot>
{
public:
	Harmonic(unsigned seats = 2, bool oneSeatPerWinner = false);
	double CalculateOutcomeQuality(const std::vector<ScoreBallot> &ballots, const Outcome &outcome) override;
};