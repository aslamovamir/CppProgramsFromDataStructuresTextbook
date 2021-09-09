#include <iostream>
#include <vector>

std::vector<double> product(const std::vector<double> &v1, const std::vector<double> &v2);

int main() {

    std::vector<double> v1;
    std::vector<double> v2;
    int size;
    double entree;
    std::cout<<"Enter the number of entrees you want to input for each vector: ";
    std::cin>>size;
    std::cout<<"\nEntrees for the first vector...\n";
    for (int i = 0; i < size; i++) {
        std::cout<<"Enter a number: ";
        std::cin>>entree;
        v1.push_back(entree);
    }
    std::cout<<"\nEntrees for the second vector...\n";
    for (int i = 0; i < size; i++) {
        std::cout<<"Enter a number: ";
        std::cin>>entree;
        v2.push_back(entree);
    }

    std::cout<<"\nHere is the first vector you have entered: ";
    for (int i = 0; i < v1.size(); i++) {
        std::cout<<v1[i]<<" ";
    }
    std::cout<<"\nHere is the second vector you have entered: ";
    for (int i = 0; i < v1.size(); i++) {
        std::cout<<v2[i]<<" ";
    }

    std::vector<double> returned = product(v1, v2);
    std::cout<<"\nHere's the element-by-element product list of the two vectors: ";
    for (int i = 0; i < returned.size(); i++) {
        std::cout<<returned[i]<<" ";
    }


    return 0;
}


std::vector<double> product(const std::vector<double> &v1, const std::vector<double> &v2) {

    std::vector<double> results;
  
    for (int i = 0; i < v1.size(); i++) {
        results.push_back(v1[i] * v2[i]);
    }

    return results;
}
