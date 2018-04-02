#include <vector>
#include <iostream>
#include <sstream>
#include <thread>
#include <map>
#include <fstream>
#include <math.h>
#include <algorithm>

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

std::vector<size_t> primfaktorzerlegung(size_t zahl)
{
	std::vector<size_t> faktoren;
	size_t teiler = 0;

	while (zahl != 1)
	{
		teiler = teile(zahl);
		faktoren.push_back(teiler);
		zahl = zahl / teiler;
		if (zahl != 1)
			faktoren.push_back(zahl);
	}

	return faktoren;
}

int main(int argc, char **argv)
{
	size_t num;

	if (argc == 1)
	{
		std::cout << "Usage: ./satzdeseuklid [<zahl0>...<zahln>]" << std::endl;
		return -1;
	}
	else
	{
		size_t produkt = 1;
		std::vector<size_t> faktoren;
		for (int i = 1; i < argc; ++i)
			faktoren.push_back(atoll(argv[i]));
		for (size_t faktor : faktoren)
			produkt *= faktor;
		++produkt;
		std::vector<size_t> neue_faktoren = primfaktorzerlegung(produkt);
		for (size_t faktor : neue_faktoren)
			if (std::find(faktoren.begin(), faktoren.end(), faktor) == faktoren.end())
				std::cout << faktor << " ";
		std::cout <<std::endl;
	}

	return 0;
}
