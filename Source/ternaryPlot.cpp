#include <fstream>
#include "Barycentric.h"
#include "ApportionmentAlgorithems.h"
#include "TemperaryMethods.h"
#include "MathFunctions.h"

using namespace std;

int doubleToColor(double x);
int seatsToColor(int seats, int numSeats);

const int width = 1024 /*255*/, height = 887 /*255*/;

int main()
{
	ofstream img ("ternaryPlot.ppm");
	img << "P3" << endl;
	img << width << " " << height << endl;
	img << "255" << endl;
	
	double P[2];
	double Q[3];
	double A[2] = {0, 0};
	double B[2] = {1024, 0};
	double C[2] = {512, 887};
	int numSeats = 2;
	BarycentricConverter *bary = new BarycentricConverter(A, B, C);

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
				int seats[3] = { 0 };
				TempPAV(seats, Q);
				r = seatsToColor(seats[0], numSeats);
				g = seatsToColor(seats[1], numSeats);
				b = seatsToColor(seats[2], numSeats);

				/*int winner = TempDistributed(Q);
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
		printf("%f%%\n", (100.0 * (y+1)) / height);
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
	return 255 - (int)(sqrt(x) * 255.0); // Doing this makes the colors look more neon-ish and less boring
}

int seatsToColor(int seats, int numSeats)
{
	return doubleToColor(((double)seats) / numSeats);
}