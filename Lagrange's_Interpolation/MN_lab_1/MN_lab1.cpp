/*
Format of a data file should be as following.
First line: Number of nodes
Next lines:
On the left: node, on the right: value of that node
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;



struct Point {
    float x;
    float y;

    Point() { x = 0; y = 0; }
    Point(float x, float y) {
        this->x = x;
        this->y = y;
    }
    void write() {
        cout << "(" << x << "," << y << ")";
    }
};

void ReadFromFile(string path, vector<Point>* points, float* node_count)
{
    string line;
    ifstream myfile("" + path);

    if (myfile.good()) {
        float val;
        bool isNode = true;
        Point p;
        myfile >> val;
        *node_count = val;
        while (myfile >> val) {
            isNode ? p.x = val : p.y = val;
            if (!isNode) points->push_back(p);
            isNode = !isNode;
        }
    }
    else {
        cout << "Cannot open a file." << endl;
        exit(0);
    }
}

//funkcja obliczajaca wartosc wielomianu w punkcie x
float LaGrangeInterpolation(vector<Point> points, float x) {

    float L, l_i;
    vector <float> l;

    //calculate l
    for (int i = 0; i < points.size(); i++) {
        l_i = 1;
        for (int j = 0; j < points.size(); j++) {
            if (i != j) {
                l_i *= (x - points[j].x) / (points[i].x - points[j].x);
            }
        }
        l.push_back(l_i);
    }

    //calculate L
    L = 0;
    for (int i = 0; i < points.size(); i++) {
        L += l[i] * points[i].y;
    }
    return L;
}


int main() {
    float x;
    cout << "Enter a point at which you want to calculate the value of La Grange's interpolation polynomial: ";
    cin >> x;

    vector <Point> points;
    float node_count;
    ReadFromFile("data.txt", &points, &node_count);

    cout << "Number of nodes = " << points.size() << endl;

    cout << "Data: " << endl;
    for (int i = 0; i < points.size(); i++) {
        points[i].write();
        cout << " ";
    }

    cout << "\nPoint at which we calculate the value of the polynomial: x = " << x << endl;

    float L = LaGrangeInterpolation(points, x);
    cout << "Value of the polynomial in a given point: " << L << endl;

    points.clear();

    /*ADDITIONAL TASK*/
    //calculate third degree root of 50
    cout << "\n\n************************************************" << endl;
    cout << "Task: calculate third degree root of 50" << endl;
    double sq3 = 1.0 / 3.0;
    vector <double> nodes;
    vector <double> values;
    nodes.push_back(27.0);
    nodes.push_back(64.0);
    nodes.push_back(125.0);
    nodes.push_back(216.0);

    for (int i = 0; i < nodes.size(); i++) {
        values.push_back(pow(nodes[i], sq3));
        Point p(nodes[i], values[i]);
        points.push_back(p);
    }

    x = 50;
    L = LaGrangeInterpolation(points, 50);
    cout << "Third degree root of " << x << ": " << L << endl;

    return 0;
}

