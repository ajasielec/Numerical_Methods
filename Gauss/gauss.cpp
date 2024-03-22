#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

#define SMALL_NUMBER 0.0001

void ReadFromFile(string A1, string B1, vector<vector<double>> *a, vector<double> *b)
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
        cout << "Cannot open first file." << endl;
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
        cout << "Cannot open second file." << endl;
        exit(0);
    }

    myfile.close();
    myfile2.close();

}

void printMatrix(vector<vector<double>> matrix) {
    for (const auto& row : matrix) {
        for (float element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

void printExtendedMatrix(vector<vector<double>> a, vector<double> b) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[0].size(); j++) {
            cout << a[i][j] << "\t";
        }
        cout << b[i];
        cout << endl;
    }
}

bool zeroOnDiagonal(vector <vector<double>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i][i] == 0) return true;
    }
    return false;
}

vector <double> GaussElimination(vector<vector<double>> matrix) {
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

    cout << "Macierz po pierwszym etapie obliczen: " << endl;
    printMatrix(matrix);

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

vector<vector<double>> scalMacierz(vector<vector<double>> a, vector<double> b) {
    vector<vector<double>> matrix;
    for (int i = 0; i < a.size(); i++) {
        matrix.push_back(a[i]);
        matrix[i].push_back(b[i]);
    }
    return matrix;
}


int main() {

    // create matrix
    vector<vector<double>> a;
    vector<double> b;
    ReadFromFile("A1.txt", "B1.txt", &a, &b);

    // extended matrix
    vector<vector<double>> matrix;
    matrix = scalMacierz(a, b);

    // write out matrix
    cout << "Macierz przed obliczeniami: " << endl;
    printMatrix(matrix);
    cout << endl;

   
    vector<double> results;

    // check if there are zeros on the diagonal
    if (zeroOnDiagonal(a)) {
        cout << "Obliczenia niemozliwe - zera na przekatnej!" << endl;
    }
    else {
        // calculate gauss
        results = GaussElimination(matrix);
        cout << "\nRozwiazanie ukladu rownan:";
        for (int i = 0; i < results.size(); i++) {
            cout << "\nx_" << i << " = " << results[i];
        }
        cout << endl;
    }

    return 0;
}