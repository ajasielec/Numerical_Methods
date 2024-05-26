#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
#define SMALL_NUMBER 0e-3

// metoda stycznych
double MetodaStycznych (double (*f)(double), double (*df_f)(double), double a, double b, double x_0, double e) {
	// zalozenia
	if (f(a) * f(b) > 0) {
		cout << "Funkcja nie posiada pierwiastka f(x) = 0" << endl;
		return NULL;
	}

	
	vector<double> x;
	x.push_back(x_0);
	int k = 0;
	while (f(x[k]) != SMALL_NUMBER) {
		x.push_back (x[k] - (f(x[k]) / df_f(x[k])));
		k++;
		cout << "f(" << x[k] << ") = " << f(x[k]) << endl;

	}
	cout << "Liczba iteracji: " << k << endl;

	return x[k];
}

// metoda siecznych
double MetodaSiecznych(double (*f)(double), double a, double b, double x_0, double e) {
	vector<double> x;
	x.push_back(x_0 - 0.1);
	x.push_back(x_0);
	int k = 1;
	while (f(x[k]) != SMALL_NUMBER) {
		x.push_back(x[k] - f(x[k]) * (x[k]-x[k-1]) / (f(x[k]) - f(x[k-1]) ) );
		k++;
		cout << "f(" << x[k] << ") = " << f(x[k]) << endl;
	}
	cout << "Liczba iteracji: " << k << endl;

	return x[k];
}


int main() {
	// dane
	auto f = [](double x) {return -pow(x, 3) + 10 * x + 5; };		// f(x)
	auto df_f = [](double x) {return -3 * x * x + 10; };			// f'(x)
	double a = 2.0;
	double b = 6.0;
	double x_0 = 6.0;	// punkt startowy
	double e = 0.001;	// dokladnosc
	cout << "Podaj punkt startowy: ";
	cin >> x_0;

	// wyswietlanie w konsoli
	cout << "f(x) = -x^3 + 10x + 5" << endl;
	cout << "Metoda stycznych: " << endl;
	double result = MetodaStycznych(f, df_f, a, b, x_0, e);
	//cout << "f(" << result << ") = 0" << endl;

	cout << "\nMetoda siecznych: " << endl;
	double result2 = MetodaSiecznych(f, a, b, x_0, e);
	//cout << "f(" << result2 << ") = 0" << endl;

	
	return 0;
}