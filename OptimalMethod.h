#include "MultiWinnerMethod.h"

#pragma once

template<typename BallotType = CardinalBallot, typename QualityValue = double>
class OptimalMethod : public MultiWinnerMethod<BallotType>
{
public:
	OptimalMethod(unsigned seats = 2, bool oneSeatPerWinner = false);
	OptimalMethod(std::vector<Outcome> &possibleOutcomes);

	static std::vector<Outcome> GeneratePosssibleOutcomes(int numSeats = 2, bool oneSeatPerWinner = false);
	void SetPosssibleOutcomes(int numSeats = 2, bool oneSeatPerWinner = false);
	void SetPossibleOutcomes(std::vector<Outcome> &possibleOutcomes);
	std::vector<Outcome> &GetPossibleOutcomes();

	Outcome &CalculateResults(std::vector<BallotType> &ballots, unsigned seats, bool oneSeatPerWinner) override;
	Outcome &CalculateResults(std::vector<BallotType> &ballots, const std::vector<Outcome> &possibleOutcomes);
	virtual QualityValue CalculateOutcomeQuality(const std::vector<BallotType> &ballots, const Outcome &outcome) = 0;

private:
	void OnNumSeatsChange();
	void OnNumSeatsPerWinnerChange();
	bool _isOutcomeListDirty = true;

	std::vector<Outcome> *_outcomeList;
};

// If I wasn't working in Visual Studios, I would just include all of this code in the cpp file 
// (and include the cpp file in this header), but because VS loves to make it harder to use templates, 
// the code is here instead:

template<typename BallotType, typename QualityValue>
OptimalMethod<BallotType, QualityValue>::OptimalMethod(unsigned seats, bool oneSeatPerWinner) : MultiWinnerMethod<BallotType>(seats, oneSeatPerWinner) {}

template<typename BallotType, typename QualityValue>
OptimalMethod<BallotType, QualityValue>::OptimalMethod(std::vector<Outcome> &possibleOutcomes) : MultiWinnerMethod<BallotType>(0) // arguement here is irrelevent because it will be changed later
{
	SetPossibleOutcomes(possibleOutcomes);
}

template<typename BallotType, typename QualityValue>
std::vector<Outcome> OptimalMethod<BallotType, QualityValue>::GeneratePosssibleOutcomes(int numSeats, bool oneSeatPerWinner)
{
	return std::vector<Outcome>(); // todo
}

template<typename BallotType, typename QualityValue>
void OptimalMethod<BallotType, QualityValue>::SetPosssibleOutcomes(int numSeats, bool oneSeatPerWinner)
{
	_outcomeList = &GeneratePosssibleOutcomes(numSeats, oneSeatPerWinner);
}

template<typename BallotType, typename QualityValue>
void OptimalMethod<BallotType, QualityValue>::SetPossibleOutcomes(std::vector<Outcome> &possibleOutcomes)
{
	int maxNumSeats = 0;
	bool oneSeatPerWinner = true;

	for (Outcome &outcome : possibleOutcomes)
	{
		int currNumSeats = outcome.GetNumSeats();
		if (maxNumSeats < currNumSeats)
			maxNumSeats = currNumSeats;

		std::vector<unsigned> seats = outcome.GetSeats();

		for (int seatNum : seats)
			if (seatNum > 1)
				oneSeatPerWinner = false;
	}

	SetNumSeats(maxNumSeats);
	SetOneSeatPerWinner(oneSeatPerWinner);

	delete _outcomeList;
	_outcomeList = &possibleOutcomes;
	_isOutcomeListDirty = false;
}

template<typename BallotType, typename QualityValue>
std::vector<Outcome> &OptimalMethod<BallotType, QualityValue>::GetPossibleOutcomes()
{
	return *_outcomeList;
}

template<typename BallotType, typename QualityValue>
Outcome &OptimalMethod<BallotType, QualityValue>::CalculateResults(std::vector<BallotType> &ballots, unsigned seats, bool oneSeatPerWinner)
{
	if (_isOutcomeListDirty)
		SetPosssibleOutcomes(GetNumSeats(), IsOneSeatPerWinner());

	return CalculateResults(ballots, *_outcomeList);
}

template<typename BallotType, typename QualityValue>
Outcome &OptimalMethod<BallotType, QualityValue>::CalculateResults(std::vector<BallotType> &ballots, const std::vector<Outcome> &possibleOutcomes)
{
	QualityValue maxQuality = CalculateOutcomeQuality(ballots, possibleOutcomes[0]);
	int best = 0;
	bool tie = false;
	for (int i = 1; i < possibleOutcomes.size(); ++i)
	{
		QualityValue currQuality = CalculateOutcomeQuality(ballots, possibleOutcomes[i]);
		if (maxQuality <= currQuality)
		{
			maxQuality = currQuality;
			tie = maxQuality == currQuality;
		}
	}

	Outcome results = Outcome(possibleOutcomes[best]);
	results.SetTieFlag(tie);
	return results;
}

template<typename BallotType, typename QualityValue>
void OptimalMethod<BallotType, QualityValue>::OnNumSeatsChange()
{
	_isOutcomeListDirty = true;
}

template<typename BallotType, typename QualityValue>
void OptimalMethod<BallotType, QualityValue>::OnNumSeatsPerWinnerChange()
{
	_isOutcomeListDirty = true;
}