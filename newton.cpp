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

    Punkt() { x = 0; y = 0; }
    Punkt(float x, float y) {
        this->x = x;
        this->y = y;
    }
    void wypisz() {
        cout << "(" << x << "," << y << ")";
    }
};

//funkcja umieszczajaca punkty w wektorze
void ReadFromFile(string path, vector<Punkt> *punkty, float *liczba_wezlow)
{	string line;
	ifstream myfile(""+path);

    if (myfile.good()) {
        float val;
        bool isNode = true;
        Punkt p;
        myfile >> val;
        *liczba_wezlow = val;
        while (myfile >> val) {
            isNode ? p.x = val : p.y = val;
            if (!isNode) punkty->push_back(p);
            isNode = !isNode;
        }
    }
}



float interpolacjaNewtona(vector<Punkt> &wezly, float x) {
    float p_0 = 1.0;
    float p_k = 1.0;
    float b_0 = wezly[0].y;
    float b_k = 0.0;
    float mianownik = 1;
    float Wn = p_0 * b_0;


    for (int wezel = 1; wezel<wezly.size(); wezel++){
        //obliczanie bk
        b_k = 0.0;
        for (int i = 0; i <= wezel; i++) {
            mianownik = 1.0;
            for (int j = 0; j <= wezel; j++) {
                if (i != j) {
                    mianownik *= wezly[i].x - wezly[j].x;
                }
            }
            b_k += (wezly[i].y / mianownik);
        }
        //obliczanie pk
        p_k = 1.0;
        for (int i = 0; i < wezel; i++) {
            p_k *= (x - wezly[i].x);
        }
        //dodawanie do wielomianu
        Wn += (b_k * p_k);
    }

    return Wn;
}

int main() {
    //ZAD_1
    cout << "ZAD_1:" << endl;
    //pobranie danych od uzytkownika
    float x;
    cout << "Podaj szukany punkt: ";
    cin >> x;

    vector <Punkt> wezly;
    float liczba_wezlow;
    ReadFromFile("zmienne.txt", &wezly, &liczba_wezlow);
  
    //wypisanie liczby w�z��w
    cout << "Liczba wezlow = " << liczba_wezlow << endl;

    //wypisanie wezlow interpolacji i wartosci funkcji w wezlach
    cout << "Dane: " << endl;
    for (int i = 0; i < wezly.size(); i++) {
        wezly[i].wypisz();
        cout << " ";
    }

    //wypisanie punktu w ktorym liczymy wartosc wielomianu
    cout << "\nPunkt, w ktorym liczymy wartosc wielomianu: x = " << x << endl;

    //obliczanie wartosci wielomianu w punkcie x
    
   float Wx = interpolacjaNewtona(wezly, x);
   cout << "Wartosc wielomianu w szukanym punkcie: " << Wx;

    return 0;
}

