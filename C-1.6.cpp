#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>



std::string make_word(const char stack[], const int size) {
    
    int rand_index;
    std::vector<int> indeces_accounted;
    std::string word = "";
    char list[size];

    for (int i = 0; i < size; i++) {

        rand_index = rand() % size;
        for (int j = 0; j < indeces_accounted.size(); j++) {
            if (rand_index == indeces_accounted[j]) {
                j = -1;
                rand_index = rand() % size;
            }          
        }
        indeces_accounted.push_back(rand_index);
        list[rand_index] = stack[i];
    }

    for (int i = 0; i < size; i++) {
        word+= list[i];
    }

    return word;
}


int main() {

    srand(time(0));

    int user_input_size;

    std::cout<<"Enter the number of characters in the set: ";
    std::cin>>user_input_size;
    char user_input[user_input_size];

    for (int i = 0; i < user_input_size; i++) {
        std::cout<<"Enter a character: ";
        std::cin>>user_input[i];
    }
    std::cout<<"\nPrinting the user input: ";
    for (int i = 0; i < user_input_size; i++) {
        std::cout<<user_input[i]<<" ";
    }

    std::string word_made;
    std::vector<std::string> word_combs;
    int total_num_combs = sizeof(user_input);
    bool word_ready = false;


    for (int i = total_num_combs - 1; i > 0; i--) {
        total_num_combs *= i;
    }

    std::cout<<"\nThe total number of combinations possible: "<<total_num_combs<<std::endl;

    for (int i = 0; i < total_num_combs; i++) {
        word_made = make_word(user_input, sizeof(user_input));

        for (int j = 0; j < word_combs.size(); j++) {
            if (word_made == word_combs[j]) {
                word_ready = true;
            }
        }

        if (word_ready == true) {
            while(word_ready == true) {
                word_ready = false;
                word_made = make_word(user_input, sizeof(user_input));
                for (int j = 0; j < word_combs.size(); j++) {
                    if (word_made == word_combs[j]) {
                        word_ready = true;
                    }
                }
            }
        }

        word_combs.push_back(word_made);
    }
    
    std::cout<<"\nPrinting all the possible combinations: ";
    for (int y = 0; y < word_combs.size(); y++) {
        std::cout<<word_combs[y]<<" ";
    }

    return 0;
}
