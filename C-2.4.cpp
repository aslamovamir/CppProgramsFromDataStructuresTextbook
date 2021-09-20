// Design a class Line that implements a line, which is represented by the formula y = ax + b.
// Your class should store a and b as double member variables. Write a member function intersect(l)
// that returns the x coordinate at which this line intersects line l. If the two lines are parallel, 
// then your function should throw an exception Parallel. Write a C++ program that creates a number of 
// Line objects and tests each pair for intersection. Your program should print an appropriate error message for parallel lines.


#include <iostream>


class Line {

    private:
        double a, b;
    public:
        Line(double a = 0, double b = 0) : a(a), b(b) {};
        
        double intersect(Line l) {
            // y = ax1 + b1 // y = ax2 + b2 // 
            try {
                if (this->a == l.a) {
                    throw 0;
                }
                double dif_a, dif_b;
                dif_a = this->a - l.a;
                dif_b = l.b - this->b;

                return (dif_b / dif_a);

            } catch (int error) {
                std::cout<<"\nError!"<<std::endl;
            }
        }
        void printLine() {
        
            if (this->b > 0 && this->a != 0) {
                std::cout<<"Line: y = "<<this->a<<"x + "<<this->b<<std::endl;
            } else if (this->b == 0 && this->a != 0) {
                std::cout<<"Line: y = "<<this->a<<"x"<<std::endl;
            } else if (this->b < 0 && this->a != 0) {
                std::cout<<"Line: y = "<<this->a<<"x "<<this->b<<std::endl;
            } else if (this->b != 0 && this->a == 0) {
                std::cout<<"Line: y = "<<this->b<<std::endl;
            } else if (this->b == 0 && this->a == 0) {
                std::cout<<"Line: y = 0"<<std::endl;
            }
        }
};





int main() {

    double a, b;

    std::cout<<"Enter the x and y coordinates of teh first line: ";
    std::cin>>a>>b;
    Line line1(a, b);

    std::cout<<"\nNow enter the x and y coordinates of the second line: ";
    std::cin>>a>>b;
    Line line2(a, b);

    std::cout<<"\nPrinting the lines you have entered: "<<std::endl;
    line1.printLine();
    line2.printLine();

    std::cout<<"Line 2 interset line 1 at x: "<<line1.intersect(line2);

    return EXIT_SUCCESS;
}
