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

double ApprovalBallot::IsApproved(unsigned candidate) const
{
	return _approvals[candidate];
}

double ApprovalBallot::GetNumApprovals() const
{
	double sum = 0;
	for (int i = 0; i < _approvals.size(); ++i)
		sum += _approvals[i];

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
