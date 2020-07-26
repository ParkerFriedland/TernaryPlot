#include "OrderingMethod.h"

class SPAV : public OrderingMethod
{
public:
	SPAV(double delata = 1, bool oneSeatPerWinner = false);
	int CalculateNextWinner();
};