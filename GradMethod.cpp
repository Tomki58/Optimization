// GradMethod.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

#define EPS (1e-5)
#define Lambda (1e-2)

using namespace std;

double f(double x0, double x1)
{
	return 10 * x0 * x0 + x1 * x1;
}

double gradx0(double x0, double x1)
{
	return 20 * x0;
}

double gradx1(double x0, double x1)
{
	return 2 * x1;
}

vector<double> Descent()
{
	vector<double> x;
	x.push_back(10);
	x.push_back(10);
	double F1 = f(x.at(0), x.at(1));
	double F2 = NULL;
	do
	{
		x.at(0) = x.at(0) - Lambda * gradx0(x.at(0), x.at(1));
		x.at(1) = x.at(1) - Lambda * gradx1(x.at(0), x.at(1));
		if (F2 == NULL)
		{
			F2 = f(x.at(0), x.at(1));
		}
		else
		{
			F1 = F2;
			F2 = f(x.at(0), x.at(1));
		}
	} while (abs(F2 - F1) > EPS);
	x.push_back(F2);
	return x;
}

int main()
{
	cout << "x0 = " << Descent().at(0) << "  " << "x1 = " << Descent().at(1) << "F(x) = " << Descent().at(2) << endl;
    return 0;
}

