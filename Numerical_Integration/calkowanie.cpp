#include <iostream>
#include <functional>
#include <cmath>
using namespace std;

float metodaProstokatow(float (*f)(float x), float a, float b, int n) {
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

float metodaTrapezow(float (*f)(float x), float a, float b, int n) {
	float s = (b - a) / n;

	float * x = new float[n + 1];
	for (int i = 0; i < n + 1; i++) {
		x[i] = a + i * s;
	}

	float sum = 0.0f;
	for (int i = 0; i < n; i++) {
		sum += ((x[i + 1] - x[i]) / 2) * (f(x[i]) + f(x[i + 1]));
	}

	return sum;
}

float metodaSimpsona(float (*f)(float x), float a, float b, int n) {
	return (b - a) / 6 * (f(a) + 4 * f((a + b) / 2) + f(b));
}


int main() 
{
	float a, b;
	int n = 16;

	//*		calka z sin(x)		*//
	a = 0.5, b = 2.5;

	cout << "f(x) = sin(x)" << endl;
	cout << "Przedzial calkowania: <" << a << ", " << b << ">" << endl;
	cout << "Liczba przedzialow: " << n << endl;

	cout << "\tmetoda prostakatow: " << metodaProstokatow(sin, a, b, n) << endl;
	cout << "\tmetoda trapezow: " << metodaTrapezow(sin, a, b, n) << endl;
	cout << "\tmetoda Simpsona: " << metodaSimpsona(sin, a, b, n) << endl;
	cout << endl;

	//*		calka z x^2 + 2x + 5"	*//
	auto f = [](float x) {return x * x + 2 * x + 5; };
	a = 0.5, b = 5.0;

	cout << "f(x) = x^2 + 2x + 5" << endl;
	cout << "Przedzial calkowania: <" << a << ", " << b << ">" << endl;
	cout << "Liczba przedzialow: " << n << endl;

	cout << "\tmetoda prostakatow: " << metodaProstokatow(f, a, b, n) << endl;
	cout << "\tmetoda trapezow : " << metodaTrapezow(f, a, b, n) << endl;
	cout << "\tmetoda Simpsona: " << metodaSimpsona(f, a, b, n) << endl;
	cout << endl;

	//*		calka z exp(x)		*//
	a = 0.5, b = 5.0;

	cout << "f(x) = exp(x)" << endl;
	cout << "Przedzial calkowania: <" << a << ", " << b << ">" << endl;
	cout << "Liczba przedzialow: " << n << endl;

	cout << "\tmetoda prostakatow: " << metodaProstokatow(exp, a, b, n) << endl;
	cout << "\tmetoda trapezow: " << metodaTrapezow(exp, a, b, n) << endl;
	cout << "\tmetoda Simpsona: " << metodaSimpsona(exp, a, b, n) << endl;
	cout << endl;

	return 0;
}