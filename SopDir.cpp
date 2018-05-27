// SopDir.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <vector>

#define EPS (1e-1)
#define Sigma (0.2)
#define N (1e3)

using namespace std;

double f(double x0, double x1)
{
	return 4 * pow((x0 - 5), 2) + pow((x1 - 6), 2);
}

double Optim(double x0, double x1, vector<double> dir)
{
	int k = 0;
	double a = -100; double b = 70;
	do
	{
		double y = (a + b - Sigma) / 2;
		double z = (a + b + Sigma) / 2;
		if (f(x0 + y*dir.at(0), x1 + y*dir.at(1)) <= f(x0 + z*dir.at(0), x1 + z*dir.at(1)))
			b = z;
		else
			a = y;
		k++;
	} while (abs(b - a) > EPS && k < N);
	return (a + b) / 2;
}

void Directions()
{
	double x0 = 8; double x1 = 9;
	int i = 0; int k = 0; int n = 2;
	double y0 = NULL, y1 = NULL;
	vector<double> p1 = { 1 , 0 };
	vector<double> p2 = { 0, 1 };
	vector<double> arr[2] = { p1, p2 };

	while (i <= n)
	{
		if (y0 == NULL && y1 == NULL)
		{
			y0 = x0; y1 = x1;
		}
		if (!(i % 2))
		{
			y1 = y1 + Optim(y0, y1, arr[1]);
		}
		else
		{
			y0 = y0 + Optim(y0, y1, arr[0]);
		}
		i++;
	}
	cout << y0 << y1;
}

int main()
{
	Directions();
    return 0;
}

