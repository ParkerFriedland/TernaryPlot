// Code that was moved to the header file because visual studios sucks sometimes

//#include "SequentialMethod.h"
//
//SequentialMethod::SequentialMethod(unsigned seats, bool oneSeatPerWinner) : MultiWinnerMethod(seats, oneSeatPerWinner) {}
//
//Outcome &SequentialMethod::CalculateResults(std::vector<CardinalBallot> &ballots, unsigned seats, bool oneSeatPerWinner)
//{
//	results.ClearSeats();
//	for(unsigned i = 0; i < seats; ++i)
//		results.AddSeat(CalculateNextWinner(ballots, results, seats, oneSeatPerWinner));
//	return results;
//}