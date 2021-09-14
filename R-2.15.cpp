// Write a short C++ function that counts the number of vowels in a given character string.

#include <iostream>


class Word {

    private:
        int num_vowels;
        std::string str_word;
    public:
        static int count;

        Word (std::string string_argument ="Default"): 
            str_word(string_argument) {
                num_vowels = 0;
                count++;
            };
        ~Word() {
            std::cout<<"\n\nObject destroyed.\n";
        }
        static void getCount() { std::cout << "The number of word objects dealt with so far: " << count <<std::endl;};
        int getNumVowels () const { return num_vowels; };
        std::string getWord()const { return str_word; };
        int findNumVowels();

    int getNumVowels() {

        for (int i = 0; i < str_word.length(); i++) {
            if (str_word[i] == 'a' || str_word[i] == 'i' || str_word[i] == 'e' || str_word[i] == 'o' || str_word[i] == 'u') {
                num_vowels++;
            }
        }

        return num_vowels;
    }

};

int Word::count = 0;

int main() {

    std::string word;
    std::cout<<"Enter a word: ";
    std::cin>>word;
    std::cout<<"\nThanks, the word you have entered: "<<word<<std::endl;

    Word input(word);
    std::cout<<"The number of vowels in this word: "<<input.getNumVowels()<<std::endl;

    Word::getCount();

    return EXIT_SUCCESS;
}
