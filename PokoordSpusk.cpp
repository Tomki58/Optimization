// PokoordSpusk.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<math.h>

//максимально возможное число итераций
#define NUMBER_OF_ITERATIONS (1000)

//eps для критерия останова
#define EPS (1e-5)

//критерий останова
#define OSTANOV (2)

using namespace std;

vector<double> goldensectionoptimize(double(*f)(vector<double>), vector<double> x, int p, double a, double b, int n);
double f(vector<double> x);
vector<double> CoordinateDescent(double(*f)(vector<double>), int N, vector<double> x0);

double f(vector<double> x)
{
	//int l=x.size();
	return (x[0] - 1)*(x[0] - 1) + (x[1] - 1)*(x[1] - 1) - x[0] * x[1];
}


vector<double> CoordinateDescent(double(*f)(vector<double>), int N, vector<double> x0, int&Iterations)
//minimizes N-dimensional function f; x0 - start point
{
	vector <double> tmp, cur_x = x0, old;
	double s;
	int i, j;


	for (Iterations = 0; Iterations<NUMBER_OF_ITERATIONS; Iterations++)
	{
		old = cur_x;
		for (i = 0; i<N; i++)
		{
			//ищем минимум вдоль i-й координаты
			cur_x = goldensectionoptimize(f, cur_x, i, -10, 10, 100);
		}

		//выбор критерия останова
		if (OSTANOV == 1)
		{
			//условие останова 1
			s = 0;
			for (j = 0; j<old.size(); j++)
				s += (old[j] - cur_x[j])*(old[j] - cur_x[j]);
			s = sqrt(s);
			if (s<EPS)
				return cur_x;
		}

		if (OSTANOV == 2)
		{
			//условие останова 2
			s = fabs(f(cur_x) - f(old));
			if (s<EPS)
				return	cur_x;
		}
	}

	return cur_x;
}

int main()
{
	vector<double> x;
	x.push_back(10);
	x.push_back(10);
	int i, Iteration;
	vector<double> ans = CoordinateDescent(&f, 2, x, Iteration);
	cout << "Value: " << f(ans) << endl;
	cout << "Point: ";
	for (i = 0; i<ans.size(); i++)
		cout << ans[i] << ' ';
	cout << endl << "Number of iterations:" << Iteration << endl;
	return 0;

}

vector<double> goldensectionoptimize(double(*f) (vector<double>), vector<double> x, int p, double a, double b, int n)
{
	vector<double> tmp = x;
	int i;
	double s1;
	double s2;
	double u1;
	double u2;
	double fu1;
	double fu2;

	s1 = (3 - sqrt(double(5))) / 2;
	s2 = (sqrt(double(5)) - 1) / 2;
	u1 = a + s1*(b - a);
	u2 = a + s2*(b - a);
	tmp[p] = u1;
	i = tmp.size();
	fu1 = (*f)(tmp);
	tmp[p] = u2;
	fu2 = (*f)(tmp);

	for (i = 1; i <= n; i++)
	{
		if (fu1 <= fu2)
		{
			b = u2;
			u2 = u1;
			fu2 = fu1;
			u1 = a + s1*(b - a);
			tmp[p] = u1;
			fu1 = (*f)(tmp);
		}
		else
		{
			a = u1;
			u1 = u2;
			fu1 = fu2;
			u2 = a + s2*(b - a);
			tmp[p] = u2;
			fu2 = (*f)(tmp);
		}
	}
	tmp[p] = u1;
	fu1 = (*f)(tmp);
	tmp[p] = u2;
	fu2 = (*f)(tmp);

	if (fu1<fu2)
		tmp[p] = u1;
	else
		tmp[p] = u2;

	return tmp;
}

