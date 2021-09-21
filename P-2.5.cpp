// Write a C++ program that has a Polygon interface that has abstract functions, area(), 
// and perimeter(). Implement classes for Triangle, Quadrilateral, Pentagon, Hexagon, 
// and Octagon, which implement this interface, with the obvious meanings for the area()
// and perimeter() functions. Also implement classes, IsoscelesTriangle, EquilateralTriangle, 
// Rectangle, and Square, which have the appropriate inheritance relationships. Finally, 
// write a simple user interface that allows users to create polygons of the various types, 
// input their geometric dimensions, and then output their area and perimeter. For extra effort,
// allow users to input polygons by specifying their vertex coordinates and be able to test if 
// two such polygons are similar.

#include <iostream>
#include <cmath>
using namespace std;


class Polygon {
    public:
        virtual double area() const = 0;
        virtual double perimeter() const= 0;
        virtual void printMeaseres() {
            cout<<"Area: "<<this->area()<<endl;
            cout<<"Perimeter: "<<this->perimeter()<<endl;
        }
};





class Triangle: public Polygon {
    private:
        double a, b, c;
    public:
        Triangle(double a = 0, double b = 0, double c = 0): a(a), b(b), c(c) {}
        ~Triangle() {}
        virtual double area() const { 
            // Heron's formula of triangle area
            // s = (a + b + c)/2 
            // area = sqrt(s(s-a)(s-b)(s-c))
            double s = (this->a + this->b + this->c)/2;
            double area = sqrt(s * (s - this->a) * (s - this->b) * (s - this->c));
            return area;
        }
        virtual double perimeter() const { return (this->a + this->b + this->c); };
};

class Quadrilateral: public Polygon {
    private: 
        double a, b, c, d;
    public:
        Quadrilateral(double a = 0, double b = 0, double c = 0, double d = 0): a(a), b(b), c(c), d(d) {};
        ~Quadrilateral() {}
        virtual double area() const {
            // Brahmagupta's Formula
            // s = (a + b + c + d)/2
            // area = sqrt((s-a)(s-b)(s-c)(s-d))
            double s = (this->a + this->b + this->c + this->d)/2;
            double area = sqrt((s - this->a)*(s - this->b)*(s - this->c)*(s - this->d));
            return area;
        }
        virtual double perimeter() const { return(this->a + this->b + this->c + this->d); };
};

// regular pentagon blueprint
class Pentagon: public Polygon {
    private:
        double a;
    public:
        Pentagon(double a = 0): a(a) {};
        ~Pentagon() {}
        double area() const {
            double area = (pow(a, 2.0)/4) * (sqrt(5*(5 + 2*sqrt(5))));
            return area;
        }
        double perimeter() const {
            return (5 * this->a);
        }
};

// regular hexagon blueprint
class Hexagon: public Polygon {
    private:
        double a;
    public :
        Hexagon(double a = 0): a(a) {};
        ~Hexagon() {}
        double area() const {
            double area = (3*sqrt(3)/2)*(pow(a, 2.0));
            return area;
        }
        double perimeter() const {
            return (6*this->a);
        }
};

// regular octagon blueprint
class Octagon: public Polygon {
    private:
        double a;
    public:
        Octagon(double a = 0): a(a) {};
        ~Octagon() {};
        double area() const {
            double area = 2 * (1 + sqrt(2)) * pow(this->a, 2.0);
            return area;
        }
        double perimeter() const {
            return (8 * this->a);
        }
};





class IsoscelesTriangle: public Triangle {
    private:
        double a, b;
    public: 
        IsoscelesTriangle (double a = 0, double b = 0): a(a), b(b) {}
        ~IsoscelesTriangle() {}
        virtual double area() const { // we add dynamacy from parent
            double area = (sqrt(pow(this->a, 2.0) - pow(this->b, 2.0)/4)*this->b)/2;
            return area;
        }
        virtual double perimeter() const {
            return (2*this->a + this->b);
        }
};

class EquilateralTriangle: public Triangle {
    private:
        double a;
    public: 
        EquilateralTriangle (double a = 0): a(a) {}
        ~EquilateralTriangle() {}
        virtual double area() const {
            double area = sqrt(3)/4*pow(this->a, 2.0);
            return area;
        }
        virtual double perimeter() const {
            return (3*this->a);
        }
};


class Rectangle: public Quadrilateral {
    private:
        double a, b;
    public: 
        Rectangle(double a, double b): a(a), b(b) {}
        ~Rectangle(){}
        virtual double area() const {
            double area = this->a * this->b;
            return area;
        }
        virtual double perimeter() const {
            return(2*this->a + 2*this->b);
        }
};

class Square: public Quadrilateral {
    private:
        double a;
    public:
        Square(double a = 0): a(a) {}
        ~Square() {}
        virtual double area() const {
            double area = pow(this->a, 2.0);
            return area;
        }
        virtual double perimeter() const {
            return (4*this->a);
        }
};






int main() {

    double a, b, c, d;

    cout<<"Enter the sides of a regular triangle: ";
    cin>>a>>b>>c;
    Triangle regular_triangle(a, b, c);
    regular_triangle.printMeaseres();

    cout<<"\nEnter the sides of a quadrilateral: ";
    cin>>a>>b>>c>>d;
    Quadrilateral quadrilateral(a, b, c, d);
    quadrilateral.printMeaseres();

    cout<<"Enter one side of the pentagon: ";
    cin>>a;
    Pentagon pentagon(a);
    pentagon.printMeaseres();

    cout<<"Enter one side of a hexagon: ";
    cin>>a;
    Hexagon hexagon(a);
    hexagon.printMeaseres();

    cout<<"Enter one side of an octagon: ";
    cin>>a;
    Octagon octagon(a);
    octagon.printMeaseres();

    cout<<"Enter the value of the sides equal to each other and then that of the third side of an isosceles triangle: ";
    cin>>a>>b;
    IsoscelesTriangle isos_triangle(a, b);
    isos_triangle.printMeaseres();

    cout<<"Enter the side of an equilateral triangle: ";
    cin>>a;
    EquilateralTriangle equil_triangle(a);
    equil_triangle.printMeaseres();

    cout<<"Enter the length and width of a rectangle: ";
    cin>>a>>b;
    Rectangle rectangle(a, b);
    rectangle.printMeaseres();

    cout<<"Enter the side of a square: ";
    cin>>a;
    Square square(a);
    square.printMeaseres();

    return EXIT_SUCCESS;
}
