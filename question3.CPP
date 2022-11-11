// Kavya Sundaresan
//400307169


#include <iostream>
#include <math.h>
#include <string>
#include <cstdlib>
using namespace std;


class Point {
    public:
        Point(); // constructor with no arguments
        Point(double x1, double y1); //constructor that can set x and y member variables
        double getX(); //returns x coordinate
        double getY(); //returns y coordinate
        double distanceTo(const Point& otherP); //returns distance between 2 points
        friend istream& operator>>(istream& is, Point& P); //inputs x and y coordinates from user
        friend ostream& operator<<(ostream& os, const Point& P); //outputs x and y coordinates
        
    private:
        double x; // x and y coordinates of point
        double y;
};

class Polygon {
    public:
        Polygon(int v = 10); //constructor with argument that indicates number of points
        Polygon(int v1, Point* list); // constructor that receives number of vertices and an array of pointers
        ~Polygon(); // destructor
        double perimeter(); //function to calculate perimeter of shape
        friend ostream& operator<<(ostream& os, const Polygon& p); //inputs x and y coordinates of shape's vertices
        friend istream& operator>>(istream& is, Polygon& p); //outputs x and y coordinates of shape's vertices
    private:
        int num_vertices; //stores number of vertices
        Point* points = new Point[5]; //stores points

};

Point::Point() { //initializes member variables to 0;
    x = 0;
    y = 0;
}

Point::Point(double x1, double y1) { //assigns member variables values of arguments
    x = x1;
    y = y1;
}

ostream& operator<<(ostream& os, const Point& P) { //prints point in (x,y) format
    os << '(' << P.x << ',' << P.y << ')'<<endl;
    return os;
}

istream& operator>>(istream& is, Point& P) { //takes user input for a point's coordinates
    cout << "Please input the x coordinate and then the y coordinate in the format 'x y' without the quotation marks: " << endl;
    is >> P.x >> P.y;
    return is;
}

double Point::getX() { //returns x coordinate
    return x;
}

double Point::getY() { //returns y coordinate
    return y;
}

double Point::distanceTo(const Point& otherP) {
    int delta_x = x-otherP.x; //difference in x coordinates of two points
    int delta_y = y-otherP.y; //difference in y coordinates of two points
    int d = sqrt(pow(delta_x,2)+pow(delta_y,2)); // distance between 2 points
    return d;
}

Polygon::Polygon(int n) {
    num_vertices = n;
}

Polygon::Polygon(int v1, Point* list) { //assigns member variables the values of the arguments
    num_vertices = v1;
    points = list;
}
Polygon::~Polygon() { //deletes points array
    delete [] points;
}

double Polygon::perimeter() {
    int perimeter = 0;
    for (int i = 0; i < num_vertices-1; i++) { //calculates the distance between adjacent points in the shape
        perimeter += points[i].distanceTo(points[i+1]); //sums together the distances to calculate the perimeter
    }
    perimeter += points[0].distanceTo(points[num_vertices-1]); // calculates distance between last and first point in the shape
    return perimeter;
}

ostream& operator<<(ostream& os, const Polygon& p) {
    for (int i=0; i<p.num_vertices; i++) {
        os << 'P'<< p.points[i];
    }
    return os;
}

istream& operator>>(istream& is, Polygon& p) {
    for (int i=0; i<p.num_vertices; i++) {
        cout<< "Enter coordinate " << i+1 <<endl;
        is >> p.points[i];
        cout<<'\n'<<endl;
    }
    return is;    
}

int main() {

    Point p1; 
    std::cout << p1 << ", ";  

    Point p2(3, 9);
    std::cout << p2 << "\n";

    std::cout << p2.getX() << ", "; 
    std::cout << p2.getY() << "\n";

    
    Point* points_list = new Point[4];
    points_list[0] = Point(0, 0);
    points_list[1] = Point(0, 4);
    points_list[2] = Point(1, 4);
    points_list[3] = Point(1, 0);
    Polygon rectangle(4, points_list);
    cout << rectangle << "\n";
    
    cout << rectangle.perimeter() << ", "; 
    
    Polygon poly (4);
    cin >> poly;
    cout << poly << "\n";
    cout << poly.perimeter() << "\n";
    
    Point p10;
    cin >> p10;
    cout << p10 << "\n";

    return 0;
}