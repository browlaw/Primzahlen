#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double read_input(void)
{
	char buf[256];
	double n = -1;

	printf("Enter n: ");
	scanf("%lf", &n);
	return n;
}

double fermat_1(double num)
{
	double f;
	if (num == 0)
		f = 3;
	else
		f = pow(fermat_1(num - 1) - 1, 2) + 1;
	printf("F_%.0lf = %.0lf\n", num, f);
	return f;
}

int main(int argc, char *argv[])
{
	double n = read_input();
	fermat_1(n);

	return 0;
}
