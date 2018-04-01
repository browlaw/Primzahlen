#include <vector>
#include <iostream>
#include <sstream>
#include <thread>
#include <map>
#include <fstream>
#include <math.h>

const size_t g_maxVal = 0xFFFFFF;
bool g_should_exit;

size_t teile(size_t zahl)
{
	size_t teiler = 2;
	size_t x = sqrt(zahl);
	while (zahl % teiler != 0)
	{
		if (teiler >= x)
		{
			return zahl;
		}
		else
		{
			++teiler;
		}
	}

	return teiler;
}

std::string primfaktorzerlegung(size_t zahl)
{
	std::stringstream ss;
	size_t teiler = 0;

	ss << zahl << " = ";

	while (zahl != 1)
	{
		teiler = teile(zahl);
		ss << teiler;
		zahl = zahl / teiler;
		if (zahl != 1)
			ss << "*";
	}

	return ss.str();
}

void generate_prime_factors(unsigned threadnum, unsigned threadc, std::map<size_t, std::string>* factors)
{
	if (threadnum == 0)
		threadnum += threadc;
	for (size_t i = threadnum; i < g_maxVal && !g_should_exit; i += threadc)
	{
		factors->insert(std::pair<size_t, std::string>(i, primfaktorzerlegung(i)));
	}
}

void multithreaded_factorization(std::map<size_t, std::string>* factors)
{
	const size_t threadc = std::thread::hardware_concurrency();
	std::thread* threads = new std::thread[threadc];
	for (unsigned i = 0; i < threadc; ++i)
	{
		threads[i] = std::thread(generate_prime_factors, i, threadc, factors);
	}

	for (unsigned i = 0; i < threadc; ++i)
	{
		threads[i].join();
	}

	delete[] threads;
}

void print_factors(std::ostream& os, std::map<size_t, std::string>* factors)
{
	for (std::map<size_t, std::string>::iterator it = factors->begin(); it != factors->end(); ++it)
	{
		os << it->second << "\n";
	}
}

int main2()
{
	g_should_exit = false;
	std::map<size_t, std::string> factors;
	multithreaded_factorization(&factors);
	print_factors(std::cout, &factors);

	return 0;
}

int main(int argc, char **argv)
{
	size_t num;

	if (argc == 1)
	{
		main2();
	}
	else if (argc == 2)
	{
		size_t num = atoll(argv[1]);
		std::cout << primfaktorzerlegung(num) << std::endl;
	}
	else
	{
		std::cout << "Usage: ./dick <num>" << std::endl;
		return 1;
	}

	return 0;
}
