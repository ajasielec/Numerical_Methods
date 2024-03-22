#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

#define SMALL_NUMBER 0.0001


void ReadFromFile(string A1, string B1, vector<vector<double>>* a, vector<double>* b)
{
    string line;
    ifstream myfile("" + A1);
    vector<vector<double>> matrix;

    // 1 plik
    if (myfile.good()) {
        while (getline(myfile, line)) {
            vector <double> row;
            istringstream iss(line);
            double number;

            while (iss >> number) {
                row.push_back(number);
            }
            a->push_back(row);
        }
    }
    else {
        std::cout << "Cannot open first file." << endl;
        exit(0);
    }

    myfile.close();

    // 2 plik
    ifstream myfile2("" + B1);

    if (myfile2.good()) {
        double number;
        while (myfile2 >> number) {
            b->push_back(number);
        }
    }
    else {
        std::cout << "Cannot open second file." << endl;
        exit(0);
    }

    myfile.close();
    myfile2.close();
}


void printExtendedMatrix(const vector<vector<double>>& a, const vector<double>& b) {
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a[0].size(); j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << b[i] << endl;
    }
}


void partialPivotElimination(vector<vector<double>> matrix, vector<double> b) {
    int n = matrix.size();
        // znajdz najwiekszy element
        for (int i = 0; i < n; i++) {
            double maxVal = abs(matrix[i][i]);
            int maxRow = i;
            for (int j = i + 1; j < n; j++) {
                if (abs(matrix[j][i]) > maxVal) {
                    maxVal = abs(matrix[j][i]);
                    maxRow = j;
                }
            }
            std::swap(matrix[i], matrix[maxRow]);
            std::swap(b[i], b[maxRow]);
        
        // gauss elimination 
            for (int l = i + 1; l < n; l++) {
                double factor = matrix[l][i] / matrix[i][i];
                for (int k = i; k < n; ++k) {
                    matrix[l][k] -= factor * matrix[i][k];
                    if (abs(matrix[l][k]) < SMALL_NUMBER) {
                        matrix[l][k] = 0;
                    }
                }
                b[l] -= factor * b[i];
                if (abs(b[l]) < SMALL_NUMBER) {
                    b[l] = 0;
                }
            }
        }
    
    // macierz po 1 etapie
    std::cout << "Macierz po postepowaniu prostym (zmiana po wierszach):" << endl;
    printExtendedMatrix(matrix, b);
    std::cout << endl;

    // podstawienie wsteczne
    vector<double> results(n);

    for (int i = n - 1; i >= 0; i--) {
        results[i] = b[i] / matrix[i][i];
        for (int j = i - 1; j >= 0; j--) {
            b[j] -= matrix[j][i] * results[i];
        }
    }

    // wypisz wyniki
    std::cout << "Rozwiazanie ukladu rownan (zmiana po wierszach):" << endl;
    for (size_t i = 0; i < results.size(); i++) {
        std::cout << "x_" << i << " = " << results[i] << endl;
    }
    std::cout << endl;

}


void gaussCroutElimination(vector<vector<double>>& matrix, vector<double>& b) {
    int n = matrix.size();
    vector<double> x(n);

    vector<int> pivot(n);
    for (int i = 0; i < n; ++i) {
        pivot[i] = i;
    }

    for (int i = 0; i < n; ++i) {
        // szukanie elementu maksymalnego w kolumnie
        double maxVal = abs(matrix[i][i]);
        int maxRow = i;
        int maxCol = i;
        for (int col = i; col < n; col++) {
            if (abs(matrix[i][col]) > maxVal) {
                maxVal = abs(matrix[i][col]);
                maxCol = col;
            }
        }

        // zamiana miejscami kolumn
        for (int row = 0; row < n; ++row) {
            swap(matrix[row][i], matrix[row][maxCol]);
        }
        swap(pivot[i], pivot[maxCol]);

        // eliminacja w kolumnie i-tej
        for (int j = i + 1; j < n; ++j) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < n; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
            b[j] -= factor * b[i];
        }
    }

    // macierz po pierwszym etapie
    cout << "Macierz po postepowaniu prostym (zmiana po kolumnach):" << endl;
    printExtendedMatrix(matrix, b);
    cout << endl;

    // wektor z pivotem
    cout << "Wektor z numerami kolumn:" << endl;
    cout << '[';
    for (int i = 0; i < n-1; i++) {
        cout << pivot[i] << ", ";
    }
    cout << pivot[n-1] << ']' << endl;

    // rozwiązanie
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += matrix[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / matrix[i][i];
    }

    cout << "\nRozwiazanie ukladu rownan (zmiana po kolumnach):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x_" << pivot[i] << " = " << x[i] << endl;
    }
}

int main() {
    // create matrix
    vector<vector<double>> a;
    vector<double> b;
    ReadFromFile("A1.txt", "B1.txt", &a, &b);

    // write out matrix
    std::cout << "Macierz przed obliczeniami: " << endl;
    printExtendedMatrix(a, b);
    std::cout << endl;

    // zmiana po wierszach
    cout << "\nZADANIE 1: zamiana po wierszach" << endl << endl;
    partialPivotElimination(a, b);

    // zmiana po kolumnach
    cout << "\nZADANIE 2: zamiana po kolumnach" << endl << endl;
    gaussCroutElimination(a, b);
   

    return 0;
}