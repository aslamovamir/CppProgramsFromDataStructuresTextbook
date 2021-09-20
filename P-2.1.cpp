// Write a C++ program that can take a positive integer greater than 2 as input 
// and write out the number of times one must repeatedly divide this number by 
// 2 before getting a value less than 2.

#include <iostream>
using namespace std;

int div_num(double input);

int main() {

    double input;
    cout<<"Enter a number greater than 2: ";
    cin>>input;
    if (input <= 2) {
        while (input <= 2)  {
            cout<<"\nError! Enter a number greater than 2: ";
            cin>>input;
        }
    }

    cout<<"The number of times you can divide the number by 2 before it gets less than 2 is: "
            <<div_num(input)<<endl;

    return EXIT_SUCCESS;
}

int div_num(double input) {
    int div_ind = 0;
    while (input >= 2) {
        input /= 2;
        div_ind++;
    } div_ind--;
    return div_ind;
}
