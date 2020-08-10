#include <fstream>
#include "Barycentric.h"
#include "ApportionmentAlgorithems.h"
#include "TemperaryMethods.h"
#include "MathFunctions.h"
#include "Random.h"

#include "VotingMethod.h"
#include "RRV.h"
#include "ReweightedSTAR.h"
#include "SequentialMonroe.h"
#include "SequentiallySubtractedScore.h"
#include "SequentiallyScaledScore.h"
#include "ScoreBallot.h"
#include "Outcome.h"

using namespace std;

int doubleToColor(double x);
int seatsToColor(int seats, double max);

const int width = 1024 /*255*/, height = 887 /*255*/;

int main()
{
	ofstream img ("RRV4_deviation.ppm");
	img << "P3" << endl;
	img << width << " " << height << endl;
	img << "255" << endl;
	
	double P[2];
	double Q[3];
	double A[2] = {0, 0};
	double B[2] = {1024, 0};
	double C[2] = {512, 887};
	int numSeats = 4;
	BarycentricConverter *bary = new BarycentricConverter(A, B, C);

	std::vector<double> vote1 = { 1.0, 0.0, 0.3 };
	std::vector<double> vote2 = { 0.7, 1.0, 0.0 };
	std::vector<double> vote3 = { 0.0, 0.5, 1.0 };

	Random rand = Random();

	std::vector<ScoreBallot> ballots = std::vector<ScoreBallot>();
	ballots.reserve(3);
	ballots.push_back(ScoreBallot(vote1, 0.0, rand));
	ballots.push_back(ScoreBallot(vote2, 0.0, rand));
	ballots.push_back(ScoreBallot(vote3, 0.0, rand));

	VotingMethod<ScoreBallot>* method = new ReweightedRange(1);
	reinterpret_cast<MultiWinnerMethod<ScoreBallot>*>(method)->SetNumSeats(numSeats);

	Domain domain = Domain(3);
	Outcome out = Outcome(3);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			P[0] = (double)x;
			P[1] = (double)y;
			bary->ToBarycentric(P, Q);

			int r = 0, g = 0, b = 0;
			if (Q[0] >= 0 && Q[1] >= 0 && Q[2] >= 0)
			{
				double approveC = Q[0];
				double approveM = 0.3 * Q[1];
				double approveY = 0.5 * Q[2];

				double approveCM = 0.7 * Q[1];
				double approveCY = 0.3 * Q[0];
				double approveMY = 0.5 * Q[2];

				double idealC = approveC
					+ (approveCM * ((approveC + approveCY) / (approveC + approveCY + approveM + approveMY))) // split CM into C and M
					+ (approveCY * ((approveC + approveCM) / (approveC + approveCM + approveY + approveMY))); // split CY into C and Y

				double idealM = approveM
					+ (approveCM * ((approveM + approveMY) / (approveM + approveMY + approveC + approveCY))) // split CM into C and M
					+ (approveMY * ((approveM + approveCM) / (approveM + approveCM + approveY + approveCY))); // split CY into C and Y

				double idealY = approveY
					+ (approveCY * ((approveY + approveMY) / (approveY + approveMY + approveC + approveCM))) // split CM into C and M
					+ (approveMY * ((approveY + approveCY) / (approveY + approveCY + approveM + approveCM))); // split CY into C and Y

				//double max = 1.0 -
				//	 ((1.0 - idealC)
				//	* (1.0 - idealM)
				//	* (1.0 - idealY));

				//r = doubleToColor(idealC / max);
				//g = doubleToColor(idealM / max);
				//b = doubleToColor(idealY / max);

				/*double max = 1.0 -
						   ((1.0 - Q[0])
						  * (1.0 - Q[1])
						  * (1.0 - Q[2]));

				r = doubleToColor(Q[0] / max);
				g = doubleToColor(Q[1] / max);
				b = doubleToColor(Q[2] / max);*/

				/*int seats[3] = { 0 };
				TempSTV(seats, numSeats, Q);

				r = seatsToColor(seats[0], numSeats);
				g = seatsToColor(seats[1], numSeats);
				b = seatsToColor(seats[2], numSeats);*/

				ballots[0].Reset(Q[0]);
				ballots[1].Reset(Q[1]);
				ballots[2].Reset(Q[2]);

				domain.IncludeAll();

				method->CalculateResults(ballots, domain, out);

				/*double max = static_cast<double>(numSeats) * (1.0 -
							((1.0 - (static_cast<double>(out.GetNumSeats(0)) / static_cast<double>(numSeats)))
						   * (1.0 - (static_cast<double>(out.GetNumSeats(1)) / static_cast<double>(numSeats)))
						   * (1.0 - (static_cast<double>(out.GetNumSeats(2)) / static_cast<double>(numSeats)))));
				r = seatsToColor(out.GetNumSeats(0), max);
				g = seatsToColor(out.GetNumSeats(1), max);
				b = seatsToColor(out.GetNumSeats(2), max);*/

				double diffC = (static_cast<double>(out.GetNumSeats(0)) / static_cast<double>(numSeats) - idealC) / 2 + 0.5;
				double diffM = (static_cast<double>(out.GetNumSeats(1)) / static_cast<double>(numSeats) - idealC) / 2 + 0.5;
				double diffY = (static_cast<double>(out.GetNumSeats(2)) / static_cast<double>(numSeats) - idealC) / 2 + 0.5;

				/*double max = 1.0 -
					 ((1.0 - diffC)
					* (1.0 - diffM)
					* (1.0 - diffY));*/

				r = doubleToColor(diffC); // / max);
				g = doubleToColor(diffM); // / max);
				b = doubleToColor(diffY); // / max);

				out.ClearSeats();

				/*int winner = Temp_CB_Merged_With_SB_V2(Q);
				if (winner == 0)
				{
					r = 255;
					g = 0;
					b = 0;
				}
				if (winner == 1)
				{
					r = 0;
					g = 255;
					b = 0;
				}
				if (winner == 2)
				{
					r = 0;
					g = 0;
					b = 255;
				}*/

				/*r = doubleToColor(Q[0] + 0.7 * Q[1]);
				g = doubleToColor(Q[1] + 0.5 * Q[2]);
				b = doubleToColor(Q[2] + 0.3 * Q[0]);*/

				/*r = doubleToColor(Q[0]);
				g = doubleToColor(Q[1]);
				b = doubleToColor(Q[2]);*/
			}

			/*
			int seats[3] = { 0 };
			Hill(seats, numSeats, Q);
			int r = 0, g = 0, b = 0;
			if (Q[0] >= 0 && Q[1] >= 0 && Q[2] >= 0)
			{
				r = seatsToColor(seats[0], numSeats);
				g = seatsToColor(seats[1], numSeats);
				b = seatsToColor(seats[2], numSeats);
			}
			*/

			img << r << " " << g << " " << b << endl;
		}
		printf("%f%%\n", (100.0 * (++y)--) / height);
	}
	printf("done");

	//system("open picture.ppm");
	return 0;
}

int doubleToColor(double x)
{
	if (x <= 0)
		return 255;
	if (x >= 1)
		return 0;
	return (int)(255.0 * (1 - x) * (1 - x)); // Doing this makes the colors look more neon-ish and less boring
}

int seatsToColor(int seats, double max)
{
	return doubleToColor(((double)seats) / max);
}