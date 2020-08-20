#include <vector>
#include "Random.h"

#pragma once

class Ballot
{
public:
	Ballot(unsigned candidates = 3, double weight = 1.0, Random &prng = Random());

	virtual void RandomizePrefrences() = 0;

	void Reset();
	void Reset(double weight);
	void ResetWeight(double weight);
	void ResetCurrentRoundWeight();
	void SetWeight(double weight);
	void SetCurrentWeight(double weight);
	double GetWeight() const;
	double GetCurrentRoundWeight() const;

	unsigned GetNumCandidates() const;

	void SetDivisor(double amount); // for divisor based re-weighting methods
	void AddToDivisor(double amount); // for divisor based re-weighting methods
	double GetDivisor(); // for divisor based re-weighting methods

protected:
	virtual void ResetNonBaseAtributes() = 0;
	const Random &GetPRNG();

private:
	unsigned _numCandidates;

	double _defaultWeight; // how much weight your vote has overall
	double _currentWeight; // how much weight your vote has in a given round of selection
	double _divisor = 1.0;
	bool _exausted = false;

	Random *_rand;
};