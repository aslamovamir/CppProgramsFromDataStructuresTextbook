\\ Write a C++ program that inputs a document and then outputs a bar-chart
\\ plot of the frequencies of each alphabet character that appears in that doc- ument.



#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class file {
    //  a b c d e f g h i j k l m n o p q r s t u v w x y z
    private:
        char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
        int indexing[26] = {0};
    public:
        file() {};
        ~file() {};
        void parse_line(string line) {
            for (int i = 0; i < line.size(); i++) {
                if (line[i] == ' ') {
                    continue;
                } else {
                    for (int j = 0; j < 26; j++) {
                        if (this->alphabet[j] == line[i]) {
                            this->indexing[j]++; 
                        }
                    }
                }
            }
        }
        void report() {
            for (int i = 0; i < 26; i++) {
                cout<<"\nChar: "<<this->alphabet[i]<<"\nCount: "<<this->indexing[i]<<endl;
            }
        }
};


int main (){

    file file_obj;
    ifstream myfile;
    string file_name;
    cout<<"Enter the name of the file: ";
    cin>>file_name;


    myfile.open(file_name);
    std::string myline;
    if ( myfile.is_open() ) {
    while ( myfile ) { // equivalent to myfile.good()
        getline (myfile, myline);
        file_obj.parse_line(myline);
    }   
    }  else {
    cout << "Couldn't open file\n";
    }

    file_obj.report();

    return 0;   
}
