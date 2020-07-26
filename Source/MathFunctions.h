#include <vector>

template <typename T>
T Min(T x, T y) 
{
	return (x < y ? x : y);
}

template <typename T>
T Min(std::vector<T> &numbers) 
{
	T min = numbers[0];
	for (int i = 1; i < numbers.size(); ++i)
		if (numbers[i] < min)
			min = numbers[i];
	return min;
}

template <typename T>
T Max(T x, T y) 
{
	return (x > y ? x : y);
}

template <typename T>
T Max(std::vector<T> &numbers) 
{
	T max = numbers[0];
	for (int i = 1; i < numbers.size(); ++i)
		if (numbers[i] > max)
			max = numbers[i];
	return max;
}

template <typename T>
T Square(T number)
{
	return number * number;
}

template <typename T>
T IntPow(T number, int pow)
{
	T product = 1;
	if (pow >= 0)
		for (; pow > 0; --pow)
			product *= number;
	T product = 1;
	else
		for (; pow < 0; ++pow)
			product /= number;
	return product;
}


double NormalizedDigamma(double x, int accuracyTerms);