#include <cmath>

double* Add2D(double a[2], double b[2], double result[2])
{
	result[0] = a[0] + b[0];
	result[1] = a[1] + b[1];
	return result;
}

double* Sub2D(double a[2], double b[2], double result[2])
{
	result[0] = a[0] - b[0];
	result[1] = a[1] - b[1];
	return result;
}

double* Mid2D(double a[2], double b[2], double result[2])
{
	result[0] = a[0] / 2 + b[0] / 2;
	result[1] = a[1] / 2 + b[1] / 2;
	return result;
}

double* Scale2D(double a[2], double b, double result[2])
{
	result[0] = a[0] * b;
	result[1] = a[1] * b;
	return result;
}

double* Div2D(double a[2], double b, double result[2])
{
	result[0] = a[0] / b;
	result[1] = a[1] / b;
	return result;
}

double Dot2D(double a[2], double b[2])
{
	return a[0] * b[0] + a[1] * b[1];
}

double SqDist2D(double a[2])
{
	return Dot2D(a, a);
}

double Dist2D(double a[2])
{
	return sqrt(SqDist2D(a));
}

double* Normalize2D(double a[2], double result[2])
{
	return Div2D(a, Dist2D(a), result);
}

double* Rot90_2D(double a[2], double result[2])
{
	result[0] = -a[1];
	result[1] = a[0];
	return result;
}

double* GetNormal2D(double a[2], double result[2])
{
	Rot90_2D(a, result);
	Normalize2D(result, result);
	return result;
}
