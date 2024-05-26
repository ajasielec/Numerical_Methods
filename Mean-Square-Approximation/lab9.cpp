#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

#define SMALL_NUMBER 0.0001

using Matrix = vector<vector<double>>;
using Vector = vector<double>;

static vector<vector<double>> scalMacierz(vector<vector<double>> a, vector<double> b) {
	vector<vector<double>> matrix;
	for (int i = 0; i < a.size(); i++) {
		matrix.push_back(a[i]);
		matrix[i].push_back(b[i]);
	}
	return matrix;
}

static void printExtendedMatrix(vector<vector<double>> a, vector<double> b) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[0].size(); j++) {
			cout << a[i][j] << "\t";
		}
		cout << b[i];
		cout << endl;
	}
}

static bool zeroOnDiagonal(vector <vector<double>> matrix) {
	for (int i = 0; i < matrix.size(); i++) {
		if (matrix[i][i] == 0) return true;
	}
	return false;
}

static vector <double> GaussElimination(vector<vector<double>> matrix) {
	// 1 etap
	int n = matrix.size();
	double m = 0;
	for (int z = 0; z < n; z++) {
		for (int i = z + 1; i < n; i++) {
			m = matrix[i][z] / matrix[z][z];
			for (int j = 0; j < n + 1; j++) {
				matrix[i][j] -= (matrix[z][j] * m);
				if (abs(matrix[i][j]) < SMALL_NUMBER) {
					matrix[i][j] = 0;
				}
			}
		}
	}

	// 2 etap
	vector<double> results(n);
	for (int i = n - 1; i >= 0; --i) {
		results[i] = matrix[i][n] / matrix[i][i];
		for (int j = i - 1; j >= 0; --j) {
			matrix[j][n] -= matrix[j][i] * results[i];
		}
	}

	return results;
}

static Vector aproximate(int n, int m, Vector x, Vector y, double (*w)(double x)) {
	Matrix g(n + 1, Vector(n + 1, 0.0));
	Vector F(n + 1, 0.0);

	for (int k = 0; k <= n; k++) {
		for (int j = 0; j <= n; j++) {
			// wypelnienie g
			g[k][j] = 0.0;
			for (int i = 0; i < m; i++) {
				g[k][j] += pow(x[i], k) * pow(x[i], j) * w(x[i]);
			}
		}
		// wypelnienie F
		F[k] = 0.0;
		for (int i = 0; i < m; i++) {
			F[k] += pow(x[i], k) * y[i] * w(x[i]);
		}
	}

	cout << "\nUklad rownan:\n";
	printExtendedMatrix(g, F);

	// rozwiazanie ukladu rownan metoda Gaussa
	Vector a(n+1, 0.0);
	a = GaussElimination(scalMacierz(g, F));

	return a;
}

int main() {
	// dane
	int n = 1;	// stopien wielomianu
	int m = 8;	// liczba wezlow
	Vector x = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0 };		// wezly aproksymacji
	Vector y = { 2.0,4.0,3.0,5.0,6.0,9.0,11.0,11.0 };	// wartosci aproksymowanej funkcji
	auto w = [](double x) {return 1.0; };				// funkcja wagowa

	// wypisanie liczby wezlow
	cout << "Liczba wezlow: " << m << endl;

	// obliczenie wspolczynnikow wielomianu aproksymujacego
	Vector results = aproximate(n, m, x, y, w);
	cout << "\nWspolczynniki wielomianu aproksymujacego:\n";
	for (const int& i : results) {
		cout << "\ta[" << i << "] = " << results[i] << endl;
	}

	// wezly aproksymacji i wartoœci funkcji w wezlach
	Vector f_xi(n + 1, 0.0);
	cout << "\nWartosci funkcji aproksymujacej w wezlach aproksymacji:\n";
	for (int i = 0; i < m; ++i) {
		double f = 0.0;
		for (int j = 0; j <= n; ++j) {
			f += results[j] * pow(x[i], j);
		}
		cout << "\t(" << x[i] << "," << y[i] << ") -> f(" << x[i] << ") = " << f << endl;
	}
	return 0;
}