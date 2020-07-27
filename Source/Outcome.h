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
	unsigned GetNumSeats() const;
	unsigned GetNumSeats(unsigned candidate) const;
	unsigned GetNumCandidates() const;

	void SetTieFlag(bool flag);
	bool GetTieFlag() const;

private:
	std::vector<unsigned> _seats;
	bool _tie;
};