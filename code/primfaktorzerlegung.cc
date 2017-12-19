#include <vector>
#include <iostream>
#include <sstream>

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

int main(  )
{
	//std::cout << primfaktorzerlegung(14) << std::endl;
	/*for (size_t i = 3; i < 0xFFFFFFFFFFFFFFFF; ++i)
	{
		std::cout << primfaktorzerlegung(i) << std::endl;
	}*/

	system("pause");

    return 0;
}

