#include "ScoreBallot.h"
#include "MathFunctions.h"

#pragma once

ScoreBallot::ScoreBallot(std::vector<double> &scores, double weight, Random &prng)
	: _scores(scores), Ballot(weight, prng) {}

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

double ScoreBallot::GetCalculatedScore(unsigned candidate) const
{
	return GetCurrentRoundWeight() * Max<double>(Min<double>(_scores[candidate] - _sub, _cap), 0);
}

const std::vector<double> &ScoreBallot::GetScores() const
{
	return _scores;
}

double ScoreBallot::NextHighestScore(double &score) const
{
	double max = 0.0;
	for (int i = 0; i < _scores.size(); ++i)
		if (_scores[i] > max && _scores[i] < score)
			max = _scores[i];
	
	double gap = max - score;
	score = max;
	return gap;
}