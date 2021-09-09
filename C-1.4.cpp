#include <iostream>
#include <vector>


void print_odd(std::vector<int> list) {

    for (int i = 0; i < list.size(); i++) {
        if (list[i] % 2 != 0) {
            std::cout<<list[i]<<" ";
        }
    }
}


int main() {

    std::vector<int> my_list;
    int entree;

    std::cout<<"Enter the list of integers, and -1 to stop entrees: ";
    while(true) {
        std::cin>>entree;
        if (entree == -1) {
            break;
        } else {
            my_list.push_back(entree);
        }
    }
    std::cout<<"\nHere is the list of your entrees: ";
    for (int i = 0; i < my_list.size(); i++) {
        std::cout<<my_list[i]<<" ";
    }
    std::cout<<"\nPrinting the odd entree integers from the list...\n";
    print_odd(my_list);

    return 0;
}
