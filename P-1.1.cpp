
/*
    A common punishment for school children is to write out the same sen-
    tence multiple times. Write a C++ stand-alone program that will write 
    out the following sentence one hundred times: “I will always use object-
    oriented design.” Your program should number each of the sentences and it
    should “accidentally” make eight different random-looking typos at var- 
    ious points in the listing, so that it looks like a human typed it all by hand.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

int main() {

    
    //will not include a dot as to not "accidentally" make it a letter
    std::string sentence[] = {"I",  "will", "always", "use", "object-oriented", "design"};
    //number of words in the sentence
    int size = sizeof(sentence)/sizeof(sentence[0]);

    const char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                             'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 
                             'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};



    int rand_word_ind, rand_letter_ind, rand_alphabet_ind;
    std::vector<int> account_words;
    std::vector<int> account_letters;
    std::vector<std::string> changed_words_storage;//this vector will hold all the chnaged words for each cycle up to 8 typos
    std::vector<std::string> storage_comp;//this vector will hold all the orginal words that become changed
    bool word_met, letter_met, restart;
    std::string temp_store;
    std::vector<std::string> copy_of_sentence;
    srand(time(0));

    //we assume that the same word can have multiple types, there is a possibility that 
    //the same word can have all the letters misput, but given the randomness of the scenario, it is less likely

    //lets print the sentence 10  times first
    for (int b = 0; b < 100; b++) {
        
        //defaulting all citical variables and vectors for the new cycle
        for (int v = 0; v < size; v++) {
            copy_of_sentence.push_back(sentence[v]);
        }
        account_words.clear();
        account_letters.clear();
        changed_words_storage.clear();
        storage_comp.clear();

        //producing 8 typos
        //after 8 typos are produced, all the vectors and critical variables have to be turned to default
        for (int i = 0; i < 8; i++) {

            restart = true;

            while(restart == true) {

                word_met = false;
                letter_met = false;
                restart = false;
            
                rand_word_ind = rand() % size;
                //we can have the same word to have more than one typo, so we just push the word index into the vector
                //but we record if the same word has been already selected

                //if the chosen word is "I", we can skip because it is less reasonable to make a typo in "I"
                while(rand_word_ind == 0) {
                    rand_word_ind = rand() % size;
                }

                for (int l = 0; l < account_words.size(); l++) {
                    if (rand_word_ind == account_words[l]) {
                        word_met = true;
                    }
                }
                if (word_met == false) {
                    account_words.push_back(rand_word_ind);
                }
                //now we randomly choose a letter to have a typo, total must be 8
    
                rand_letter_ind = rand() % sentence[rand_word_ind].size();//the index of a letter to be replaced with another random letter
                //we check if the same combination of both words indeces and letter indeces are already inside the respective vectors
                for (int k = 0; k < account_letters.size(); k++) {
                    if (rand_letter_ind == account_letters[k]) {
                        letter_met = true;
                    }
                }
                if (letter_met == false) {
                    account_letters.push_back(rand_letter_ind);
                }
                //if both combos are already encountered we pick another letter for the same word
                if (word_met == true && letter_met == true) {
                    restart = true;
                }
            
        }

        //now we randomly replace the chosen letter of a chosen word with any random letter from the alphabet
        //no restriction on the replacement letter from the alphabet
        rand_alphabet_ind = rand() % (sizeof(alphabet) / sizeof(alphabet[0]));
        temp_store = copy_of_sentence[rand_word_ind];
        storage_comp.push_back(sentence[rand_word_ind]);
        temp_store[rand_letter_ind] = alphabet[rand_alphabet_ind];
        copy_of_sentence[rand_word_ind] = temp_store;

        //we store the changed words into the temp_storage vector
        //after the 8 words have been assigned a misput letter, all the vectors have to be cleared
        changed_words_storage.push_back(temp_store);
    }

    std::cout<<"\n\n";
    for (int y = 0; y < copy_of_sentence.size(); y++) {
        std::cout<<copy_of_sentence[y]<<" ";
    }
    copy_of_sentence.clear();
}

  return EXIT_SUCCESS;
}  
