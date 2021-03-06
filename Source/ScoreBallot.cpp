#include "ScoreBallot.h"
#include "MathFunctions.h"

#pragma once

ScoreBallot::ScoreBallot(std::vector<double> &scores, double weight, Random &prng)
	: _scores(scores), Ballot(scores.size(), weight, prng) {}

void ScoreBallot::RandomizePrefrences()
{
	for (int i = 0; i < _scores.size(); ++i)
		_scores[i] = GetPRNG().Double();
}

void ScoreBallot::ResetNonBaseAtributes()
{
	ScoreBallot::ResetScoreCap();
	ScoreBallot::ResetSubtractor();
}

void ScoreBallot::ResetScoreCap()
{
	_cap = 1.0;
}

void ScoreBallot::ResetSubtractor()
{
	_sub = 0.0;
}

double ScoreBallot::GetScoreCap() const
{
	return _cap;
}

double ScoreBallot::GetSubtractor() const
{
	return _sub;
}

void ScoreBallot::SetScoreCap(double cap)
{
	_cap = cap;
}

void ScoreBallot::SetSubtractor(double subtractor)
{
	_sub = subtractor;
}

void ScoreBallot::SetScore(double score, unsigned candidate)
{
	_scores[candidate] = score;
}

double ScoreBallot::GetRawScore(unsigned candidate) const
{
	return _scores[candidate];
}

double ScoreBallot::GetTotalRawScore() const
{
	double sum = 0;
	for (int i = 0; i < _scores.size(); ++i)
		sum += _scores[i];

	return sum;
}

double ScoreBallot::GetTotalRawScore(const Outcome &results) const
{
	double sum = 0;
	for (unsigned i = 0; i < _scores.size(); ++i)
		sum += results.GetNumSeats(i) * _scores[i];

	return sum;
}

double ScoreBallot::GetCalculatedScore(unsigned candidate) const
{
	return GetCurrentRoundWeight() * Max<double>(Min<double>(_scores[candidate] - _sub, _cap), 0);
}

double ScoreBallot::GetUnweightedCalculatedScore(unsigned candidate) const
{
	return Max<double>(Min<double>(_scores[candidate] - _sub, _cap), 0);
}

const std::vector<double> &ScoreBallot::GetScores() const
{
	return _scores;
}

unsigned ScoreBallot::NextHighestScore(double &score, const Outcome &results) const
{
	double max = 0.0;
	unsigned i = 0;
	while(i < _scores.size())
		if (_scores[i] < score && _scores[i] > max && results.GetNumSeats(i))
			max = _scores[i++];

	score = max;
	return max ? results.GetNumSeats(i) : 0;
}