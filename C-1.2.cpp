#include <iostream>

bool even_pair(int array[], int size);

int main() {

    int size;

    std::cout<<"Enter the size of the array: ";
    std::cin>>size;
    int array[size];
    std::cout<<"\nEnter the values for the array: ";
    for (int i = 0; i < size; i++) {
        std::cin>>array[i];
    }
    std::cout<<"You have entered the following array: ";
    for (int i = 0; i < size; i++) {
        std::cout<<array[i]<<" ";
    }

    if (even_pair(array, size)) {
        std::cout<<"\nThere is at least one pair of values with an even product in the array."<<std::endl;
    } else {
        std::cout<<"\nThere is no any pair of values in the array whose prodcut is even."<<std::endl;
    }

    return 0;
}

bool even_pair(int array[], int size) {

    //array: 2 3 4 4 5 9
    bool even = false;

    for (int i = 0; i < size; i++) {
        if (i == size - 1) {
            break;
        }
        for (int j = i + 1; j < size; j++) {
            if ((array[i] * array[j]) % 2 == 0) {
                even = true;
                break;
            }
        }
    }
    return even;
}
