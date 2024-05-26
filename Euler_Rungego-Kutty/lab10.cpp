#include <iostream>
#include<vector>

using namespace std;

// metoda eulera
double euler(double (*f)(double, double), double x0, double y0, double xk, int N) {
	double h = (xk - x0) / N;
	vector<double> x(N+1, 0.0);
	vector<double> y(N+1, 0.0);
	x[0] = x0;
	y[0] = y0;
	for (int i = 1; i <= N; i++) {
		x[i] = x[i - 1] + h;
		// cout << x[i] << endl;
		y[i] = y[i - 1] + h * f(x[i - 1], y[i - 1]);
		// cout << y[i] << endl;

	}
	return y[N];
}

double rk2(double (*f)(double, double), double x0, double y0, double xk, int N) {
	double h = (xk - x0) / N;
	vector<double> x(N + 1, 0.0);
	vector<double> y(N + 1, 0.0);
	x[0] = x0;
	y[0] = y0;
	for (int i = 0; i < N; i++) {
		double k1 = f(x[i], y[i]);
		double k2 = f(x[i] + h, y[i] + h * k1);
		double phi = (k1 + k2) / 2;
		y[i + 1] = y[i] + h * phi;
		x[i + 1] = x[i] + h;
		//cout << " x[" << i << "] = " << x[i] << endl;
	}
	return y[N];
}

double rk4(double (*f)(double, double), double x0, double y0, double xk, int N) {
	double h = (xk - x0) / N;
	vector<double> x(N + 1, 0.0);
	vector<double> y(N + 1, 0.0);
	x[0] = x0;
	y[0] = y0;
	for (int i = 0; i < N; i++) {
		double k1 = f(x[i], y[i]);
		double k2 = f(x[i] + h/2, y[i] + h * k1 / 2);
		double k3 = f(x[i] + h / 2, y[i] + h * k2 / 2);
		double k4 = f(x[i] + h, y[i] + h * k3);
		double phi = (k1 + 2*k2 + 2*k3 + k4) / 6;
		y[i + 1] = y[i] + h * phi;
		x[i + 1] = x[i] + h;
	}
	return y[N];
}

int main() {
	// dane
	int N = 10;
	auto f = [](double x, double y) {return 2 * y * (x + 1); };		// f(x,y)
	double y_0 = 1.0;		// warunek poczatkowy
	double x_k = 1.0;
	double x_0 = 0.0;

	// wyswietlanie w konsoli
	cout << "Punkt koncowy: x = " << x_k << endl;
	cout << "Krok obliczen: N = " << N << endl;

	// rozwiazania
	cout << "\n1. f(x,y) = 2y(x+1), y(0) = " << y_0 << endl;
	double euler_result = euler(f, x_0, y_0, x_k, N);
	cout << "\tEuler: " << euler_result << endl;
	double rk2_result = rk2(f, x_0, y_0, x_k, N);
	cout << "\trk2: " << rk2_result << endl;
	double rk4_result = rk4(f, x_0, y_0, x_k, N);
	cout << "\trk4: " << rk4_result << endl;
	cout << "\trzeczywisty: " << 20.0855 << endl;

	// dane do 2
	auto f2 = [](double x, double y) {return x+y; };		// f(x,y)
	y_0 = 0.1;		// warunek poczatkowy

	cout << "---------------------------------" << endl;
	cout << "\n2. f(x,y) = x + y, y(0) = " << y_0 << endl;
	euler_result = euler(f2, x_0, y_0, x_k, N);
	cout << "\tEuler: " << euler_result << endl;
	rk2_result = rk2(f2, x_0, y_0, x_k, N);
	cout << "\trk2: " << rk2_result << endl;
	rk4_result = rk4(f2, x_0, y_0, x_k, N);
	cout << "\trk4: " << rk4_result << endl;
	cout << "\trzeczywisty: " << 0.99011 << endl;

	return 0;
}