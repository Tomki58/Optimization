// Gauss.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <deque>
#include <math.h>

using namespace std;

#define EPS (1e-5)
#define Sigma (0.2)
#define N (1e3)
#define eps (1)

double f(double x0, double x1)
{
	return 2 * pow(x0, 2) + x0*x1 + pow(x1, 2);
}

double dx0(double x0, double x1)
{
	return 4 * x0 + x1;
} 

double dx1(double x0, double x1)
{
	return x0 + 2 * x1;
}

double stepForGZMethod(double x0, double x1, int dim)
{
	// оптимизация функции f(x0 - dx0 * t, x1 - dx1 * t) в зависимости от оси оптимизации
	double a = 0; double b = 5;
	do
	{
		double y = (a + b - Sigma) / 2;
		double z = (a + b + Sigma) / 2;
		if (!dim)
		{
			if (f(x0 - y*dx0(x0, x1) * 1, x1) <= f(x0 - z*dx0(x0, x1), x1))
			{
				a = a; b = z;
			}
			else
			{
				a = y; b = b;
			}
		}
		else
		{
			if (f(x0, x1 - y*dx1(x0, x1) * 1) <= f(x0, x1 - z*dx1(x0, x1) * 1))
			{
				a = a; b = z;
			}
			else
			{
				a = y; b = b;
			}
		}
	}
	while (abs(b - a) > eps);
	return abs(a + b) / 2;
}


double GaussZeidel()
{
	double x0 = 0.5; double x1 = 1;
	int k = 0; double step0 = 0; double step1 = 0; int i = 0;
	do
	{
		cout << "Iterration #" << i << endl;
		cout << "x0 = " << x0 << "\nx1 = " << x1 << endl;
		if (!k)
		{
			step0 = stepForGZMethod(x0, x1, k);
			x0 = x0 - step0 * dx0(x0, x1);
		}
		else
		{
			step1 = stepForGZMethod(x0, x1, k);
			x1 = x1 - step1 * dx1(x0, x1);
		}
		if (!k)
		{
			k++;
		}
		else k = 0;
		i++;
		cout << endl;
	} while (sqrt(pow(dx0(x0, x1),2) + pow(dx1(x0, x1),2)) > EPS);
	cout << endl;
	cout << "f(x0, x1) = " << f(x0, x1) << endl;
	return 1;
}

int main()
{
	GaussZeidel();
    return 0;
}

