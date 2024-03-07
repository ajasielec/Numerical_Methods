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

//function puts data from a file to a vector
void ReadFromFile(string path, vector<Point> *points, float *node_count)
{	string line;
	ifstream myfile(""+path);

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


float NewtonInterpolation(vector<Point> &points, float x, vector<float> *coefficients) {
    float p_0 = 1.0;
    float p_k = 1.0;
    float b_0 = points[0].y;
    coefficients->push_back(b_0);
    float b_k = 0.0;
    float denominator = 1;
    float result = p_0 * b_0;


    for (int node = 1; node<points.size(); node++){
        //calculate bk
        b_k = 0.0;
        for (int i = 0; i <= node; i++) {
            denominator = 1.0;
            for (int j = 0; j <= node; j++) {
                if (i != j) {
                    denominator *= points[i].x - points[j].x;
                }
            }
            b_k += (points[i].y / denominator);
            
        }
        //calculate pk
        p_k = 1.0;
        for (int i = 0; i < node; i++) {
            p_k *= (x - points[i].x);
        }
        //adding to polynomial
        result += (b_k * p_k);
        coefficients->push_back(b_k);    
    }
    return result;
}

int main() {
    //get user input
    float x;
    cout << "Enter a point at which you want to calculate the value of Newton's interpolation polynomial: ";
    cin >> x;

    vector <Point> points;
    float node_count;
    ReadFromFile("Data.txt", &points, &node_count);
  
    cout << "Node count = " << node_count << endl;

    cout << "Data: " << endl;
    for (int i = 0; i < node_count; i++) {
        points[i].write();
        cout << " ";
    }

   cout << "\nPoint at which we calculate the value of the polynomial: x = " << x << endl;
   
   vector<float> coefficients;
   float val = NewtonInterpolation(points, x, &coefficients);
   cout << "Value of the polynomial in a given point: " << val << endl;

   cout << "Coefficients: " << endl;
   for (int i = 0; i < coefficients.size(); i++) {
       cout <<"b_" << i << " = " << coefficients[i] << endl;
   }

    return 0;
}