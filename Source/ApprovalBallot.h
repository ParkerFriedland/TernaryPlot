#include <vector>
#include "Random.h"
#include "Ballot.h"

#pragma once

class ApprovalBallot : public Ballot
{
public:
	ApprovalBallot(std::vector<bool> &approvals, double weight = 1.0, Random &prng = Random());

	void RandomizePrefrences();

	void SetApproval(bool approval, unsigned candidate);
	double IsApproved(unsigned candidate) const;
	double GetNumApprovals() const; // For distributed vote and methods related to culmutive voting
	double GetWeightedApproval(unsigned candidate) const;
	const std::vector<bool> &GetApprovals() const;

private:
	void ResetNonBaseAtributes() override;

	std::vector<bool> _approvals;
};