#include "stdafx.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <thread>
#include <map>
#include <fstream>

const size_t g_maxVal = 0xFFFFFF;

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
	for (size_t i = threadnum; i < g_maxVal && !g_shouldExit; i += threadc)
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

int main()
{
	std::map<size_t, std::string> factors;
	multithreaded_factorization(&factors);
	std::ofstream os("testfile.txt", std::ios::trunc | std::ios::binary);
	if (os)
		print_factors(os, &factors);
	os.close();

	std::system("pause");

	return 0;
}
