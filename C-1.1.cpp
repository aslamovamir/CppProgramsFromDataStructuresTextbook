#include <iostream>

void reverse(int array[], int size) {

    int reversed [size];
    int i, j;

    for (i = size - 1, j = 0; i >= 0 && j < size; i--, j++) {
        reversed[j] = array[i];
    }

    std::cout<<"\nHere is the reversed array: ";
    for (i = 0; i < size; i++) {
        std::cout<<reversed[i] << " ";
    }
}


int main () {

    int size;
    std::cout<<"Enter the size of the array: ";
    std::cin>>size;
    int array[size];
    std::cout<<"\nNow enter the array of integers of the entered length: ";
    for (int i = 0; i < size; i++) {
        std::cin>>array[i];
    }
    std::cout<<"\nYou have enterred the following array: ";
    for (int i = 0; i < size; i++) {
        std::cout<<array[i]<<" ";
    }

    reverse(array, size);

    return EXIT_SUCCESS;
}
