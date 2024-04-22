#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;

// Typ aliasu dla macierzy
using Matrix = vector<vector<double>>;
// Typ aliasu dla wektora
using Vector = vector<double>;

Matrix readMatrix(const string& filename) {
    string line;
    ifstream myfile(filename);
    Matrix matrix;

    if (myfile.good()) {
        while (getline(myfile, line)) {
            vector <double> row;
            istringstream iss(line);
            double number;

            while (iss >> number) {
                row.push_back(number);
            }
            matrix.push_back(row);
        }
    }
    else {
        std::cout << "Cannot open first file." << endl;
        exit(0);
    }

    myfile.close();
    return matrix;
}

// wypisywanie macierzy
void showMatrix(Matrix matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << '\t';
        }
        cout << endl;
    }
}

// Funkcja sprawdzaj¹ca, czy macierz jest diagonalnie s³abo dominuj¹ca
bool isDiagonallyDominant(const Matrix& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        double diagonalElement = abs(matrix[i][i]);
        double sumOfNonDiagonal = 0.0;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                sumOfNonDiagonal += abs(matrix[i][j]);
            }
        }
        if (diagonalElement < sumOfNonDiagonal) {
            return false;
        }
    }
    return true;
}

// Metoda Jacobiego
Vector jacobiMethod(const Matrix& matrix, int iterations) {
    int n = matrix.size();
    Vector x(n, 0.0);

    // Wydzielenie macierzy D, L i U
    Matrix D(n, Vector(n, 0.0));
    Matrix L_U(n, Vector(n, 0.0));

    // Obliczenie macierzy L+U
    for (int i = 0; i < n; ++i) {
        D[i][i] = matrix[i][i];
        for (int j = 0; j < n; ++j) {
            if (j < i) {
                L_U[i][j] = matrix[i][j];
            }
            else if (j > i) {
                L_U[i][j] = matrix[i][j];
            }
        }
    }

    // Obliczenie macierzy D^(-1)
    Matrix D_inv(n, Vector(n, 0.0));
    for (int i = 0; i < n; ++i) {
        D_inv[i][i] = 1 / D[i][i];
    }

    // Wypisanie macierzy L+U oraz D^-1
    cout << "\nMacierz L+U:" << endl;
    showMatrix(L_U);
    cout << "\nMacierz diagonalna odwrotna:" << endl;
    showMatrix(D_inv);


    for (int iter = 0; iter < iterations; iter++) {
        // cout << "nr iteracji: " << iter << endl;
        Vector x_new(n, 0.0);
        // Obliczenie kolejnego przybli¿enia x
        for (int i = 0; i < n; ++i) {
            double sum1 = 0.0;
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    sum1 += L_U[i][j] * x[j];
                }
            }
            x_new[i] = -sum1;
            x_new[i] += matrix[i].back();
        }
        // Pomno¿enie przez macierz D^-1
        for (int i = 0; i < n; ++i) {
            x_new[i] *= D_inv[i][i];
        }
        x = x_new;
    }
    return x;
}

// Metoda Jacobiego dla zad 2
Vector jacobiMethod2(const Matrix& matrix, double epsilon, int max_iterations) {
    int n = matrix.size();
    Vector x(n, 0.0);
    Vector x_prev = x;

    for (int iter = 0; iter < max_iterations; ++iter) {
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    sum += matrix[i][j] * x_prev[j];
                }
            }
            x[i] = (matrix[i].back() - sum) / matrix[i][i];
        }

        // Sprawdzenie warunku stopu dla ka¿dego x
        bool stop_condition_met = true;
        for (int i = 0; i < n; ++i) {
            if (abs(x[i] - x_prev[i]) >= epsilon) {
                stop_condition_met = false;
                break;
            }
        }
        if (stop_condition_met) {
            cout << "Warunek stopu zostal spelniony po " << iter + 1 << " iteracjach." << endl;
            break;
        }

        x_prev = x;
    }

    return x;
}

int main() {
    // ZADANIE 1 //
    // wczytanie macierzy z pliku
    string filename = "A1.txt";
    Matrix matrix = readMatrix(filename);
    cout << "Macierz rozszerzona:" << endl;
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }

    // sprawdzenie czy macierz jest diagonalnie slabo dominujaca
    if (isDiagonallyDominant(matrix)) {
        cout << "Macierz jest diagonalnie slabo dominujaca." << endl;
    }
    else {
        cout << "Macierz nie jest diagonalnie slabo dominujaca." << endl;
    }

    // okreslenie liczby iteracji
    int iterations;
    cout << "Podaj liczbe iteracji: ";
    cin >> iterations;

    // wypisanie rozwi¹zania
    Vector solution_jacobi = jacobiMethod(matrix, iterations);
    cout << "\nRozwiazanie po " << iterations << " iteracjach:" << endl;
    for (int i = 0; i < solution_jacobi.size(); i++) {
        cout <<"x[" << i << "] = " << solution_jacobi[i] << endl;
    }
    cout << endl;

    // ZADANIE 2 //
    double epsilon_values[] = { 0.001, 0.000001 };
    int max_iterations = 1000; // Maksymalna iloœæ iteracji

    for (double epsilon : epsilon_values) {
        cout << "\nObliczenia dla epsilon = " << epsilon << endl;
        Vector solution_jacobi = jacobiMethod2(matrix, epsilon, max_iterations);

        cout << "Rozwiazanie ukladu rownan:" << endl;
        for (const auto& elem : solution_jacobi) {
            cout << elem << " ";
        }
        cout << endl;

        cout << "Wartosc bledu dla kazdego x:" << endl;
        for (int i = 0; i < solution_jacobi.size(); ++i) {
            double error = abs(solution_jacobi[i] - matrix[i].back());
            cout << "x[" << i << "]: " << error << endl;
        }
    }

    return 0;
}
