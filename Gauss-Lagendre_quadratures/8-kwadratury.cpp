#include <iostream>
#include <stdlib.h>

using namespace std;

static float metodaProstokatow(float (*f)(float x), float a, float b, int n) {
	float s = (b - a) / n;

	float* x = new float[n];
	for (int i = 0; i < n; i++) {
		x[i] = a + i * s;
	}

	float sum = 0.0f;
	for (int i = 0; i < n; i++) {
		sum += f(x[i] + (1.0 / 2.0) * s);
	}

	return s * sum;
}

static float metodaTrapezow(float (*f)(float x), float a, float b, int n) {
	float s = (b - a) / n;

	float* x = new float[n + 1];
	for (int i = 0; i < n + 1; i++) {
		x[i] = a + i * s;
	}

	float sum = 0.0f;
	for (int i = 0; i < n; i++) {
		sum += ((x[i + 1] - x[i]) / 2) * (f(x[i]) + f(x[i + 1]));
	}

	return sum;
}

static float metodaSimpsona(float (*f)(float x), float a, float b, int n) {
	return (b - a) / 6 * (f(a) + 4 * f((a + b) / 2) + f(b));
}

static float solve_quadratures(float (*f)(float x), float a, float b, int n) {
	float* x = new float[n];
	float* A = new float[n];
	if (n == 2) {
		x[0] = -sqrt(3.0) / 3.0;
		x[1] = sqrt(3.0) / 3.0;
		A[0] = 1;
		A[1] = 1;
	}
	else if (n == 3) {
		x[0] = -sqrt(3.0 / 5.0);
		x[1] = 0;
		x[2] = sqrt(3.0 / 5.0);

		A[0] = 5.0 / 9.0;
		A[1] = 8.0 / 9.0;
		A[2] = 5.0 / 9.0;
	}
	else if (n == 4) {
		x[0] = -(1.0 / 35.0) * sqrt(525.0 + 70.0 * sqrt(30.0));
		x[1] = -(1.0 / 35.0) * sqrt(525.0 - 70.0 * sqrt(30.0));
		x[2] = (1.0 / 35.0) * sqrt(525.0 - 70.0 * sqrt(30.0));
		x[3] = (1.0 / 35.0) * sqrt(525.0 + 70.0 * sqrt(30.0));

		A[0] = (1.0 / 36.0) * (18.0 - sqrt(30.0));
		A[1] = (1.0 / 36.0) * (18.0 + sqrt(30.0));
		A[2] = (1.0 / 36.0) * (18.0 + sqrt(30.0));
		A[3] = (1.0 / 36.0) * (18.0 - sqrt(30.0));
	}
	else {
		std::cout << "Wrong number of nodes!" << std::endl;
		exit(0);
	}

	float t_i;
	float sum = 0.0;
	for (int i = 0; i < n; i++) {
		t_i = (a + b) / 2 + (b - a) / 2 * x[i];
		sum += A[i] * f(t_i);
	}

	return (b - a) / 2 * sum;
}

int main() {
	float a, b;
	int n = 1;

	// calka z sin
	std::cout << "f(x) = sin(x)\n";
	a = 0.5, b = 2.5;
	cout << "\tDokladny wynik: " << -cos(b) + cos(a) << endl;
	cout << "\tmetoda prostakatow: " << metodaProstokatow(sin, a, b, n) << endl;
	cout << "\tmetoda trapezow: " << metodaTrapezow(sin, a, b, n) << endl;
	cout << "\tmetoda Simpsona: " << metodaSimpsona(sin, a, b, n) << endl;

	cout << "\tmetoda kwadratur:" << endl;

	for (int n = 2; n <= 4; n++) {
		std::cout << "\t\tn = " << n << ": " << solve_quadratures(sin, a, b, n) << std::endl;
	}

	// calka z x^2 + 2x + 5
	std::cout << "\nf(x) = x^2 + 2x + 5\n";
	auto f = [](float x) {return x * x + 2 * x + 5; };
	a = 0.5, b = 5;
	cout << "\tDokladny wynik: " << pow(5, 3) / 3 + pow(5, 2) + 5 * 5 - (pow(0.5, 3) / 3 + pow(0.5, 2) + 5 * 0.5)<< endl;
	cout << "\tmetoda prostakatow: " << metodaProstokatow(f, a, b, n) << endl;
	cout << "\tmetoda trapezow: " << metodaTrapezow(f, a, b, n) << endl;
	cout << "\tmetoda Simpsona: " << metodaSimpsona(f, a, b, n) << endl;

	cout << "\tmetoda kwadratur:" << endl;

	for (int n = 2; n <= 4; n++) {
		std::cout << "\tn = " << n << ": " << solve_quadratures(f, a, b, n) << std::endl;
	}

	// calka z exp(x)
	std::cout << "\nf(x) = exp(x)\n";
	cout << "\tDokladny wynik: " << 146.764 << endl;
	cout << "\tmetoda prostakatow: " << metodaProstokatow(exp, a, b, n) << endl;
	cout << "\tmetoda trapezow: " << metodaTrapezow(exp, a, b, n) << endl;
	cout << "\tmetoda Simpsona: " << metodaSimpsona(exp, a, b, n) << endl;

	cout << "\tmetoda kwadratur:" << endl;

	for (int n = 2; n <= 4; n++) {
		std::cout << "\tn = " << n << ": " << solve_quadratures(exp, a, b, n) << std::endl;
	}

	return 0;
}