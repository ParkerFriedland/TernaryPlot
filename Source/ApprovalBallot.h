#include <vector>
#include "Random.h"
#include "Ballot.h"
#include "Outcome.h"

#pragma once

class ApprovalBallot : public Ballot
{
public:
	ApprovalBallot(std::vector<bool> &approvals, double weight = 1.0, Random &prng = Random());

	void RandomizePrefrences();

	void SetApproval(bool approval, unsigned candidate);
	bool IsApproved(unsigned candidate) const;
	unsigned GetOutcomeApprovalSum(const Outcome &results) const; // for PAV
	double GetWeightedApproval(unsigned candidate) const;
	const std::vector<bool> &GetApprovals() const;

private:
	void ResetNonBaseAtributes() override;

	std::vector<bool> _approvals;
};