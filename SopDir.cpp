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

int Optim(double x0, double x1, vector<double> dir)
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

int Directions()
{
	vector<vector<double>> x = { {8,9} };
	int i = 0; int k = 0; int n = 2;			// i = 0, k = 0
	vector<double> p1 = { 1 , 0 };				// первое направление поиска
	vector<double> p2 = { 0, 1 };				// второе направление поиска
	vector<double> arr[2] = { p1, p2 };
	vector<double> p0 = arr[n-1];				// p0 = pn

	vector<vector<double>> y = { {8, 9} };
	y.push_back({ 0,0 });
	y.push_back({ 0,0 });
	y.push_back({ 0,0 });

	while (k < N)
	{
		while (i <= n)
		{

			y[i + 1][0] = y[i][0] + Optim(y[i][0], y[i][1], arr[0]);
			y[i + 1][1] = y[i][1] + Optim(y[i][0], y[i][1], arr[1]);
			cout << "Y[0] = " << y[0][0] << y[0][1] << endl;
			cout << "Y = " << y[i][0] << y[i][1] << endl;
			cout << "Y[n] = " << y[n][0] << y[n][1] << endl;
			cout << "i = " << i << endl << endl;
			if (i == n - 1 && y[n] == y[0])
			{
				cout << "X = {" << y[n][0] << " ; " << y[n][1] << " } " << endl;
				return 0;
			}
			if (i == n && y[n + 1] == y[1])
			{
				cout << "X = {" << y[n + 1][0] << " ; " << y[n + 1][1] << " } " << endl;
				return 0;
			}
			i++;
		}
		x.push_back(y[n + 1]);
		if (sqrt(pow(x[k + 1][0] - x[k][0], 2) + pow(x[k + 1][1] - x[k][1], 2)) < EPS)
		{
			cout << "X = {" << x[k + 1][0] << " ; " << x[k + 1][1] << " } " << endl;
			return 0;
		}
		else
		{
			arr[0] = arr[1];
			arr[1] = { y[n + 1][0] - y[1][0], y[n + 1][1] - y[1][1] };
			y[0] = x[k + 1];
			k++; i = 0;
		}
	}
}

int main()
{
	Directions();
	return 0;
}
