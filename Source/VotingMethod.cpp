//#include "VotingMethod.h"
//
//void VotingMethod::SetBallots(std::vector<CardinalBallot> &ballots)
//{
//	_ballots = &ballots;
//}
//
//void VotingMethod::ResetBallots()
//{
//	for (CardinalBallot ballot : *_ballots)
//		ballot.Reset();
//}
//
//void VotingMethod::ClearBallots()
//{
//	_ballots->clear();
//}
//
//void VotingMethod::RemoveLastBallot()
//{
//	_ballots->pop_back();
//}
//
//std::vector<CardinalBallot> &VotingMethod::GetBallots()
//{
//	return *_ballots;
//}