//Anna Jasielec, gr.4 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

struct Punkt {
    float x;
    float y;

    Punkt() {}
    Punkt(float x, float y) {
        this->x = x;
        this->y = y;
    }
    void wypisz() {
        cout << "(" << x << "," << y << ")";
    }
};

//funkcja umieszczajaca punkty w wektorze
void ReadFromFile(string path, vector<Punkt> *wezly)
{	string line;
	ifstream myfile(""+path);

    if (myfile.good()) {
        float val;
        bool isNode = true;
        Punkt p;
        while (myfile >> val) {
            isNode ? p.x = val : p.y = val;
            if (!isNode) wezly->push_back(p);
            isNode = !isNode;
        }
    }
}

//funkcja obliczajaca wartosc wielomianu w punkcie x
float interpolacja(vector<Punkt> wezly, float x) {

    float L, l_i;
    vector <float> l;

    //wyliczenie l
    for (int i = 0; i < wezly.size(); i++) {
        l_i = 1;
        for (int j = 0; j < wezly.size(); j++) {
            if (i != j) {
                l_i *= (x - wezly[j].x) / (wezly[i].x - wezly[j].x);
            }
        }
        //cout << "l" << i <<  ": " << l_i << endl;
        l.push_back(l_i);
    }

    //wyliczenie L
    L = 0;
    for (int i = 0; i < wezly.size(); i++) {
        L += l[i] * wezly[i].y;
    }
    return L;
}


int main() {
    //ZAD_1
    cout << "ZAD_1:" << endl;
    //pobranie danych od uzytkownika
    float x;
    cout << "Podaj szukany punkt: ";
    cin >> x;

    vector <Punkt> wezly;
    ReadFromFile("zmienne.txt", &wezly);
  
    //wypisanie liczby wêz³ów
    cout << "Liczba wezlow = " << wezly.size() << endl;

    //wypisanie wezlow interpolacji i wartosci funkcji w wezlach
    cout << "Dane: " << endl;
    for (int i = 0; i < wezly.size(); i++) {
        wezly[i].wypisz();
        cout << " ";
    }

    //wypisanie punktu w ktorym liczymy wartosc wielomianu
    cout << "\nPunkt, w ktorym liczymy wartosc wielomianu: x = " << x << endl;

    //obliczanie wartosci wielomianu w punkcie x
    float L = interpolacja(wezly, x);
    cout << "Wartosc wielomianu Lagrange'a w punkcie " << x <<": " << L << endl;

    //ZAD_2
    cout << "\nZAD_2: " << endl;
    double sq3 = 1.0/3.0;
    vector <double> wezly_z2;
    vector <double> wartosci_z2;
    vector <Punkt> dane;
    wezly_z2.push_back(27.0);
    wezly_z2.push_back(64.0);
    wezly_z2.push_back(125.0);
    wezly_z2.push_back(216.0);

    for (int i = 0; i < wezly_z2.size(); i++) {
        wartosci_z2.push_back(pow(wezly_z2[i], sq3));
        Punkt p(wezly_z2[i], wartosci_z2[i]);
        dane.push_back(p);
    }

    x = pow(50, sq3);
    L = interpolacja(dane, x);
    cout << "Wartosc wielomianu Lagrange'a w punkcie " << x << ": " << L << endl;

    return 0;
}

