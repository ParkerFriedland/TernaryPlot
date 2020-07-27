#include "ApprovalBallot.h"
#include "MathFunctions.h"

#pragma once

ApprovalBallot::ApprovalBallot(std::vector <bool> &approvals, double weight, Random &prng)
	: _approvals(approvals), Ballot(weight, prng) {}

void ApprovalBallot::RandomizePrefrences()
{
	for (int i = 0; i < _approvals.size(); ++i)
		_approvals[i] = GetPRNG().Double();
}

void ApprovalBallot::ResetNonBaseAtributes() {}

void ApprovalBallot::SetApproval(bool approval, unsigned candidate)
{
	_approvals[candidate] = approval;
}

bool ApprovalBallot::IsApproved(unsigned candidate) const
{
	return _approvals[candidate];
}

unsigned ApprovalBallot::GetOutcomeApprovalSum(const Outcome &result) const
{
	unsigned sum = 0;
	for (int i = 0; i < _approvals.size(); ++i)
		if(_approvals[i])
			sum += result.GetNumSeats(i);

	return sum;
}

double ApprovalBallot::GetWeightedApproval(unsigned candidate) const
{
	return _approvals[candidate] ? GetCurrentRoundWeight() : 0;
}

const std::vector<bool> &ApprovalBallot::GetApprovals() const
{
	return _approvals;
}
