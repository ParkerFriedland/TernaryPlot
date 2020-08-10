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
void Sort3(T *_3nums)
{
	if (_3nums[1] < _3nums[0])
		std::swap(_3nums[0], _3nums[1]);

	if (_3nums[2] < _3nums[1])
	{
		std::swap(_3nums[1], _3nums[2]);
		if (_3nums[1] < _3nums[0])
			std::swap(_3nums[1], _3nums[0]);
	}
}

template <typename T>
void Sort4(T* _4nums)
{
	if (_4nums[1] < _4nums[0])
		std::swap(_4nums[0], _4nums[1]);

	if (_4nums[3] < _4nums[2])
		std::swap(_4nums[2], _4nums[3]);

	if (_4nums[2] < _4nums[0])
		std::swap(_4nums[0], _4nums[2]);

	if(_4nums[3] < _4nums[1])
		std::swap(_4nums[1], _4nums[3]);

	if(_4nums[2] < _4nums[1])
		std::swap(_4nums[1], _4nums[2]);
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


double NormalizedDigamma(double x, unsigned accuracyTerms);