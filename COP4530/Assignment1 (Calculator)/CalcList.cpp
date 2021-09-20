#include "CalcList.hpp"


CalcList::CalcList() {
    header = new CalcOperation;
    trailer = new CalcOperation;
    
    //we initialize the two nodes' attributes to default values
    header->curr_total = 0.0;
    header->prev_total = 0.0;
    header->operand = 0.0;
    header->operation = '+';
    header->count = 0;

    trailer->curr_total = 0.0;
    trailer->prev_total = 0.0;
    trailer->operand = 0.0;
    trailer->operation = '+';
    trailer->count = 0;

    //making them point to each other will make sure the 
    //list automatically doubly linked each time the list object is created
    header->next = trailer;
    trailer->prev = header;
}

CalcList::~CalcList() {

    //we will keep removing the node next to the header node 
    //until the header is pointing to the trailer, in which case the list is empty
    while(!empty()) {   
        removeFront();
    }

    //we will delete the two linker nodes at the end, 
    //thus empletely destroying the list object
    delete header;
    delete trailer;
}

bool CalcList::empty() const {
    return (header->next == trailer);
}

void CalcList::addOperation(const char &operation, const double &operand) {

    // we also increment the counter to keep track of total operations completed
    ops_counter++;

    CalcOperation *new_op = new CalcOperation; 
    new_op->operation = operation; 
    new_op->operand = operand;
    new_op->prev_total = trailer->prev->curr_total;
    new_op->count = ops_counter;

    if (operation == '+') {
        new_op->curr_total = new_op->prev_total + operand;
    } else if (operation == '-') {
       new_op->curr_total = new_op->prev_total - operand;
    } else if (operation == '*') {
        new_op->curr_total = new_op->prev_total * operand;
    } else if (operation == '/') {
        new_op->curr_total = new_op->prev_total / operand;
    }
    
    new_op->next = trailer; //we add the new operation to the end of the list
    new_op->prev = trailer->prev;
    trailer->prev->next = new_op;
    trailer->prev = new_op;
}

void CalcList::removeOperation(CalcOperation *operation) {
    CalcOperation *temp_prev = operation->prev;
    CalcOperation *temp_next = operation->next;

    //we will decrement the counter to accomodate the 
    //track of operations completed so far
    ops_counter--;

    temp_prev->next = temp_next;
    temp_next->prev = temp_prev;
    delete operation;
}

void CalcList::removeFront() {
    removeOperation(header->next);
}

void CalcList::removeLastOperation() {
        if (trailer->prev == header) {
            throw -2;
        }
        removeOperation(trailer->prev);
}

double CalcList::total() const {
    return trailer->prev->curr_total;
}

void CalcList::newOperation(const FUNCTIONS func, const double operand) {

    char char_op = '-';

        // if the division operator comes along with the zero operand 
        // the function throws, skipping the code below the if block
        if (func == DIVISION && operand == 0.0) {
            throw -1;
        }

        if (func == ADDITION) {
            char_op = '+';
        } else if (func == SUBTRACTION) {
            char_op = '-';
        } else if (func == MULTIPLICATION) {
            char_op = '*';
        } else if (func == DIVISION) {
            char_op = '/';
        }


        // operations are implemented
        if (char_op == '+') {
            addOperation(char_op, operand);
        } else if (char_op == '-') {
            addOperation(char_op, operand);
        } else if (char_op == '*') {
            addOperation(char_op, operand);
        } else if (char_op == '/') {
            addOperation(char_op, operand);
        }
}

std::string CalcList::toString(unsigned short precision) const {
    
    //a temp pointer to loop through the list
    CalcOperation *temp = new CalcOperation;
    temp = trailer->prev;
    int step = ops_counter;
    //stream object
    std::stringstream strStream;
    strStream.precision(precision);
    std::string operation_str = "";

    while (step != 0) {

        strStream << step<<": ";
        strStream << std::fixed << temp->prev_total;

        switch (temp->operation) {
            case '+':
                operation_str = "+"; break;
            case '-':
                operation_str = "-"; break;
            case '*':
                operation_str = "*"; break;
            case '/':
                operation_str = "/"; break;
        }

        strStream << operation_str;
        strStream << temp->operand;
        strStream << "=";
        strStream << temp->curr_total;
        strStream << std::endl;

        temp = temp->prev;
        step--;
    } 
    
    return strStream.str();
}
