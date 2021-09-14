// Write a short C++ function that removes all the punctuation from a string storing a sentence. 
// For example, this operation would transform the string "Let’s try, Mike." to "Lets try Mike".

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Sentence {

    private:
        string orig_sentence;
        string modif_sentence;
        vector<char> list_char;

    public:
        Sentence(string input="Default"): orig_sentence(input) {
            modif_sentence = "";
            cout<<"\n\nObject created.";
        }
        ~Sentence() { cout<<"\n\nObject destroyed.\n"; list_char.clear(); cout<<"List cleared.\n\n"; };
        string getOrigSentence() { return orig_sentence; };
        string getModifSentence() { return modif_sentence; };
        void setOrigSentence(string input) { orig_sentence = input; };
        void removePunctuations();
        void printList();
};

void Sentence::removePunctuations() {

    int punct_list[] = {'\'', '.', '?', '"', '!', '(', ')', '[', ']', '/', ':', ';', ',', '-', '_', '{', '}'};
    int const punct_list_size = sizeof(punct_list)/sizeof(punct_list[0]);
    bool found = false;

    for (int i = 0; i < orig_sentence.length(); i++) {
        for (int j = 0; j < punct_list_size; j++) {
            if (orig_sentence[i] == punct_list[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            list_char.push_back(orig_sentence[i]);
        }
        found = false;
    }

    for (int i = 0; i < list_char.size(); i++) {
        modif_sentence += list_char[i];
    }
    this->setOrigSentence(modif_sentence);
}

void Sentence::printList() {

    for (int i = 0; i < list_char.size(); i++) {
        cout<<list_char[i]<<" ";
    }
    cout<<"\nSIZE: "<<list_char.size();
}



int main() {
    
    string input;
    cout<<"Plese, enter a sentence: ";
    getline(cin, input);
    cout<<"\nThanks, you have entered the following: "<<input;
    cout<<"\nThe length of your input: "<<input.length()<<endl;

    Sentence object(input);

    cout<<"\n\nHERE IS THE ORIGINAL SENTENCE NOW: "<<object.getOrigSentence();
    cout<<"\nHERE IS THE MODIFIED SENTENCE NOW: "<<object.getModifSentence();

    object.removePunctuations();
    cout<<"\n\nHERE IS THE ORIGINAL SENTENCE NOW: "<<object.getOrigSentence();
    cout<<"\nHERE IS THE MODIFIED SENTENCE NOW: "<<object.getModifSentence();


    return 0;
}
