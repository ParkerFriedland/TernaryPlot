#include "Ballot.h"

#pragma once

Ballot::Ballot(unsigned candidiates, double weight, Random &prng) : _numCandidates(candidiates), _defaultWeight(weight), _currentWeight(weight), _rand(&prng) {}

void Ballot::Reset()
{
	ResetCurrentRoundWeight();
	ResetNonBaseAtributes();
}

void Ballot::Reset(double weight)
{
	ResetWeight(weight);
	ResetNonBaseAtributes();
}

void Ballot::ResetWeight(double weight)
{
	_defaultWeight = weight;
	_currentWeight = weight;
	_divisor = 1.0;
}

void Ballot::ResetCurrentRoundWeight()
{
	_currentWeight = _defaultWeight;
	_divisor = 1.0;
}

void Ballot::SetWeight(double weight)
{
	_currentWeight *= weight / _defaultWeight;
	_defaultWeight = weight;
}

void Ballot::SetCurrentWeight(double weight)
{
	_currentWeight = weight;
}

double Ballot::GetWeight() const
{
	return _defaultWeight;
}

double Ballot::GetCurrentRoundWeight() const
{
	return _currentWeight;
}

unsigned Ballot::GetNumCandidates() const
{
	return _numCandidates;
}

void Ballot::AddToDivisor(double amount)
{
	_divisor += amount;
	_currentWeight = _defaultWeight / _divisor;
}

const Random &Ballot::GetPRNG()
{
	return *_rand;
}