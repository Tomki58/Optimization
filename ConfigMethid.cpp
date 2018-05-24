// МетодКонфигураций.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream> //Метод Конфигураций или метод Хука - Дживса
#include <cmath>
#include <conio.h>

using namespace std;

double f(double  x1, double x2) {
	//return 4*(x1-5)*(x1-5)+(x2-6)*(x2-6);}
	return pow(2 * (pow(x1, 2))*(x2 + 3), 1.0 / 3);
}
//return 2*x1*x1+x1*x2+x2*x2; }

int main() {
	//double del_1=0.2,del_2=0.4,E=0.1,alfa=4,liamda=1.5;
	double E = 0.3, del_1 = 1, del_2 = 2, alfa = 2, liamda = 1;
	int i, j, s = 0, n = 2;
	int w1 = 0, w2 = 1;
	int k = 0, I[100];
	I[s] = 1;
	double d1[1][2] = { 1,0 };
	double d2[1][2] = { 0,1 };
	double X[1][2], Y[1][2], Xo[1][2], Xz[1][2];

	cout << "Elements:" << endl;
	for (int i = 0; i<1; i++)
		for (int j = 0; j<2; j++)
			cin >> X[i][j];

	for (i = 0; i<1; i++)
		for (j = 0; j<2; j++)
			Y[i][j] = X[i][j];

	Xo[w1][w1] = X[w1][w1];
	Xo[w1][w2] = X[w1][w2];      //cout <<Xo[w1][w1]<<" "<<Xo[w1][w2];  
								 //.2..............a...................         
T: if (I[s] == 1) {        //первый случай
	cout << " 2__a) I == 1 " << endl;
	if (f(Y[w1][w1] + del_1*d1[w1][w1], Y[w1][w2] + del_1*d1[w1][w2])<
		f(Y[w1][w1], Y[w1][w2])) {
		Y[w1][w1] = Y[w1][w1] + del_1*d1[w1][w1];  cout << Y[w1][w1] << " ";
		Y[w1][w2] = Y[w1][w2] + del_1*d1[w1][w2];  cout << Y[w1][w2] << endl;

		goto F;   //перейти к шагу - 3                                                     
	}
	//.................б...................    
	if (f(Y[w1][w1] - del_1*d1[w1][w1], Y[w1][w2] - del_1*d1[w1][w2])<
		f(Y[w1][w1], Y[w1][w2])) {
		cout << " 2__b) I == 1 " << endl;
		Y[w1][w1] = Y[w1][w1] - del_1*d1[w1][w1];  cout << Y[w1][w1] << " ";
		Y[w1][w2] = Y[w1][w2] - del_1*d1[w1][w2];  cout << Y[w1][w2] << endl;
		goto F;   //шаг - 3                              
	}
}
   if (I[s] == 2) {           //второй случай
	   if (f(Y[w1][w1] + del_2*d2[w1][w1], Y[w1][w2] + del_2*d2[w1][w2])<
		   f(Y[w1][w1], Y[w1][w2])) {
		   cout << " 2__a) I == 2 " << endl;
		   Y[w1][w1] = Y[w1][w1] + del_2*d2[w1][w1];  cout << Y[w1][w1] << " ";
		   Y[w1][w2] = Y[w1][w2] + del_2*d2[w1][w2];  cout << Y[w1][w2] << endl;

		   goto F;   //перейти к шагу - 3                                                     
	   }
	   //.................б...................    
	   if (f(Y[w1][w1] - del_2*d2[w1][w1], Y[w1][w2] - del_2*d2[w1][w2])<
		   f(Y[w1][w1], Y[w1][w2])) {
		   cout << " 2__b) I == 2 " << endl;
		   Y[w1][w1] = Y[w1][w1] - del_2*d2[w1][w1];  cout << Y[w1][w1] << " ";
		   Y[w1][w2] = Y[w1][w2] - del_2*d2[w1][w2];  cout << Y[w1][w2] << endl;

		   goto F;   //шаг - 3     
	   }
   }
   //.................в...................    
   if (f(Y[w1][w1] + del_1*d1[w1][w1], Y[w1][w2] + del_1*d1[w1][w2])>
	   f(Y[w1][w1], Y[w1][w2]) && f(Y[w1][w1] - del_1*d1[w1][w1], Y[w1][w2] - del_1*d1[w1][w2])>
	   f(Y[w1][w1], Y[w1][w2])) {
	   cout << " 2__v) " << endl;
   } //*/
	 //.3...............а.....................
F:    if (I[s]<n) {
   I[s] = I[s] + 1;     //cout <<"++"<<endl; 
   cout << " 3__a) " << endl;
   goto T;
}
	  //.................б.....................      
	  if (I[s] = n) {
		  if (f(Y[w1][w1], Y[w1][w2])<f(X[w1][w1], X[w1][w2])) {
			  cout << " 3__b) " << endl;
			  //cout <<"f(Y) "<<f(Y[w1][w1],Y[w1][w2])<<endl;
			  //cout <<"f(Y) "<<f(X[w1][w1],X[w1][w2])<<endl;    
			  goto Fourth;        //перейти к 4 шагу                                      
		  }
		  if (f(Y[w1][w1], Y[w1][w2]) >= f(X[w1][w1], X[w1][w2])) {
			  cout << " 3__b) " << endl;
			  Xo[w1][w1] = X[w1][w1];   /*старый базис*/       //cout <<"X ("<<X[w1][w1]<<" ";  
			  Xo[w1][w2] = X[w1][w2];                          //cout <<X[w1][w2]<<")"<<endl; 
															   //cout <<"f(Y) "<<f(Y[w1][w1],Y[w1][w2])<<endl;
															   //cout <<"f(Y) "<<f(X[w1][w1],X[w1][w2])<<endl;    
			  goto Five;        //перейти к 5 шагу                                                     
		  }
	  }  //*/
		 //.4.....................................
  Fourth: X[w1][w1] = Y[w1][w1];       //cout <<X[w1][w1]<<endl;
	  X[w1][w2] = Y[w1][w2];       //cout <<Y[w1][w2]<<endl; 
	  I[s] = 1;
	  Y[w1][w1] = X[w1][w1] + liamda*(X[w1][w1] - Xo[w1][w1]);  //cout <<Y[w1][w1]<<endl;
	  Y[w1][w2] = X[w1][w2] + liamda*(X[w1][w2] - Xo[w1][w2]);  //cout <<Y[w1][w2]<<endl; 
	  cout << " 4__ " << endl;
	  Xo[w1][w1] = X[w1][w1];
	  Xo[w1][w2] = X[w1][w2];       cout << Xo[w1][w1] << " " << Xo[w1][w2] << endl;  //старый базис
	  cout << Y[w1][w1] << " " << Y[w1][w2] << endl;  //старый базис  

	  goto T;
	  //.5.....................................
	  //.................a.....................
  Five:    if ((del_1<E) && (del_2<E)) {
	  cout << " 5__a) " << endl;
	  //cout <<"X ("<<X[w1][w1]<<" "; 
	  //cout <<X[w1][w2]<<")"<<endl;  
	  Xz[w1][w1] = X[w1][w1];
	  Xz[w1][w2] = X[w1][w2];

  }
		   //.................б.....................
		   if ((del_1>E) || (del_2>E)) { //|| ( (del_1E) && (del_2>E) ){
			   cout << " 5__b) " << endl;
			   del_1 = del_1 / 2;   cout << del_1 << "  ";
			   del_2 = del_2 / 2;   cout << del_2 << endl;

			   Y[w1][w1] = X[w1][w1];
			   Y[w1][w2] = X[w1][w2];

			   Xo[w1][w1] = X[w1][w1];
			   Xo[w1][w2] = X[w1][w2];
			   I[s] = 1;

			   goto T;
		   }

		   cout << "X* = " << Xz[w1][w1] << " " << Xz[w1][w2] << endl; //*/ 
}





