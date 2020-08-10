#include "Outcome.h"

Outcome::Outcome(unsigned candidates) : _seats(std::vector<unsigned>()), _tie(false) 
{
	_seats.reserve(candidates);
	for (unsigned i = 0; i < candidates; ++i)
		_seats.push_back(0);
}

Outcome::Outcome(std::vector<unsigned> &seats) : _seats(seats), _tie(false) {}

void Outcome::SetSeats(std::vector<unsigned> &seats)
{
	_seats = seats;
}

void Outcome::AddSeat(unsigned nextWinner)
{
	++_seats[nextWinner];
}

void Outcome::ClearSeats()
{
	for (unsigned& candidate : _seats)
		candidate = 0;
	_tie = false;
}

const std::vector<unsigned> &Outcome::GetSeats()
{
	return _seats;
}

unsigned Outcome::GetNumSeats() const
{
	unsigned sum = 0;
	for (unsigned seatNum : _seats)
		sum += seatNum;
	return sum;
}

unsigned Outcome::GetNumSeats(unsigned candidate) const
{
	return _seats[candidate];
}

unsigned Outcome::GetNumCandidates() const
{
	return _seats.size();
}

void Outcome::SetTieFlag(bool flag)
{
	_tie = flag;
}

bool Outcome::GetTieFlag() const
{
	return _tie;
}