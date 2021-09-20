#ifndef CALCLIST_H
#define CALCLIST_H

#include "CalcListInterface.hpp"
#include <iostream> //CAN BE REMOVED
#include <sstream>
#include <string>
#include <iomanip>



// a node class
class CalcOperation {

    private:
        char operation;
        double operand;
        double prev_total; // will hold the total at the time of the current operation
        double curr_total; // will hold the total after the current operation
        int count; // will keep track of the operation's sequence

        // sentinals
        CalcOperation* prev;
        CalcOperation* next;

        // making the class CalcList friend will allow the list to access the nodes
        friend class CalcList;
};



// a linked list
class CalcList: public CalcListInterface {

    private:
        CalcOperation* header; // list sentinels
        CalcOperation* trailer;

    public:
        int ops_counter = 0; // this variable will keep track of the operations completed 
        CalcList(); // a constructor
        ~CalcList(); // a destructor
        bool empty() const; // to see if the list is empty or not
        void addOperation(const char &operation, const double &operand); // adds  a new node that represents an operation
        void removeOperation(CalcOperation *operation); // removes a node specified as the argument
        void removeFront(); // to remove from front of list, needed to "destroy" the calcList object

    public:
        double total() const;  // returns the static total_value
        void newOperation(const FUNCTIONS func, const double operand);
        void removeLastOperation(); 
        std::string toString(unsigned short precision) const; //prints all the nodes in a formatted string
};



#endif /* CALCLIST_H */
