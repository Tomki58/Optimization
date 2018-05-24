// FastestDescent.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <Math.h>
#include <string>
#include <sstream>
#include <conio.h>

using namespace std;

typedef vector<double> DataList;

void InitData();
void GradSearch(DataList &p, double sigma, double epsilon);
void QMin(DataList &de_dxi, DataList &p, double epsilon, double sigma);
void getDfDx(DataList &de_dxi, DataList &p);
string CreateResultString(DataList &pMin, double yMin);
double getFunc(DataList &p);
string stringify(double x);

DataList p1;
DataList p2;
DataList pMin;
DataList de_dxi;

double yMin;
double err;
double z0;
double h;
int N;

int j;

int main()
{
	N = 2;

	InitData();

	DataList p;
	p.push_back(0.99);
	p.push_back(1.01);
	double sigma = 0.0000000001;
	double epsilon = 0.0000000001;

	GradSearch(p, sigma, epsilon);

	return 0;
}

void GradSearch(DataList &p, double sigma, double epsilon)
{
	int max = 60;
	h = 1;
	err = 1;
	int count = 0;

	while (count < max && (h>sigma || err > epsilon))
	{
		getDfDx(de_dxi, p);
		QMin(de_dxi, p, epsilon, sigma);

		for (int i = 0; i<N; i++)
			p.at(i) = pMin.at(i);

		z0 = yMin;
		count = count + j + 1;

		cout << CreateResultString(pMin, yMin) << endl;
	}
	cout << endl << "Min(F): " << "-4*x + x*x - y - x*y + y*y" << endl;
	cout << CreateResultString(pMin, yMin) << endl;
}

void QMin(DataList &de_dxi, DataList &p, double epsilon, double sigma)
{
	int cond = 0;
	int jmax = 60;

	z0 = getFunc(p);

	for (int i = 0; i<N; i++)
		p1.at(i) = p.at(i) + h * de_dxi.at(i);

	double y1 = getFunc(p1);

	for (int i = 0; i<N; i++)
		p2.at(i) = p.at(i) + 2 * h * de_dxi.at(i);

	double y2 = getFunc(p2);

	j = 0;

	while (j<jmax && cond == 0)
	{
		if (z0 <= y1)
		{
			for (int i = 0; i<N; i++)
				p2.at(i) = p1.at(i);

			y2 = y1;
			h = h / 2;

			for (int i = 0; i<N; i++)
				p1.at(i) = p.at(i) + h * de_dxi.at(i);

			y1 = getFunc(p1);
		}
		else if (y2 < y1)
		{
			for (int i = 0; i<N; i++)
				p1.at(i) = p2.at(i);

			y1 = y2;

			h = h * 2;

			for (int i = 0; i<N; i++)
				p2.at(i) = p.at(i) + 2 * h * de_dxi.at(i);

			y2 = getFunc(p2);
		}
		else
		{
			cond = -1;
		}

		j = j + 1;
		if (h < sigma)
			cond = 1;
	}

	double hMin = (h / 2)* (4 * y1 - 3 * z0 - y2) / (2 * y1 - z0 - y2);

	for (int i = 0; i< N; i++)
	{
		pMin.at(i) = p.at(i) + hMin * de_dxi.at(i);
	}

	yMin = getFunc(pMin);

	double h0 = fabs(hMin);
	double h1 = fabs(hMin - h);
	double h2 = fabs(hMin - 2 * h);

	if (h0 < h)
		h = h0;
	if (h1 < h)
		h = h1;
	if (h2 < h)
		h = h2;
	if (h == 0)
		h = hMin;
	if (h < sigma)
		cond = 1;
	double e0 = fabs(z0 - yMin);
	double e1 = fabs(y1 - yMin);
	double e2 = fabs(y2 - yMin);

	if (e0 != 0 && e0 < err)
		err = e0;
	if (e1 != 0 && e1 < err)
		err = e1;
	if (e2 != 0 && e2 < err)
		err = e2;
	if (e0 == 0 && e1 == 0 && e2 == 0)
		err = 0;
	if (err < epsilon)
		cond = 2;
}

double getFunc(DataList &p)
{
	double x = p.at(0);
	double y = p.at(1);

	double result = -4 * x + x*x - y - x * y + y * y;

	return result;
}

void getDfDx(DataList & de_dxi, DataList &p)
{
	double x = p.at(0);
	double y = p.at(1);


	double dfDx = -4 + 2 * x - y;
	double dfDy = -1 - x + 2 * y;

	double norm = sqrt(dfDx*dfDx + dfDy*dfDy);

	dfDx = -dfDx / norm;
	dfDy = -dfDy / norm;

	de_dxi.at(0) = dfDx;
	de_dxi.at(1) = dfDy;
}

void InitData()
{
	for (int i = 0; i<N; i++)
	{
		p1.push_back(0);

		p2.push_back(0);

		pMin.push_back(0);

		de_dxi.push_back(0);
	}
}

string stringify(double x)
{
	ostringstream o;
	if (!(o << x))
		return 0;
	return o.str();
}

string CreateResultString(DataList &pMin, double yMin)
{
	string resultStr = "f[";

	for (int i = 0; i<N; i++)
	{
		if (i != 0)
			resultStr += ",";
		resultStr += stringify(pMin.at(i));
	}

	resultStr += "] = " + stringify(yMin);

	return resultStr;
}

