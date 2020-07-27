#include <vector>
#include "Random.h"
#include "Ballot.h"
#include "Outcome.h"

#pragma once

class ScoreBallot : public Ballot
{
public:
	ScoreBallot(std::vector<double> &scores, double weight = 1.0, Random &prng = Random());

	void RandomizePrefrences();

	void SetScore(double score, unsigned candidate);
	double GetRawScore(unsigned candidate) const;
	double GetTotalRawScore() const; // For distributed vote and methods related to culmutive voting.
	double GetCalculatedScore(unsigned candidate) const;
	const std::vector<double> &GetScores() const;
	//std::vector<ApprovalBallot> KPT(); will add once I add ApprovalBallot class

	unsigned NextHighestScore(double &score, const Outcome &results) const; // For harmonic voting.

	// For sequentaily spent score. 
	// Would like to factor out of this class since only one voting method uses these methods.
	void ResetScoreCap();
	void SetScoreCap(double cap);
	double GetScoreCap() const;

	// For sequentaily spent score. 
	// Would like to factor out of this class since only one voting method uses these methods.
	void ResetSubtractor();
	void SetSubtractor(double subtractor);
	double GetSubtractor() const;

private:
	void ResetNonBaseAtributes() override;

	std::vector<double> _scores;

	double _cap = 1.0; // For sequentaily spent score.
					   // Would like to factor out of this class since only one voting method uses this.
	double _sub = 0.0; // For sequentaily subtracted score.
					   // Would like to factor out of this class since only one voting method uses this.
};