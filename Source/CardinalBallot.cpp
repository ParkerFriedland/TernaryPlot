#include "CardinalBallot.h"
#include "MathFunctions.h"

#pragma once

CardinalBallot::CardinalBallot(std::vector<double> &scores, double weight, Random &prng)
	: _scores(scores), Ballot(weight, prng) {}

void CardinalBallot::RandomizePrefrences()
{
	for (int i = 0; i < _scores.size(); ++i)
		_scores[i] = GetPRNG().Double();
}

void CardinalBallot::ResetNonBaseAtributes()
{
	CardinalBallot::ResetScoreCap();
	CardinalBallot::ResetSubtractor();
}

void CardinalBallot::ResetScoreCap()
{
	_cap = 1.0;
}

void CardinalBallot::ResetSubtractor()
{
	_sub = 0.0;
}

double CardinalBallot::GetScoreCap() const
{
	return _cap;
}

double CardinalBallot::GetSubtractor() const
{
	return _sub;
}

void CardinalBallot::SetScoreCap(double cap)
{
	_cap = cap;
}

void CardinalBallot::SetSubtractor(double subtractor)
{
	_sub = subtractor;
}

void CardinalBallot::SetScore(double score, unsigned candidate)
{
	_scores[candidate] = score;
}

double CardinalBallot::GetRawScore(unsigned candidate) const
{
	return _scores[candidate];
}

double CardinalBallot::GetTotalRawScore() const
{
	double sum = 0;
	for (int i = 0; i < _scores.size(); ++i)
		sum += _scores[i];

	return sum;
}

double CardinalBallot::GetCalculatedScore(unsigned candidate) const
{
	return GetCurrentRoundWeight() * Max<double>(Min<double>(_scores[candidate] - _sub, _cap), 0);
}

const std::vector<double> &CardinalBallot::GetScores() const
{
	return _scores;
}

double CardinalBallot::NextHighestScore(double &score) const
{
	double max = 0.0;
	for (int i = 0; i < _scores.size(); ++i)
		if (_scores[i] > max && _scores[i] < score)
			max = _scores[i];
	
	double gap = max - score;
	score = max;
	return gap;
}