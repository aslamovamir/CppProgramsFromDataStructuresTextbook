// Write a short C++ program that creates a Pair class that can store two objects 
// declared as generic types. Demonstrate this program by creating and printing 
// Pair objects that contain five different kinds of pairs, such as <int,string> and <float,long>.


#include <iostream>
using namespace std;


template <class T, class Y>
class Pair {
    private: 
        T object1;
        Y object2;
    public:
        Pair(T ob1, Y ob2) : object1(ob1), object2(ob2) {
            cout<<"\nObject created!"<<endl;
        }
        void printSum() { cout<<"THE SUM OF THE TWO OBJECTS: "<<object1 + object2<<endl; };
        void printthem() { cout<<"Here are the two objects of different types: "<<object1<<" "<<object2<<endl;};
};


int main() {

    Pair <int, int> object1(2, 3);
    object1.printSum();

    Pair <float, long> object2(2.3, 23000000);
    object2.printSum();

    Pair <string, int> object3("apple", 23);
    object3.printthem();

    Pair <string, char> object4("pineapple", 'a');
    object4.printthem(); 
 

    return EXIT_SUCCESS;
}
