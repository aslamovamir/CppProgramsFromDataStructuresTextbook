#include <iostream>


int itself(int times, int &result) {
    
    if(times == 1) {
        return result;
    } else {
        result *= 2;
        return itself(times - 1, result);
    }
}


int main() {

    int i;
    std::cout<<"Enter the value of the i: ";
    std::cin>>i;
    int result = 2;
    result = itself(i, result);

    std::cout<<"\nThe result is: "<<result;

    return 0;
}
