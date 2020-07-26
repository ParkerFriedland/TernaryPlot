// Code that was moved to the header file because visual studios sucks sometimes

//#include "MultiWinnerMethod.h"
//
//template<typename BallotType>
//MultiWinnerMethod<BallotType>::MultiWinnerMethod(unsigned seats, bool oneSeatPerWinner)
//	: _numSeats(seats), _oneSeatPerWinner(oneSeatPerWinner) {}
//
//template<typename BallotType>
//void MultiWinnerMethod<BallotType>::SetNumSeats(int numSeats)
//{
//	_numSeats = numSeats;
//	OnNumSeatsChange();
//}
//
//template<typename BallotType>
//unsigned MultiWinnerMethod<BallotType>::GetNumSeats()
//{
//	return _numSeats;
//}
//
//template<typename BallotType>
//void MultiWinnerMethod<BallotType>::SetOneSeatPerWinner(bool oneSeatPerWinner)
//{
//	_oneSeatPerWinner = oneSeatPerWinner;
//	OnNumSeatsPerWinnerChange();
//}
//
//template<typename BallotType>
//bool MultiWinnerMethod<BallotType>::IsOneSeatPerWinner()
//{
//	return _oneSeatPerWinner;
//}
//
//template<typename BallotType>
//Outcome &MultiWinnerMethod<BallotType>::CalculateResults(std::vector<CardinalBallot> &ballots)
//{
//	return CalculateResults(ballots, _numSeats, _oneSeatPerWinner);
//}
//
//template<typename BallotType>
//void MultiWinnerMethod<BallotType>::OnNumSeatsChange() {}
//
//template<typename BallotType>
//void MultiWinnerMethod<BallotType>::OnNumSeatsPerWinnerChange() {}