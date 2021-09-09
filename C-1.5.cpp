#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>



void shuffle(std::vector<int> &list) {

    std::vector<int> indeces_accouted;

    srand(time(0));
    int rand_index, temp_store;

    for (int i = 0; i < list.size(); i++) {
        rand_index = (rand() % 52) + 1;

        for (int j = 0; j < indeces_accouted.size(); j++) {
            if(rand_index == indeces_accouted[j]) {
                continue;
            }
        }

        indeces_accouted.push_back(rand_index);
        temp_store = list[rand_index];
        list[rand_index] = list[i];
        list[i] = temp_store;
    }
}


int main() {

    std::vector<int> set_52;
    int entree;
    std::cout<<"Enter the list of integers in the range of 1 to 52 (-1 to stop entrees): ";
    for (int i = 0; i < 52; i++) {
        std::cin>>entree;
        if (entree == -1) {
            break;
        } else {
            set_52.push_back(entree);
        }
    }

    // for (int i = 0; i < 52; i++) {
    //     set_52.push_back(i);
    // }



    std::cout<<"\nHere is the original list of integers: ";
    for (int i = 0; i < 52; i++) {
        std::cout<<set_52[i]<<" ";
    }

    shuffle(set_52);

    std::cout<<"\nHere is the shuffled list: ";
    for (int i = 0; i < 52; i++) {
        std::cout<<set_52[i]<<" ";
    }

    return 0;
}
