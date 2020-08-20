#include <fstream>
#include "Barycentric.h"
#include "ApportionmentAlgorithems.h"
#include "TemperaryMethods.h"
#include "MathFunctions.h"
#include "Random.h"
#include <cmath>

#include "VotingMethod.h"
#include "RRV.h"
#include "ReweightedSTAR.h"
#include "SingleDistributedVote.h"
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
	ofstream img ("Output\\SPSV1000.ppm");
	img << "P3" << endl;
	img << width << " " << height << endl;
	img << "255" << endl;
	
	double P[2];
	double Q[3];
	double A[2] = {0, 0};
	double B[2] = {1024, 0};
	double C[2] = {512, 887};
	int numSeats = 1000;
	BarycentricConverter *bary = new BarycentricConverter(A, B, C);

	std::vector<double> vote1a = { 1.0, 0.0, 0.0 }; //{ 1.0, 0.0, 0.3 };
	std::vector<double> vote1b = { 1.0, 0.0, 1.0 }; //{ 1.0, 0.0, 0.3 };
	std::vector<double> vote2a = { 0.0, 1.0, 0.0 }; //{ 0.7, 1.0, 0.0 };
	std::vector<double> vote2b = { 1.0, 1.0, 0.0 }; //{ 0.7, 1.0, 0.0 };
	std::vector<double> vote3a = { 0.0, 0.0, 1.0 }; //{ 0.0, 0.5, 1.0 };
	std::vector<double> vote3b = { 0.0, 1.0, 1.0 }; //{ 0.0, 0.5, 1.0 };

	Random rand = Random();

	std::vector<ScoreBallot> ballots = std::vector<ScoreBallot>();
	ballots.reserve(6);
	ballots.push_back(ScoreBallot(vote1a, 0.0, rand));
	ballots.push_back(ScoreBallot(vote1b, 0.0, rand));
	ballots.push_back(ScoreBallot(vote2a, 0.0, rand));
	ballots.push_back(ScoreBallot(vote2b, 0.0, rand));
	ballots.push_back(ScoreBallot(vote3a, 0.0, rand));
	ballots.push_back(ScoreBallot(vote3b, 0.0, rand));

	VotingMethod<ScoreBallot>* method = new ReweightedRange(1.0);
	reinterpret_cast<MultiWinnerMethod<ScoreBallot>*>(method)->SetNumSeats(numSeats);

	Domain domain = Domain(3);
	Outcome out = Outcome(3);

	double maxDiff = 0;
	double minDiff = 0;

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
				//double approveC = 0.7 * Q[0];
				//double approveM = 0.3 * Q[1];
				//double approveY = 0.5 * Q[2];

				//double approveCM = 0.7 * Q[1];
				//double approveCY = 0.3 * Q[0];
				//double approveMY = 0.5 * Q[2];

				//double idealC = approveC
				//	+ (approveCM * ((approveC + approveCY) / (approveC + approveCY + approveM + approveMY))) // split CM into C and M
				//	+ (approveCY * ((approveC + approveCM) / (approveC + approveCM + approveY + approveMY))); // split CY into C and Y

				//double idealM = approveM
				//	+ (approveCM * ((approveM + approveMY) / (approveM + approveMY + approveC + approveCY))) // split CM into C and M
				//	+ (approveMY * ((approveM + approveCM) / (approveM + approveCM + approveY + approveCY))); // split MY into M and Y

				//double idealY = approveY
				//	+ (approveCY * ((approveY + approveMY) / (approveY + approveMY + approveC + approveCM))) // split CY into C and Y
				//	+ (approveMY * ((approveY + approveCY) / (approveY + approveCY + approveM + approveCM))); // split MY into M and Y

				//double idealQuality =
				//	approveC * std::log(idealC) +
				//	approveM * std::log(idealM) +
				//	approveY * std::log(idealY) +
				//	approveCM * std::log(idealC + idealM) +
				//	approveCY * std::log(idealC + idealY) +
				//	approveMY * std::log(idealM + idealY);

				/*double idealQuality =
					std::pow(idealC, approveC) *
					std::pow(idealM, approveM) *
					std::pow(idealY, approveY) *
					std::pow(idealC + idealM, approveCM) *
					std::pow(idealC + idealY, approveCY) *
					std::pow(idealM + idealY, approveMY);*/

				/*double max = 1.0 -
					 ((1.0 - idealC)
					* (1.0 - idealM)
					* (1.0 - idealY));

				r = doubleToColor(idealC / max);
				g = doubleToColor(idealM / max);
				b = doubleToColor(idealY / max);*/

				/*double max = 1.0 -
						   ((1.0 - Q[0])
						  * (1.0 - Q[1])
						  * (1.0 - Q[2]));

				r = doubleToColor(Q[0] / max);
				g = doubleToColor(Q[1] / max);
				b = doubleToColor(Q[2] / max);*/

				/*int seats[3] = { 0 };
				TempSTV(seats, numSeats, Q);*/

				/*r = seatsToColor(seats[0], numSeats);
				g = seatsToColor(seats[1], numSeats);
				b = seatsToColor(seats[2], numSeats);*/

				ballots[0].Reset(Q[0] * 0.7);
				ballots[1].Reset(Q[0] * 0.3);
				ballots[2].Reset(Q[1] * 0.3);
				ballots[3].Reset(Q[1] * 0.7);
				ballots[4].Reset(Q[2] * 0.5);
				ballots[5].Reset(Q[2] * 0.5);

				domain.IncludeAll();

				/*if (x == 1)
					bool debug = true;

				printf("\n(%d, %d)\n", x, y);*/

				method->CalculateResults(ballots, domain, out);

				unsigned C = out.GetNumSeats(0);
				unsigned M = out.GetNumSeats(1);
				unsigned Y = out.GetNumSeats(2);

				double max = static_cast<double>(numSeats) * (1.0 -
							((1.0 - (static_cast<double>(C) / static_cast<double>(numSeats)))
						   * (1.0 - (static_cast<double>(M) / static_cast<double>(numSeats)))
						   * (1.0 - (static_cast<double>(Y) / static_cast<double>(numSeats)))));
				r = seatsToColor(C, max);
				g = seatsToColor(M, max);
				b = seatsToColor(Y, max);

				/*double actualC = static_cast<double>(out.GetNumSeats(0)) / static_cast<double>(numSeats);
				double actualM = static_cast<double>(out.GetNumSeats(1)) / static_cast<double>(numSeats);
				double actualY = static_cast<double>(out.GetNumSeats(2)) / static_cast<double>(numSeats);*/

				/*double diffC = (static_cast<double>(out.GetNumSeats(0)) / static_cast<double>(numSeats) - idealC) / 2.0 + 0.5;
				double diffM = (static_cast<double>(out.GetNumSeats(1)) / static_cast<double>(numSeats) - idealM) / 2.0 + 0.5;
				double diffY = (static_cast<double>(out.GetNumSeats(2)) / static_cast<double>(numSeats) - idealY) / 2.0 + 0.5;*/

				/*double actualQuality = std::exp(
					approveC * std::log(actualC) +
					approveM * std::log(actualM) +
					approveY * std::log(actualY) +
					approveCM * std::log(actualC + actualM) +
					approveCY * std::log(actualC + actualY) +
					approveMY * std::log(actualM + actualY));*/

				/*double actualQuality = 
					approveC  * std::log(actualC) +
					approveM  * std::log(actualM) +
					approveY  * std::log(actualY) +
					approveCM * std::log(actualC  + actualM) +
					approveCY * std::log(actualC  + actualY) +
					approveMY * std::log(actualM  + actualY);*/

				/*double actualQuality =
					std::pow(actualC, approveC) *
					std::pow(actualM, approveM) *
					std::pow(actualY, approveY) *
					std::pow(actualC + actualM, approveCM) *
					std::pow(actualC + actualY, approveCY) *
					std::pow(actualM + actualY, approveMY);*/

				//double qualityDiff = actualQuality - idealQuality;

				/*if (qualityDiff < minDiff)
					minDiff = qualityDiff;
				if (qualityDiff > maxDiff)
					maxDiff = qualityDiff;*/
				// qualityDiff *= 100.0;

				/*if (std::isnan(qualityDiff) || qualityDiff > 0.0)
				{
					r = 255;
					g = 0;
					b = 0;
				}
				else
				{
					int magnifiedDiff = static_cast<int>(std::pow(1000000, qualityDiff) * 255.0);
					if (magnifiedDiff < 0)
					{
						r = 0;
						g = 255;
						b = 0;
					}
					else
					{
						r = static_cast<int>(255 - magnifiedDiff);
						g = static_cast<int>(magnifiedDiff);
						b = 0;
					}
				}*/

				/*double max = 1.0 -
					 ((1.0 - diffC)
					* (1.0 - diffM)
					* (1.0 - diffY));*/

				//r = doubleToColor(diffC); // / max);
				//g = doubleToColor(diffM); // / max);
				//b = doubleToColor(diffY); // / max);

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