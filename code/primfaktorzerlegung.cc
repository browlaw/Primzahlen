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

void generatePrimeFactors(unsigned threadnum, std::map<size_t, std::string>* factors)
{
	std::cout << threadnum << std::endl;
	for (size_t i = threadnum; i < 0xFFFFFFF; i += 8)
	{
		factors->insert(std::pair<size_t, std::string>(i, primfaktorzerlegung(i)));
	}
}

int main(  )
{
	std::map<size_t, std::string> factors;
	std::thread* threads = new std::thread[8];
	for (unsigned i = 0; i < 8; ++i)
	{
		threads[i] = std::thread(generatePrimeFactors, i, &factors);
	}

	for (unsigned i = 0; i < 8; ++i)
	{
		threads[i].join();
	}

	delete[] threads;

	system("pause");

    return 0;
}