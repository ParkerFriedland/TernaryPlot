#include "OptimalMethod.h"
#include "ScoreBallot.h"

class PSI : public OptimalMethod<ScoreBallot, double>
{
public:
	PSI(unsigned accuracy = 256, bool oneSeatPerWinner = false);
	double CalculateOutcomeQuality(const std::vector<ScoreBallot>& ballots, const Outcome& outcome) override;

private:
	unsigned _accuracy;
};