#include "Domain.h"

#pragma once

class Outcome
{
public:
	Outcome(unsigned candidates);
	Outcome(std::vector<unsigned> &seats);

	void SetSeats(std::vector<unsigned> &seats);
	void AddSeat(unsigned nextWinner);
	void ClearSeats();

	const std::vector<unsigned> &GetSeats();
	unsigned GetNumSeats();
	unsigned GetNumSeats(unsigned candidate);
	unsigned GetNumCandidates();

	void SetTieFlag(bool flag);
	bool GetTieFlag();

private:
	std::vector<unsigned> _seats;
	bool _tie;
};