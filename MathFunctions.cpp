
double NormalizedDigamma(double x, int accuracyTerms)
{
	double sum = 0.0;
	for (int i = 1; i <= accuracyTerms; ++i)
		sum += 1.0 / i - 1.0 / (i + x);
	return sum;
}