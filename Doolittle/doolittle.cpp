#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

#define SMALL_NUMBER 0.0001


void ReadFromFile(string A1, string B1, vector<vector<double>>* a, vector<double>* b)
{
    // 1 plik
    string line;
    ifstream file_A("" + A1);

    if (file_A.good()) {
        while (getline(file_A, line)) {
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

    file_A.close();

    // 2 plik
    ifstream file_B("" + B1);

    if (file_B.good()) {
        double number;
        while (file_B >> number) {
            b->push_back(number);
        }
    }
    else {
        std::cout << "Cannot open second file." << endl;
        exit(0);
    }

    file_B.close();
}

void printMatrix(const vector<vector<double>>& a) {
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a[0].size(); j++) {
            std::cout << a[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
void printMatrix(const vector<vector<double>>& a, const vector<double>& b) {
    for (size_t i = 0; i < a.size(); i++) {
        for (size_t j = 0; j < a[0].size(); j++) {
            std::cout << a[i][j] << "\t";
        }
        std::cout << b[i] << std::endl;
    }
    cout << endl;
}
void printMatrix(const vector<double>& b) {
    cout << '[';
    for (size_t i = 0; i < b.size()-1; i++) {
            std::cout << b[i] << ", ";
    }
    cout << b[b.size()-1]<< ']' << endl << endl;
}

// Funkcja rozwi¹zuj¹ca uk³ad równañ przy u¿yciu rozk³adu LU
vector<double> solveEquations(const vector<vector<double>>& A, const vector<double>& b) {
    
    int n = A.size();

    // jesli 0 na przekatnej - zakoncz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][i] == 0) {
                cout << "Zero na przekatnej - nie mozna rozwiazac." << endl;
                exit(0);
            }
        }
    }        
    
    // ROZKLAD LU //
    // utworz dwie macierze L i U o stopniu macierzy A, wypelnione zerami
    vector<vector<double>> L(n, vector<double>(n, 0.0));
    vector<vector<double>> U(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        // przypisz 1 na przekatnej macierzy L
        L[i][i] = 1.0;

        for (int j = 0; j < n; j++) {
            if (i <= j) {
            // oblicz macierz U
                double suma = 0.0f;
                for (int k = 0; k < i; k++) {
                    suma += (L[i][k] * U[k][j]);
                }
                U[i][j] = A[i][j] - suma;
            }
            else {
            // oblicz macierz L
                double suma = 0.0f;
                for (int k = 0; k < j; k++) {
                    suma += (L[i][k] * U[k][j]);
                }
                L[i][j] = (A[i][j] - suma) / U[j][j];
            }
        }
    }
    // wypisz macierze L i U
    cout << "Macierz L:" << endl;
    printMatrix(L);
    cout << "Macierz U:" << endl;
    printMatrix(U);

    // rozwiazanie rownania LxY = B 
    vector<double> y(n);
    y[0] = b[0];
    for (int i = 0; i < n; ++i) {
        double suma = 0.0f;
        for (int j = 0; j < i; j++) {
            suma += L[i][j] * y[j];
        }
        y[i] = (b[i] - suma);
    }

    // wypisz wektor y
    cout << "Wektor y:" << endl;
    printMatrix(y);

    // rozwiazanie rownania UX = Y (podstawienie wstecz)
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        double suma = 0.0f;
        for (int j = i + 1; j < n; j++) {
            suma += U[i][j] * x[j];
        }
        x[i] = (y[i] - suma) / U[i][i];
    }

    return x;
}

int main() {
    
    vector<vector<double>> A;
    vector<double> b;

    // wczytanie danych z pliku
    ReadFromFile("A1.txt", "B1.txt", &A, &b);

    // wypisanie macierzy przed obliczeniami
    cout << "Macierz rozszerzona (przed obliczeniami):" << endl;
    printMatrix(A, b);

    // rozwi¹zanie uk³adu równañ
    vector<double> solution = solveEquations(A, b);

    // wyœwietlenie rozwi¹zania
    cout << "Rozwiazanie ukladu rownan:" << endl;
    for (int i = 0; i < solution.size(); ++i)
        cout << "x" << i << " = " << solution[i] << endl;

    return 0;
}
