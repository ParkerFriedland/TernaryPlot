// Code that was moved to the header file because visual studios sucks sometimes

//#include "OptimalMethod.h"
//
//OptimalMethod::OptimalMethod(unsigned seats, bool oneSeatPerWinner) : MultiWinnerMethod(seats, oneSeatPerWinner) {}
//
//OptimalMethod::OptimalMethod(std::vector<Outcome> &possibleOutcomes) : MultiWinnerMethod(0) // arguement here is irrelevent because it will be changed later
//{
//	SetPossibleOutcomes(possibleOutcomes);
//}
//
//std::vector<Outcome> OptimalMethod::GeneratePosssibleOutcomes(int numSeats, bool oneSeatPerWinner)
//{
//	return std::vector<Outcome>(); // todo
//}
//
//void OptimalMethod::SetPosssibleOutcomes(int numSeats, bool oneSeatPerWinner)
//{
//	_outcomeList = &GeneratePosssibleOutcomes(numSeats, oneSeatPerWinner);
//}
//
//void OptimalMethod::SetPossibleOutcomes(std::vector<Outcome> &possibleOutcomes)
//{
//	int maxNumSeats = 0;
//	bool oneSeatPerWinner = true;
//
//	for (Outcome &outcome : possibleOutcomes)
//	{
//		int currNumSeats = outcome.GetNumSeats();
//		if (maxNumSeats < currNumSeats)
//			maxNumSeats = currNumSeats;
//
//		std::vector<unsigned> seats = outcome.GetSeats();
//
//		for (int seatNum : seats)
//			if (seatNum > 1)
//				oneSeatPerWinner = false;
//	}
//
//	SetNumSeats(maxNumSeats);
//	SetOneSeatPerWinner(oneSeatPerWinner);
//
//	delete _outcomeList;
//	_outcomeList = &possibleOutcomes;
//	_isOutcomeListDirty = false;
//}
//
//std::vector<Outcome> &OptimalMethod::GetPossibleOutcomes()
//{
//	return *_outcomeList;
//}
//
//Outcome &OptimalMethod::CalculateResults(std::vector<CardinalBallot> &ballots, unsigned seats, bool oneSeatPerWinner)
//{
//	if (_isOutcomeListDirty)
//		SetPosssibleOutcomes(GetNumSeats(), IsOneSeatPerWinner());
//
//	return CalculateResults(ballots, *_outcomeList);
//}
//
//Outcome &OptimalMethod::CalculateResults(std::vector<CardinalBallot> &ballots, const std::vector<Outcome> &possibleOutcomes)
//{
//	double maxQuality = CalculateOutcomeQuality(ballots, possibleOutcomes[0]);
//	int best = 0;
//	bool tie = false;
//	for (int i = 1; i < possibleOutcomes.size(); ++i)
//	{
//		double currQuality = CalculateOutcomeQuality(ballots, possibleOutcomes[i]);
//		if (maxQuality <= currQuality)
//		{
//			maxQuality = currQuality;
//			tie = maxQuality == currQuality;
//		}
//	}
//
//	Outcome results = Outcome(possibleOutcomes[best]);
//	results.SetTieFlag(tie);
//	return results;
//}
//
//void OptimalMethod::OnNumSeatsChange()
//{
//	_isOutcomeListDirty = true;
//}
//
//void OptimalMethod::OnNumSeatsPerWinnerChange()
//{
//	_isOutcomeListDirty = true;
//}