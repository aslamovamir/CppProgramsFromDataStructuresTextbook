#include <iostream>
#include <vector>



bool distinct(const std::vector<int> &reference_list) {

    bool distinct = true;

    //2 3 4 5 6
    for (int a = 0; a < reference_list.size(); a++) {
        if (a == reference_list.size() - 1) {
            break;
        }
        for (int b = a + 1; b < reference_list.size(); b++) {
            if (reference_list[a] == reference_list[b]) {
                distinct = false;
                break;
            }
        }
    }

    return distinct;
}

int main() {

    std::vector<int> my_list;
    std::cout<<"Enter a list of integers (enter -1 to stop the list): ";
    int entree;
    while (true) {
        std::cin>>entree;
        if (entree == -1) {
            break;
        }
        my_list.push_back(entree);
    }

    std::cout<<"\nPrinting the vector: ";
    for (int i = 0; i < my_list.size(); i++) {
        std::cout<<my_list[i]<<" ";
    }

    bool distinct_list = distinct(my_list);
    if (distinct_list) {
        std::cout<<"\nThe list contains distinct values.";
    } else {
        std::cout<<"\nThe list does not contain distinct values.";
    }

    return EXIT_SUCCESS;
}
