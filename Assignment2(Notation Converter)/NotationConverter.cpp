#include "NotationConverter.hpp"

//Definitions for the doubly-linked list
//constructor for the list
DoubleList::DoubleList() {
    header = new Element;
    trailer = new Element;
    
    //REMOVE
    // Element *test = new Element;
    // test->element = 'T';
    


    header->element = '+';
    trailer->element = '-';

    header->next = trailer;
    trailer->prev = header;

    //REMOVE
    // test->next = header->next;
    // test->prev = header;
    // header->next->prev = test;
    // header->next = test;
}

//destructor for the list
DoubleList::~DoubleList() {
    while(!empty_list()) {
        removeFrontList();
    }

    delete header;
    delete trailer;
}

bool DoubleList::empty_list() const {
    return (header->next == trailer);
}

const char &DoubleList::front_item() const {
    return header->next->element;
}

const char &DoubleList::back_item() const {
    return trailer->prev->element;
}

void DoubleList::addFrontList(const char &e) {
    Element *new_el = new Element;
    new_el->element = e;

    new_el->next = header->next;
    new_el->prev = header;
    header->next->prev = new_el;
    header->next = new_el;
}

void DoubleList::addBackList(const char &e) {
    Element *new_el = new Element;
    new_el->element = e;

    new_el->next = trailer;
    new_el->prev = trailer->prev;
    trailer->prev->next = new_el;
    trailer->prev = new_el;
}

const char &DoubleList::removeItem(Element *node) {
    Element *temp_prev = node->prev;
    Element *temp_next = node->next;

    temp_prev->next = temp_next;
    temp_next->prev = temp_prev;
    
    Element *temp = node;

    delete node;

    return temp->element;
}

const char &DoubleList::removeFrontList() {
    return removeItem(header->next);
}

const char &DoubleList::removeBackList() {
    // if (trailer->next == header) {
    //     throw "List Empty!";
    // }
    return removeItem(trailer->prev);
}

void DoubleList::printItems() {
    Element *iterator = new Element;
    iterator = header->next;

    while (iterator != trailer) {
        cout<<""<<iterator->element;
        iterator = iterator->next;
    }
    cout<<"\n";
}


//Defintions for the deque
//constructor
LinkedDeque::LinkedDeque(): list(), deque_size(0) {} //initializations of member data

//returns the current size of the deque
int LinkedDeque::size() const {
    return deque_size;
}

//evaluates if the deque is empty
bool LinkedDeque::empty() const {
    return deque_size == 0;
}

//returning the element at the front of the deque
const char &LinkedDeque::front() const {
    if (empty()) {
        throw "Deque Empty!";
    }
    return list.front_item();
}

//returning the element at the back of the deque
const char &LinkedDeque::back() const {
    if (empty()) {
        throw ("Deque Empty!");
    }
    return list.back_item();
}

//inserting to the front of the deque
void LinkedDeque::insertFront(const char &e) {
    list.addFrontList(e);
    deque_size++; //increment the size of the deque
}

//inserting to the back of the deque
void LinkedDeque::insertBack(const char &e) {
    deque_size++;
    list.addBackList(e);
}

//removing from the front of the deque
const char &LinkedDeque::removeFront() {
    if (empty()) {
        throw ("Deque Empty!");
    }
    deque_size--;
    return list.removeFrontList();
}

//removing from the back of the deque
const char &LinkedDeque::removeBack()  {
    if (empty()) {
        throw ("Deque Empty!");
    }
    deque_size--;
    return list.removeBackList();
}

void LinkedDeque::printDeque() {
    list.printItems();
}


//Definitions for the NotationConverter
//constructor
//it will cause the call of the constructor of the deque, and set original value to default
NotationConverter::NotationConverter(): dequeConverted(), stackOperators(), dequeOriginal() {}

//CAN BE REMOVED!!!
//printer method will cause the call of the printer method of the deques
void NotationConverter::Printer() {
    cout<<"\nPrinting the orginal notation deque: ";
    dequeOriginal.printDeque();
    cout<<"\nPrinting the operators stack:";
    stackOperators.printDeque();
    cout<<"\nPrinting the converted deque: ";
    dequeConverted.printDeque();
}


//postfix notation to infix notation
string NotationConverter::postfixToInfix(string inStr) {
    
    char iterat;
    
    //first we will collect the original notation in a neat form in a seperate stack, originalNotation
    //a local variable "sizeOriginal" will help in managing the originalNotation deque, and "sizeOperators" 
    //will do so for the stackOperators
    int sizeOriginal = 0;
    int sizeOperators = 0;
    for (unsigned int i = 0; i < inStr.length(); i++) {
        iterat = inStr[i];
        //if the character is among lowercase or uppercase letters
        if ((iterat >= 'A' && iterat <= 'Z') || (iterat >= 'a' && iterat <= 'z')) {
            dequeOriginal.insertBack(iterat);
            sizeOriginal++;
        } else if (iterat == '(' || iterat == ')' || iterat == '+' || iterat == '-' || iterat == '*' || iterat == '/') {
            dequeOriginal.insertBack(iterat);
            sizeOriginal++;
            sizeOperators++;
        } else if (iterat == ' ') { continue; } 
        else {
            cout<<"\nINVALID NOTATION!!!\n"; //MUST THROW AN ERROR
        }
    }

    //In this type of conversion we are less concerned about the precedence rules of
    //operations but are concerned about the role of parantheses
    //In this implementation we will stackOperators as a general stack to store 
    //our elements, rearrange them, and overall manage them with operators
    //The dequeConverted will serve as a temporary container (stack) that will
    //temporarily store elements from the stack, so stack can manage the elements
    //one by one, like inserting parantheses wherever needed


    //Generally we go through elements from the dequeOriginal one element at a 
    //time: if we encounter an operator, we simply push it into the temporary container, 
    //dequeConverted, and if we encounter an operand, we pop 2 elements from the stack,
    //enque (add to the front) in the dequeConverted, put necessary parantheses and pop the 
    //two elements back from the dequeConverted

    int trackStackSize = 0;
    char holder;
    char manager;
    bool met_inner_paranthesis = false;
    for (int i = 0; i < sizeOriginal; i++) {

        //cout<<"\nCYCLE";

        holder = dequeOriginal.removeFront();
        //cout<<"\nHOLDER: "<<holder;
        
        //if the holder value is among alphabetic letters, the holder holds an operand
        //we simply push it into the stack
        if ((holder >= 'A' && holder <= 'Z') || (holder >= 'a' && holder <= 'z')) {
            //cout<<"\nINSERTING THIS INTO THE STACK: "<<holder;
            stackOperators.insertBack(holder);
            trackStackSize++;
        }
        //else the holder encountered an operation: we turn to the stack, pop two elements from there,
        //and add to the front of the dequeConverted
        else {
            //cout<<"\nHOLDER IN ELSE BLOCK: "<<holder<<endl;
            trackStackSize++; //???? DO WE INCREMENT THE TRACK STACK SIZE?
            manager = stackOperators.removeBack();
            //cout<<"\n\nMANAGER HERE: "<<manager;
            //we check if the element we have got from the stack is a closed paranthesis
            //if we did, we will keep pulling elements until we encounter its paired open
            //paranthesis

            if (manager == ')') {
                dequeConverted.insertFront(manager);
                while(manager != '(') {
                    manager = stackOperators.removeBack();
                    //we check for any other inner parantheses
                    //if we encounter another closed paranthesis, 
                    //we make the bool variable true until we ecounter its pair
                    if (manager == ')') {
                        met_inner_paranthesis = true;
                        while(met_inner_paranthesis == true) {
                            dequeConverted.insertFront(manager);
                            manager = stackOperators.removeBack();
                            if (manager == '(') {
                                met_inner_paranthesis = false;
                                dequeConverted.insertFront(manager);
                                manager = stackOperators.removeBack();
                                if(manager == '(') {
                                    dequeConverted.insertFront(manager);
                                } else {
                                    stackOperators.insertBack(manager);
                                }
                            }
                        }
                    } else {
                        dequeConverted.insertFront(manager);
                    }
                }
                //assuming the current value of the manager is '(' after the loop
                //dequeConverted.insertFront(manager);
                manager = stackOperators.removeBack();
                if (manager == ')') {
                    dequeConverted.insertFront(manager);
                    while(manager != '(') {
                        manager = stackOperators.removeBack();
                        if (manager == ')') {
                            met_inner_paranthesis = true;
                            while(met_inner_paranthesis == true) {
                                dequeConverted.insertFront(manager);
                                manager = stackOperators.removeBack();
                                if (manager == '(') {
                                    met_inner_paranthesis = false;
                                    dequeConverted.insertFront(manager);
                                    manager = stackOperators.removeBack();
                                    if(manager == '(') {
                                        dequeConverted.insertFront(manager);
                                    } else {
                                        stackOperators.insertBack(manager);
                                    }
                                }
                            }
                        } else {
                            dequeConverted.insertFront(manager);
                        }
                    }
                } else {
                    dequeConverted.insertFront(manager);
                }
            } else {
                dequeConverted.insertFront(manager);
                //we take the seocond operand from the stack
                manager = stackOperators.removeBack();
                //we check if the second operand is also enclosed into the parantheses
                if (manager == ')') {
                    dequeConverted.insertFront(manager);
                    while(manager != '(') {
                        manager = stackOperators.removeBack();
                        //we check for any additional parantheses
                        if (manager == ')') {
                            met_inner_paranthesis = true;
                            while(met_inner_paranthesis == true) {
                                dequeConverted.insertFront(manager);
                                manager = stackOperators.removeBack();
                                if (manager == '(') {
                                    met_inner_paranthesis = false;
                                    dequeConverted.insertFront(manager);
                                    manager = stackOperators.removeBack();
                                    if (manager == '(') {
                                        dequeConverted.insertFront(manager);
                                    } else {
                                        stackOperators.insertBack(manager);
                                    }
                                }   
                            }
                        } else {
                            dequeConverted.insertFront(manager);
                        }
                    }
                    //dequeConverted.insertFront(manager);
                } else {
                    dequeConverted.insertFront(manager);
                }
            }

            //now we add an open paranthesis to the stack
            stackOperators.insertBack('(');
            trackStackSize++;

            //now we push the two operands back from the dequeConverted
            //first we take one element
            //we need to check if we are pulling an open paranthesis from the dequeConverted
            //in this case, we will keep pulling until we encounter its paired closed paranthesis
            manager = dequeConverted.removeFront();
            //cout<<"\n\n\nMANAGER FROM THE DEQUECONVERTED: "<<manager<<endl;
            if (manager == '(') {
                stackOperators.insertBack(manager);
                while(manager != ')') {                    
                    manager = dequeConverted.removeFront();
                    //we check for any other inner parantheses
                    //if we encounter another closed paranthesis, 
                    //we make the bool variable true until we ecounter its pair
                    if (manager == '(') {
                        met_inner_paranthesis = true;
                        while(met_inner_paranthesis == true) {
                            stackOperators.insertBack(manager);
                            manager = dequeConverted.removeFront();
                            if (manager == ')') {
                                met_inner_paranthesis = false;
                                stackOperators.insertBack(manager);
                                manager = dequeConverted.removeFront();
                                if(manager == '(') {
                                    dequeConverted.insertFront(manager);
                                } else {
                                    stackOperators.insertBack(manager);
                                }
                            }
                        }
                    } else {
                        stackOperators.insertBack(manager);
                    }
                }
                //assuming the current value of the manager is ')' after the loop
                //stackOperators.insertBack(manager);
            } else {
                stackOperators.insertBack(manager);
            }
            //now we insert the operation, which is holder at this point, in between
            stackOperators.insertBack(holder);
            //now we can insert the second operand
            //again we check if the element we are pulling is an open paranthesis, 
            //in which case will will keep pulling until we encounter its paired closed 
            //paranthesis
            manager = dequeConverted.removeFront();

            if (manager == '(') {
                stackOperators.insertBack(manager);
                while(manager != ')') {
                    manager = dequeConverted.removeFront();
                    //we check for any other inner parantheses
                    //if we encounter another closed paranthesis, 
                    //we make the bool variable true until we ecounter its pair
                    if (manager == '(') {
                        met_inner_paranthesis = true;
                        while(met_inner_paranthesis == true) {
                            stackOperators.insertBack(manager);
                            manager = dequeConverted.removeFront();
                            if (manager == ')') {
                                met_inner_paranthesis = false;
                                stackOperators.insertBack(manager);
                                manager = dequeConverted.removeFront();
                                if(manager == ')') {
                                    stackOperators.insertBack(manager);
                                } else {
                                    stackOperators.insertBack(manager);
                                }
                            }
                        }
                    } else {
                        stackOperators.insertBack(manager);
                    }
                }
                //assuming the current value of the manager is ')' after the loop
                //stackOperators.insertBack(manager);
            } else {
                stackOperators.insertBack(manager);
            }

            //now we add the closing paranthesis to complete a new operand in the stack
            stackOperators.insertBack(')');
            trackStackSize++;  
        }
    }

    string postfix_to_infix;

    for (int i = 0; i < trackStackSize; i++) {
        cout<<stackOperators.removeFront();
    }

    string valid = "";
    char el;
    //now we put the necessary spaces between the elements
    for (int i = 0; i < trackStackSize; i++) {
        el = postfix_to_infix[i];
        valid += el;
        if (el == '(') {
            while(el == '(') {
                i++;
                el = postfix_to_infix[i];
                if (el != '(') {
                    valid += " ";
                }
                valid += el;
            }
        } else if (el == ')') {
            while(el == ')') {
                i++;
                el = postfix_to_infix[i];
                if (el != ')') {
                    valid += " ";
                }
                valid += el;
            }
        }
        valid += " ";
    }


    return valid;
}


//postfix notation to prefix nottion
string NotationConverter::postfixToPrefix(string inStr) {
    //we can first convert the expression to infix and then from infix to prefix
    string postfix_to_infix = postfixToInfix(inStr);
    string infix_to_prefix = infixToPrefix(postfix_to_infix);

    string valid = "";
    char el;
    //now we put the necessary spaces between the elements
    for (unsigned int i = 0; i < infix_to_prefix.length(); i++) {
        el = infix_to_prefix[i];
        valid += el;
        if (el == '(') {
            while(el == '(') {
                i++;
                el = infix_to_prefix[i];
                if (el != '(') {
                    valid += " ";
                }
                valid += el;
            }
        } else if (el == ')') {
            while(el == ')') {
                i++;
                el = infix_to_prefix[i];
                if (el != ')') {
                    valid += " ";
                }
                valid += el;
            }
        }
        valid += " ";
    }


    return valid;
}


//infix notation to postfix notation
string NotationConverter::infixToPostfix(string inStr) {

    char iterat;
    
    //first we will collect the original notation in a neat form in a seperate stack, originalNotation
    //a local variable "sizeOriginal" will help in managing the originalNotation deque, and "sizeOperators" 
    //will do so for the stackOperators
    int sizeOriginal = 0;
    int sizeOperators = 0;
    for (unsigned int i = 0; i < inStr.length(); i++) {
        iterat = inStr[i];
        //if the character is among lowercase or uppercase letters
        if ((iterat >= 'A' && iterat <= 'Z') || (iterat >= 'a' && iterat <= 'z')) {
            dequeOriginal.insertBack(iterat);
            sizeOriginal++;
        } else if (iterat == '(' || iterat == ')' || iterat == '+' || iterat == '-' || iterat == '*' || iterat == '/') {
            dequeOriginal.insertBack(iterat);
            sizeOriginal++;
            sizeOperators++;
        } else if (iterat == ' ') { continue; } 
        else {
            cout<<"\nINVALID NOTATION!!!\n"; //MUST THROW AN ERROR
        }
    }




    //We will pop the operators from the dequeOriginal into the stackOperators, and operands into the dequeConverted
    //if there are multiple operators in the operatorsStack, the operator on top will be popped 
    //and pushed into the dequeConverted,according to precedence rules of operators
    //Rules of Operators:
    //1st '(' or ')'
    //2nd '*' or '/'
    //3rd '+' or '-'
    //if we encounter a closed paranthesis, we will keep poping the operators form the stackOperators
    //until we encounter an open paranthesis in the stackOperators
    char holder;
    char stackItem;


    int trackSizeConverted = 0;
    int trackSizeOper = 0;

    //because we already took care of invalid characters, we can assume all charactersother than 
    //operators are variables of the expression
    for (int i = 0; i < sizeOriginal; i++) {
        holder = dequeOriginal.removeFront();
        

        //if not an operator, then a variables to be pushed into the dequeConverter directly
        if (holder != '(' && holder != ')' && holder != '/' && holder!= '*' && holder != '+' && holder != '-') {
            dequeConverted.insertBack(holder);
            trackSizeConverted++;
        } 
        //if an operator, we check with the stackOperators
        else {
            //if the tracker of the operators size is 0, then the stack is empty, not need to check the stack
            if (trackSizeOper == 0) {
                stackOperators.insertBack(holder);
                trackSizeOper++;
            } else {
                //the stack is not empty, therefore we check the precedences
                //we pop the operator from the stack, and see of the precedence of that operator is less than that of the operator at hand
                //if less, we simply push the operator at hand into the stack
                stackItem = stackOperators.removeBack();
                trackSizeOper--;
                switch (stackItem) {


                    case '(': 
                        //if it is any paranthesis, we simply push it back and push the operator at hand into the stack
                        stackOperators.insertBack(stackItem);
                        trackSizeOper++;
                        stackOperators.insertBack(holder);
                        trackSizeOper++;
                        break;

                    //We can assume the closed paranthesis will not be among the stack items


                    case '*':
                        //we now compare the precedence of the operator at hand
                        switch (holder) {
                            case '*': 

                                //precedence of the operator at hand and that of the stack operator are equal
                                //we push the stack item into the dequeConverted
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                //the stackOperators is empty, we simply push the operator at hand into the stackOperator
                                if (trackSizeOper == 0) {
                                    stackOperators.insertBack(holder);
                                    trackSizeOper++;
                                }
                                // ??? WE WILL SEE IF WE WILL NEED TO CHECK FURTHER INSIDE THE OPERATORS STACK
                                //otherwise we check if the precedence of the leftover operators is higher or lower than that 
                                //of the operator at hand
                        
                                break;

                            case '/':

                                //precedence of the operator at hand and that of the stack operator are equal
                                //we push the stack item into the dequeConverted
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                //the stackOperators is empty, we simply push the operator at hand into the stackOperator
                                if (trackSizeOper == 0) {
                                    stackOperators.insertBack(holder);
                                    trackSizeOper++;
                                }
                                // ??? WE WILL SEE IF WE WILL NEED TO CHECK FURTHER INSIDE THE OPERATORS STACK
                                //otherwise we check if the precedence of the leftover operators is higher or lower than that 
                                //of the operator at hand

                                break;

                            case '+':

                                //precedence of the stack item is higher than that of the operator at hand
                                //the stack operator will be pushed into the converted deque
                                //the operator at hand will be pushed into the operator stack
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case '-':

                                //precedence of the stack item is higher than that of the operator at hand
                                //the stack operator will be pushed into the converted deque
                                //the operator at hand will be pushed into the operator stack
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case '(':

                                //if it is an open paranthesis, we simply push it into the operator stack
                                //we push the stack operator back first
                                stackOperators.insertBack(stackItem);
                                trackSizeOper++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case ')':

                                //if it is a closed paranthesis, we keep popping operators from the operator 
                                //stack until we encounter an open paranthesis, at which point we get rid of 
                                //the open paranthesis from the operator stack, as well as not push it into
                                //the converted deque

                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;
                                stackItem = stackOperators.removeBack();
                                trackSizeOper--;

                                //two conditions to terminate the loop: stack is empty or encountered open paranthesis
                                while (true) {
                                    //cout<<"INSIDE THE BLOCK IN THE MULTIPLICATION BLOCK";
                                    //we also check if the stack has become empty
                                    if (trackSizeOper == 0) {
                                        break;
                                    }

                                    if (stackItem == '(') {
                                        break;
                                    } else {
                                        dequeConverted.insertBack(stackItem);
                                        trackSizeConverted++;
                                    }
                                    stackItem = stackOperators.removeBack();
                                    trackSizeOper--;
                                }
                                break;
                        }

                        break;







                    case '/':
                        //we now compare the precedence of the operator at hand
                        switch (holder) {

                            case '*': 

                                //precedence of the operator at hand and that of the stack operator are equal
                                //we push the stack item into the dequeConverted
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                //we push the operator at hand into the stackOperator
                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                // ??? WE WILL SEE IF WE WILL NEED TO CHECK FURTHER INSIDE THE OPERATORS STACK
                                //otherwise we check if the precedence of the leftover operators is higher or lower than that 
                                //of the operator at hand

                                break;

                            case '/':

                                //precedence of the operator at hand and that of the stack operator are equal
                                //we push the stack item into the dequeConverted
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                //we push the operator at hand into the stackOperator
                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                // ??? WE WILL SEE IF WE WILL NEED TO CHECK FURTHER INSIDE THE OPERATORS STACK
                                //otherwise we check if the precedence of the leftover operators is higher or lower than that 
                                //of the operator at hand
    
                                break;

                            case '+':

                                //precedence of the stack item is higher than that of the operator at hand
                                //the stack operator will be pushed into the converted deque
                                //the operator at hand will be pushed into the operator stack
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case '-':

                                //precedence of the stack item is higher than that of the operator at hand
                                //the stack operator will be pushed into the converted deque
                                //the operator at hand will be pushed into the operator stack
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case '(':

                                //if it is an open paranthesis, we simply push it into the operator stack
                                //we push the stack operator back first
                                stackOperators.insertBack(stackItem);
                                trackSizeOper++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case ')':

                                //if it is a closed paranthesis, we keep popping operators from the operator 
                                //stack until we encounter an open paranthesis, at which point we get rid of 
                                //the open paranthesis from the operator stack, as well as not push it into
                                //the converted deque

                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;
                                stackItem = stackOperators.removeBack();
                                trackSizeOper--;

                                //two conditions to terminate the loop: stack is empty or encountered open paranthesis
                                while (true) {
                                    
                                    //we also check if the stack has become empty
                                    if (trackSizeOper == 0) {
                                        break;
                                    }

                                    if (stackItem == '(') {
                                        break;
                                    } else {
                                        dequeConverted.insertBack(stackItem);
                                        trackSizeConverted++;
                                    }
                                    stackItem = stackOperators.removeBack();
                                    trackSizeOper--;
                                }

                                break;
                        }

                        break;







                    case '+':
                        //we now compare the precedence of the operator at hand
                        switch (holder) { 

                            case '+':
                                //the precedence of the operator at hand is equal to that of the stack operator
                                //we push the stack item into the dequeConverted
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                //we push the operator at hand into the stackOperator
                                stackOperators.insertBack(holder);
                                trackSizeOper++;
                                break;
                            
                            case '-':
                                //the precedence of the operator at hand is equal to that of the stack operator
                                //we push the stack item into the dequeConverted
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                //we push the operator at hand into the stackOperator
                                stackOperators.insertBack(holder);
                                trackSizeOper++;
                                break;
                            
                            case '*':
                                //the precedence of the operator at hand is higher than that of the stack operator
                                //we simply push both of them into the operator stack, in corresponding order
                                stackOperators.insertBack(stackItem);
                                trackSizeOper++;

                                stackOperators.insertBack(holder);
                                trackSizeConverted++;

                                break;

                            case '/':
                                //the precedence of the operator at hand is higher than that of the stack operator
                                //we simply push both of them into the operator stack, in corresponding order
                                stackOperators.insertBack(stackItem);
                                trackSizeOper++;

                                stackOperators.insertBack(holder);
                                trackSizeConverted++;

                                break;

                            case '(':

                                //if it is an open paranthesis, we simply push it into the operator stack
                                //we push the stack operator back first
                                stackOperators.insertBack(stackItem);
                                trackSizeOper++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case ')':

                                //if it is a closed paranthesis, we keep popping operators from the operator 
                                //stack until we encounter an open paranthesis, at which point we get rid of 
                                //the open paranthesis from the operator stack, as well as not push it into
                                //the converted deque
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;
                                stackItem = stackOperators.removeBack();
                                trackSizeOper--;

                                    //two conditions to terminate the loop: stack is empty or encountered open paranthesis
                                    while (true) {

                                        //we also check if the stack has become empty
                                        if (trackSizeOper == 0) {
                                            break;
                                        }

                                        if (stackItem == '(') {
                                            
                                            break;
                                        } else {
                                            dequeConverted.insertBack(stackItem);
                                            trackSizeConverted++;
                                        }
                                        stackItem = stackOperators.removeBack();
                                        trackSizeOper--;
                                    }

                                break;
                        }

                        break;






                    case '-':
                            //we now compare the precedence of the operator at hand
                            switch (holder) { 

                                case '+':
                                    //the precedence of the operator at hand is equal to that of the stack operator
                                    //we push the stack item into the dequeConverted
                                    dequeConverted.insertBack(stackItem);
                                    trackSizeConverted++;

                                    //we push the operator at hand into the stackOperator
                                    stackOperators.insertBack(holder);
                                    trackSizeOper++;
                                    break;
                            
                                case '-':
                                    //the precedence of the operator at hand is equal to that of the stack operator
                                    //we push the stack item into the dequeConverted
                                    dequeConverted.insertBack(stackItem);
                                    trackSizeConverted++;

                                    //we push the operator at hand into the stackOperator
                                    stackOperators.insertBack(holder);
                                    trackSizeOper++;
                                    break;
                            
                                case '*':
                                    //the precedence of the operator at hand is higher than that of the stack operator
                                    //we simply push both of them into the operator stack, in corresponding order
                                    stackOperators.insertBack(stackItem);
                                    trackSizeOper++;

                                    stackOperators.insertBack(holder);
                                    trackSizeConverted++;

                                    break;

                                case '/':
                                    //the precedence of the operator at hand is higher than that of the stack operator
                                    //we simply push both of them into the operator stack, in corresponding order
                                    stackOperators.insertBack(stackItem);
                                    trackSizeOper++;

                                    stackOperators.insertBack(holder);
                                    trackSizeConverted++;

                                    break;

                                case '(':

                                    //if it is an open paranthesis, we simply push it into the operator stack
                                    //we push the stack operator back first
                                    stackOperators.insertBack(stackItem);
                                    trackSizeOper++;

                                    stackOperators.insertBack(holder);
                                    trackSizeOper++;

                                    break;

                                case ')':

                                    //if it is a closed paranthesis, we keep popping operators from the operator 
                                    //stack until we encounter an open paranthesis, at which point we get rid of 
                                    //the open paranthesis from the operator stack, as well as not push it into
                                    //the converted deque

                                    dequeConverted.insertBack(stackItem);
                                    trackSizeConverted++;
                                    stackItem = stackOperators.removeBack();
                                    trackSizeOper--;
                                    

                                    //two conditions to terminate the loop: stack is empty or encountered open paranthesis
                                    while (true) {
                                        //we also check if the stack has become empty
                                        if (trackSizeOper == 0) {
                                            break;
                                        }

                                        if (stackItem == '(') {
                                            break;
                                        } else {
                                            dequeConverted.insertBack(stackItem);
                                            trackSizeConverted++;
                                        }
                                        stackItem = stackOperators.removeBack();
                                        trackSizeOper--;
                                    }

                                    break;
                        }

                        break;



                }
            }
        }

        //if the next iteration will complete the size of the original deque,
        //we will continuously push the operators from the operator stack
        //into the converted deque
        if ((i + 1) == sizeOriginal) {
            while (trackSizeOper != 0) {
                stackItem = stackOperators.removeBack();
                trackSizeOper--;
                dequeConverted.insertBack(stackItem);
                trackSizeConverted++;
            }
            //dequeConverted.insertBack(stackOperators.removeBack());
        }
    }

    //we now make a string to contain all the elements from the dequeConverted
    ////we also empty the converted deque for other conversions in the meantime
    string infix_to_postfix ="";
    for (int i = 0; i < trackSizeConverted; i++) {
        infix_to_postfix += dequeConverted.removeFront();
    }
    
    cout<<"\n\n\nCONVERTED STRING"<<infix_to_postfix;

    string valid = "";
    char el;
    //now we put the necessary spaces between the elements
    for (int i = 0; i < trackSizeConverted; i++) {
        el = infix_to_postfix[i];
        valid += el;
        if (el == '(') {
            while(el == '(') {
                i++;
                el = infix_to_postfix[i];
                if (el != '(') {
                    valid += " ";
                }
                valid += el;
            }
        } else if (el == ')') {
            while(el == ')') {
                i++;
                el = infix_to_postfix[i];
                if (el != ')') {
                    valid += " ";
                }
                valid += el;
            }
        }
        valid += " ";
    }


    return valid;
}


//infix notation to prefix notation
string NotationConverter::infixToPrefix(string inStr) {

    char iterat;
    
    //first we will collect the original notation in a neat form in a seperate stack, originalNotation
    //a local variable "sizeOriginal" will help in managing the originalNotation deque, and "sizeOperators" 
    //will do so for the stackOperators
    int sizeOriginal = 0;
    int sizeOperators = 0;
    for (unsigned int i = 0; i < inStr.length(); i++) {
        iterat = inStr[i];
        //if the character is among lowercase or uppercase letters
        if ((iterat >= 'A' && iterat <= 'Z') || (iterat >= 'a' && iterat <= 'z')) {
            dequeOriginal.insertBack(iterat);
            sizeOriginal++;
        } else if (iterat == '(' || iterat == ')' || iterat == '+' || iterat == '-' || iterat == '*' || iterat == '/') {
            dequeOriginal.insertBack(iterat);
            sizeOriginal++;
            sizeOperators++;
        } else if (iterat == ' ') { continue; } 
        else {
            cout<<"\nINVALID NOTATION!!!\n"; //MUST THROW AN ERROR
        }
    }

    //we reverse the elements first
    //to reverse we will first pop the elements from the original deque, 
    //push them into the operator stack and deque from it back into the orginal deque
    for (int i = 0; i < sizeOriginal; i++) {
        stackOperators.insertFront(dequeOriginal.removeFront());
    }
    //if the element is a paranthesis, we reverse them (open to close and vice versa)
    for (int i = 0; i < sizeOriginal; i++) {
        iterat = stackOperators.removeFront();
        if (iterat == '(') {
            iterat = ')';
        } else if (iterat == ')') {
            iterat = '(';
        }
        dequeOriginal.insertBack(iterat);
    }    


    //We will pop the operators from the dequeOriginal into the stackOperators, and operands into the dequeConverted
    //if there are multiple operators in the operatorsStack, the operator on top will be popped 
    //and pushed into the dequeConverted,according to precedence rules of operators
    //Rules of Operators:
    //1st '(' or ')'
    //2nd '*' or '/'
    //3rd '+' or '-'
    //if we encounter a closed paranthesis, we will keep poping the operators form the stackOperators
    //until we encounter an open paranthesis in the stackOperators
    char holder;
    char stackItem;


    int trackSizeConverted = 0;
    int trackSizeOper = 0;

    //because we already took care of invalid characters, we can assume all charactersother than 
    //operators are variables of the expression
    for (int i = 0; i < sizeOriginal; i++) {
        holder = dequeOriginal.removeFront();
        

        //if not an operator, then a variables to be pushed into the dequeConverter directly
        if (holder != '(' && holder != ')' && holder != '/' && holder!= '*' && holder != '+' && holder != '-') {
            dequeConverted.insertBack(holder);
            trackSizeConverted++;
        } 
        //if an operator, we check with the stackOperators
        else {
            //if the tracker of the operators size is 0, then the stack is empty, not need to check the stack
            if (trackSizeOper == 0) {
                stackOperators.insertBack(holder);
                trackSizeOper++;
            } else {
                //the stack is not empty, therefore we check the precedences
                //we pop the operator from the stack, and see of the precedence of that operator is less than that of the operator at hand
                //if less, we simply push the operator at hand into the stack
                stackItem = stackOperators.removeBack();
                trackSizeOper--;
                switch (stackItem) {


                    case '(': 
                        //if it is any paranthesis, we simply push it back and push the operator at hand into the stack
                        stackOperators.insertBack(stackItem);
                        trackSizeOper++;
                        stackOperators.insertBack(holder);
                        trackSizeOper++;
                        break;

                    //We can assume the closed paranthesis will not be among the stack items


                    case '*':
                        //we now compare the precedence of the operator at hand
                        switch (holder) {
                            case '*': 

                                //precedence of the operator at hand and that of the stack operator are equal
                                //we push the stack item into the dequeConverted
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                //the stackOperators is empty, we simply push the operator at hand into the stackOperator
                                if (trackSizeOper == 0) {
                                    stackOperators.insertBack(holder);
                                    trackSizeOper++;
                                }
                                // ??? WE WILL SEE IF WE WILL NEED TO CHECK FURTHER INSIDE THE OPERATORS STACK
                                //otherwise we check if the precedence of the leftover operators is higher or lower than that 
                                //of the operator at hand
                        
                                break;

                            case '/':

                                //precedence of the operator at hand and that of the stack operator are equal
                                //we push the stack item into the dequeConverted
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                //the stackOperators is empty, we simply push the operator at hand into the stackOperator
                                if (trackSizeOper == 0) {
                                    stackOperators.insertBack(holder);
                                    trackSizeOper++;
                                }
                                // ??? WE WILL SEE IF WE WILL NEED TO CHECK FURTHER INSIDE THE OPERATORS STACK
                                //otherwise we check if the precedence of the leftover operators is higher or lower than that 
                                //of the operator at hand

                                break;

                            case '+':

                                //precedence of the stack item is higher than that of the operator at hand
                                //the stack operator will be pushed into the converted deque
                                //the operator at hand will be pushed into the operator stack
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case '-':

                                //precedence of the stack item is higher than that of the operator at hand
                                //the stack operator will be pushed into the converted deque
                                //the operator at hand will be pushed into the operator stack
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case '(':

                                //if it is an open paranthesis, we simply push it into the operator stack
                                //we push the stack operator back first
                                stackOperators.insertBack(stackItem);
                                trackSizeOper++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case ')':

                                //if it is a closed paranthesis, we keep popping operators from the operator 
                                //stack until we encounter an open paranthesis, at which point we get rid of 
                                //the open paranthesis from the operator stack, as well as not push it into
                                //the converted deque

                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;
                                stackItem = stackOperators.removeBack();
                                trackSizeOper--;

                                //two conditions to terminate the loop: stack is empty or encountered open paranthesis
                                while (true) {
                                    //cout<<"INSIDE THE BLOCK IN THE MULTIPLICATION BLOCK";
                                    //we also check if the stack has become empty
                                    if (trackSizeOper == 0) {
                                        break;
                                    }

                                    if (stackItem == '(') {
                                        break;
                                    } else {
                                        dequeConverted.insertBack(stackItem);
                                        trackSizeConverted++;
                                    }
                                    stackItem = stackOperators.removeBack();
                                    trackSizeOper--;
                                }
                                break;
                        }

                        break;

                    case '/':
                        //we now compare the precedence of the operator at hand
                        switch (holder) {

                            case '*': 

                                //precedence of the operator at hand and that of the stack operator are equal
                                //we push the stack item into the dequeConverted
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                //we push the operator at hand into the stackOperator
                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                // ??? WE WILL SEE IF WE WILL NEED TO CHECK FURTHER INSIDE THE OPERATORS STACK
                                //otherwise we check if the precedence of the leftover operators is higher or lower than that 
                                //of the operator at hand

                                break;

                            case '/':

                                //precedence of the operator at hand and that of the stack operator are equal
                                //we push the stack item into the dequeConverted
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                //we push the operator at hand into the stackOperator
                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                // ??? WE WILL SEE IF WE WILL NEED TO CHECK FURTHER INSIDE THE OPERATORS STACK
                                //otherwise we check if the precedence of the leftover operators is higher or lower than that 
                                //of the operator at hand
    
                                break;

                            case '+':

                                //precedence of the stack item is higher than that of the operator at hand
                                //the stack operator will be pushed into the converted deque
                                //the operator at hand will be pushed into the operator stack
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case '-':

                                //precedence of the stack item is higher than that of the operator at hand
                                //the stack operator will be pushed into the converted deque
                                //the operator at hand will be pushed into the operator stack
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case '(':

                                //if it is an open paranthesis, we simply push it into the operator stack
                                //we push the stack operator back first
                                stackOperators.insertBack(stackItem);
                                trackSizeOper++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case ')':

                                //if it is a closed paranthesis, we keep popping operators from the operator 
                                //stack until we encounter an open paranthesis, at which point we get rid of 
                                //the open paranthesis from the operator stack, as well as not push it into
                                //the converted deque

                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;
                                stackItem = stackOperators.removeBack();
                                trackSizeOper--;

                                //two conditions to terminate the loop: stack is empty or encountered open paranthesis
                                while (true) {
                                    
                                    //we also check if the stack has become empty
                                    if (trackSizeOper == 0) {
                                        break;
                                    }

                                    if (stackItem == '(') {
                                        break;
                                    } else {
                                        dequeConverted.insertBack(stackItem);
                                        trackSizeConverted++;
                                    }
                                    stackItem = stackOperators.removeBack();
                                    trackSizeOper--;
                                }

                                break;
                        }

                        break;

                    case '+':
                        //we now compare the precedence of the operator at hand
                        switch (holder) { 

                            case '+':
                                //the precedence of the operator at hand is equal to that of the stack operator
                                //we push the stack item into the dequeConverted
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                //we push the operator at hand into the stackOperator
                                stackOperators.insertBack(holder);
                                trackSizeOper++;
                                break;
                            
                            case '-':
                                //the precedence of the operator at hand is equal to that of the stack operator
                                //we push the stack item into the dequeConverted
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;

                                //we push the operator at hand into the stackOperator
                                stackOperators.insertBack(holder);
                                trackSizeOper++;
                                break;
                            
                            case '*':
                                //the precedence of the operator at hand is higher than that of the stack operator
                                //we simply push both of them into the operator stack, in corresponding order
                                stackOperators.insertBack(stackItem);
                                trackSizeOper++;

                                stackOperators.insertBack(holder);
                                trackSizeConverted++;

                                break;

                            case '/':
                                //the precedence of the operator at hand is higher than that of the stack operator
                                //we simply push both of them into the operator stack, in corresponding order
                                stackOperators.insertBack(stackItem);
                                trackSizeOper++;

                                stackOperators.insertBack(holder);
                                trackSizeConverted++;

                                break;

                            case '(':

                                //if it is an open paranthesis, we simply push it into the operator stack
                                //we push the stack operator back first
                                stackOperators.insertBack(stackItem);
                                trackSizeOper++;

                                stackOperators.insertBack(holder);
                                trackSizeOper++;

                                break;

                            case ')':

                                //if it is a closed paranthesis, we keep popping operators from the operator 
                                //stack until we encounter an open paranthesis, at which point we get rid of 
                                //the open paranthesis from the operator stack, as well as not push it into
                                //the converted deque
                                dequeConverted.insertBack(stackItem);
                                trackSizeConverted++;
                                stackItem = stackOperators.removeBack();
                                trackSizeOper--;

                                    //two conditions to terminate the loop: stack is empty or encountered open paranthesis
                                    while (true) {

                                        //we also check if the stack has become empty
                                        if (trackSizeOper == 0) {
                                            break;
                                        }

                                        if (stackItem == '(') {
                                            
                                            break;
                                        } else {
                                            dequeConverted.insertBack(stackItem);
                                            trackSizeConverted++;
                                        }
                                        stackItem = stackOperators.removeBack();
                                        trackSizeOper--;
                                    }

                                break;
                        }

                        break;

                    case '-':
                            //we now compare the precedence of the operator at hand
                            switch (holder) { 

                                case '+':
                                    //the precedence of the operator at hand is equal to that of the stack operator
                                    //we push the stack item into the dequeConverted
                                    dequeConverted.insertBack(stackItem);
                                    trackSizeConverted++;

                                    //we push the operator at hand into the stackOperator
                                    stackOperators.insertBack(holder);
                                    trackSizeOper++;
                                    break;
                            
                                case '-':
                                    //the precedence of the operator at hand is equal to that of the stack operator
                                    //we push the stack item into the dequeConverted
                                    dequeConverted.insertBack(stackItem);
                                    trackSizeConverted++;

                                    //we push the operator at hand into the stackOperator
                                    stackOperators.insertBack(holder);
                                    trackSizeOper++;
                                    break;
                            
                                case '*':
                                    //the precedence of the operator at hand is higher than that of the stack operator
                                    //we simply push both of them into the operator stack, in corresponding order
                                    stackOperators.insertBack(stackItem);
                                    trackSizeOper++;

                                    stackOperators.insertBack(holder);
                                    trackSizeConverted++;

                                    break;

                                case '/':
                                    //the precedence of the operator at hand is higher than that of the stack operator
                                    //we simply push both of them into the operator stack, in corresponding order
                                    stackOperators.insertBack(stackItem);
                                    trackSizeOper++;

                                    stackOperators.insertBack(holder);
                                    trackSizeConverted++;

                                    break;

                                case '(':

                                    //if it is an open paranthesis, we simply push it into the operator stack
                                    //we push the stack operator back first
                                    stackOperators.insertBack(stackItem);
                                    trackSizeOper++;

                                    stackOperators.insertBack(holder);
                                    trackSizeOper++;

                                    break;

                                case ')':

                                    //if it is a closed paranthesis, we keep popping operators from the operator 
                                    //stack until we encounter an open paranthesis, at which point we get rid of 
                                    //the open paranthesis from the operator stack, as well as not push it into
                                    //the converted deque

                                    dequeConverted.insertBack(stackItem);
                                    trackSizeConverted++;
                                    stackItem = stackOperators.removeBack();
                                    trackSizeOper--;
                                    

                                    //two conditions to terminate the loop: stack is empty or encountered open paranthesis
                                    while (true) {
                                        //we also check if the stack has become empty
                                        if (trackSizeOper == 0) {
                                            break;
                                        }

                                        if (stackItem == '(') {
                                            break;
                                        } else {
                                            dequeConverted.insertBack(stackItem);
                                            trackSizeConverted++;
                                        }
                                        stackItem = stackOperators.removeBack();
                                        trackSizeOper--;
                                    }

                                    break;
                        }

                        break;



                }
            }
        }

        //if the next iteration will complete the size of the original deque,
        //we will continuously push the operators from the operator stack
        //into the converted deque
        if ((i + 1) == sizeOriginal) {
            while (trackSizeOper != 0) {
                stackItem = stackOperators.removeBack();
                trackSizeOper--;                
                dequeConverted.insertBack(stackItem);
                trackSizeConverted++;
            }
            //dequeConverted.insertBack(stackOperators.removeBack());
        }
        //dequeConverted.insertBack(stackOperators.removeFront());
    }

    //we empty the converted deque for other conversions

    //to reverse we will first pop the elements from the original deque, 
    //push them into the operator stack and deque from it back into the orginal deque
    for (int i = 0; i < trackSizeConverted; i++) {
        iterat = dequeConverted.removeFront();
        stackOperators.insertFront(iterat);
    }
    for (int i = 0; i < trackSizeConverted; i++) {
        iterat = stackOperators.removeFront();
        dequeConverted.insertBack(iterat);
    }    

    //we now make a string to contain all the elements from the dequeConverted
    ////we also empty the converted deque for other conversions in the meantime
    string infix_to_prefix ="";
    for (int i = 0; i < trackSizeConverted; i++) {
        infix_to_prefix += dequeConverted.removeFront();
    }

    //cout<<"CONVERTED STRING: "<<infix_to_prefix<<"\n\n\n";

    string valid = "";
    char el;
    //now we put the necessary spaces between the elements
    for (int i = 0; i < trackSizeConverted; i++) {
        el = infix_to_prefix[i];
        valid += el;
        if (el == '(') {
            while(el == '(') {
                i++;
                el = infix_to_prefix[i];
                if (el != '(') {
                    valid += " ";
                }
                valid += el;
            }
        } else if (el == ')') {
            while(el == ')') {
                i++;
                el = infix_to_prefix[i];
                if (el != ')') {
                    valid += " ";
                }
                valid += el;
            }
        }
        valid += " ";
    }


    return valid;
}


//prefix notation to infix
string NotationConverter::prefixToInfix(string inStr) {

    char iterat;
    
    //first we will collect the original notation in a neat form in a seperate stack, originalNotation
    //a local variable "sizeOriginal" will help in managing the originalNotation deque, and "sizeOperators" 
    //will do so for the stackOperators
    int sizeOriginal = 0;
    int sizeOperators = 0;
    for (unsigned int i = 0; i < inStr.length(); i++) {
        iterat = inStr[i];
        //if the character is among lowercase or uppercase letters
        if ((iterat >= 'A' && iterat <= 'Z') || (iterat >= 'a' && iterat <= 'z')) {
            dequeOriginal.insertBack(iterat);
            sizeOriginal++;
        } else if (iterat == '(' || iterat == ')' || iterat == '+' || iterat == '-' || iterat == '*' || iterat == '/') {
            dequeOriginal.insertBack(iterat);
            sizeOriginal++;
            sizeOperators++;
        } else if (iterat == ' ') { continue; } 
        else {
            cout<<"\nINVALID NOTATION!!!\n"; //MUST THROW AN ERROR
        }
    }

    //we reverse the elements first
    //to reverse we will first pop the elements from the original deque, 
    //push them into the operator stack and deque from it back into the orginal deque
    for (int i = 0; i < sizeOriginal; i++) {
        stackOperators.insertFront(dequeOriginal.removeFront());
    }
    //if the element is a paranthesis, we reverse them (open to close and vice versa)
    for (int i = 0; i < sizeOriginal; i++) {
        iterat = stackOperators.removeFront();
        if (iterat == '(') {
            iterat = ')';
        } else if (iterat == ')') {
            iterat = '(';
        }
        dequeOriginal.insertBack(iterat);
    } 

    int trackStackSize = 0;
    char holder;
    char manager;
    bool met_inner_paranthesis = false;
    for (int i = 0; i < sizeOriginal; i++) {

        //cout<<"\nCYCLE";

        holder = dequeOriginal.removeFront();
        //cout<<"\nHOLDER: "<<holder;
        
        //if the holder value is among alphabetic letters, the holder holds an operand
        //we simply push it into the stack
        if ((holder >= 'A' && holder <= 'Z') || (holder >= 'a' && holder <= 'z')) {
            //cout<<"\nINSERTING THIS INTO THE STACK: "<<holder;
            stackOperators.insertBack(holder);
            trackStackSize++;
        }
        //else the holder encountered an operation: we turn to the stack, pop two elements from there,
        //and add to the front of the dequeConverted
        else {
            //cout<<"\nHOLDER IN ELSE BLOCK: "<<holder<<endl;
            trackStackSize++; //???? DO WE INCREMENT THE TRACK STACK SIZE?
            manager = stackOperators.removeBack();
            //cout<<"\n\nMANAGER HERE: "<<manager;
            //we check if the element we have got from the stack is a closed paranthesis
            //if we did, we will keep pulling elements until we encounter its paired open
            //paranthesis

            if (manager == ')') {
                dequeConverted.insertFront(manager);
                while(manager != '(') {
                    manager = stackOperators.removeBack();
                    //we check for any other inner parantheses
                    //if we encounter another closed paranthesis, 
                    //we make the bool variable true until we ecounter its pair
                    if (manager == ')') {
                        met_inner_paranthesis = true;
                        while(met_inner_paranthesis == true) {
                            dequeConverted.insertFront(manager);
                            manager = stackOperators.removeBack();
                            if (manager == '(') {
                                met_inner_paranthesis = false;
                                dequeConverted.insertFront(manager);
                                manager = stackOperators.removeBack();
                                if(manager == '(') {
                                    dequeConverted.insertFront(manager);
                                } else {
                                    stackOperators.insertBack(manager);
                                }
                            }
                        }
                    } else {
                        dequeConverted.insertFront(manager);
                    }
                }
                //assuming the current value of the manager is '(' after the loop
                //dequeConverted.insertFront(manager);
                manager = stackOperators.removeBack();
                if (manager == ')') {
                    dequeConverted.insertFront(manager);
                    while(manager != '(') {
                        manager = stackOperators.removeBack();
                        if (manager == ')') {
                            met_inner_paranthesis = true;
                            while(met_inner_paranthesis == true) {
                                dequeConverted.insertFront(manager);
                                manager = stackOperators.removeBack();
                                if (manager == '(') {
                                    met_inner_paranthesis = false;
                                    dequeConverted.insertFront(manager);
                                    manager = stackOperators.removeBack();
                                    if(manager == '(') {
                                        dequeConverted.insertFront(manager);
                                    } else {
                                        stackOperators.insertBack(manager);
                                    }
                                }
                            }
                        } else {
                            dequeConverted.insertFront(manager);
                        }
                    }
                } else {
                    dequeConverted.insertFront(manager);
                }
            } else {
                dequeConverted.insertFront(manager);
                //we take the seocond operand from the stack
                manager = stackOperators.removeBack();
                //we check if the second operand is also enclosed into the parantheses
                if (manager == ')') {
                    dequeConverted.insertFront(manager);
                    while(manager != '(') {
                        manager = stackOperators.removeBack();
                        //we check for any additional parantheses
                        if (manager == ')') {
                            met_inner_paranthesis = true;
                            while(met_inner_paranthesis == true) {
                                dequeConverted.insertFront(manager);
                                manager = stackOperators.removeBack();
                                if (manager == '(') {
                                    met_inner_paranthesis = false;
                                    dequeConverted.insertFront(manager);
                                    manager = stackOperators.removeBack();
                                    if (manager == '(') {
                                        dequeConverted.insertFront(manager);
                                    } else {
                                        stackOperators.insertBack(manager);
                                    }
                                }   
                            }
                        } else {
                            dequeConverted.insertFront(manager);
                        }
                    }
                    //dequeConverted.insertFront(manager);
                } else {
                    dequeConverted.insertFront(manager);
                }
            }

            //now we add an open paranthesis to the stack
            stackOperators.insertBack('(');
            trackStackSize++;

            //now we push the two operands back from the dequeConverted
            //first we take one element
            //we need to check if we are pulling an open paranthesis from the dequeConverted
            //in this case, we will keep pulling until we encounter its paired closed paranthesis
            manager = dequeConverted.removeFront();
            //cout<<"\n\n\nMANAGER FROM THE DEQUECONVERTED: "<<manager<<endl;
            if (manager == '(') {
                stackOperators.insertBack(manager);
                while(manager != ')') {                    
                    manager = dequeConverted.removeFront();
                    //we check for any other inner parantheses
                    //if we encounter another closed paranthesis, 
                    //we make the bool variable true until we ecounter its pair
                    if (manager == '(') {
                        met_inner_paranthesis = true;
                        while(met_inner_paranthesis == true) {
                            stackOperators.insertBack(manager);
                            manager = dequeConverted.removeFront();
                            if (manager == ')') {
                                met_inner_paranthesis = false;
                                stackOperators.insertBack(manager);
                                manager = dequeConverted.removeFront();
                                if(manager == '(') {
                                    dequeConverted.insertFront(manager);
                                } else {
                                    stackOperators.insertBack(manager);
                                }
                            }
                        }
                    } else {
                        stackOperators.insertBack(manager);
                    }
                }
                //assuming the current value of the manager is ')' after the loop
                //stackOperators.insertBack(manager);
            } else {
                stackOperators.insertBack(manager);
            }
            //now we insert the operation, which is holder at this point, in between
            stackOperators.insertBack(holder);
            //now we can insert the second operand
            //again we check if the element we are pulling is an open paranthesis, 
            //in which case will will keep pulling until we encounter its paired closed 
            //paranthesis
            manager = dequeConverted.removeFront();

            if (manager == '(') {
                stackOperators.insertBack(manager);
                while(manager != ')') {
                    manager = dequeConverted.removeFront();
                    //we check for any other inner parantheses
                    //if we encounter another closed paranthesis, 
                    //we make the bool variable true until we ecounter its pair
                    if (manager == '(') {
                        met_inner_paranthesis = true;
                        while(met_inner_paranthesis == true) {
                            stackOperators.insertBack(manager);
                            manager = dequeConverted.removeFront();
                            if (manager == ')') {
                                met_inner_paranthesis = false;
                                stackOperators.insertBack(manager);
                                manager = dequeConverted.removeFront();
                                if(manager == ')') {
                                    stackOperators.insertBack(manager);
                                } else {
                                    stackOperators.insertBack(manager);
                                }
                            }
                        }
                    } else {
                        stackOperators.insertBack(manager);
                    }
                }
                //assuming the current value of the manager is ')' after the loop
                //stackOperators.insertBack(manager);
            } else {
                stackOperators.insertBack(manager);
            }

            //now we add the closing paranthesis to complete a new operand in the stack
            stackOperators.insertBack(')');
            trackStackSize++;  
        }
    }
    //we reverse the elements first
    //to reverse we will first pop the elements from the original deque, 
    //push them into the operator stack and deque from it back into the orginal deque
    for (int i = 0; i < trackStackSize; i++) {
        dequeOriginal.insertFront(stackOperators.removeFront());
    }
    //if the element is a paranthesis, we reverse them (open to close and vice versa)
    for (int i = 0; i < trackStackSize; i++) {
        iterat = dequeOriginal.removeFront();
        if (iterat == ')') {
            iterat = '(';
        } else if (iterat == '(') {
            iterat = ')';
        }
        stackOperators.insertBack(iterat);
    } 
    
    string prefix_to_infix = "";
    for (int i = 0; i < trackStackSize; i++) {
        prefix_to_infix += stackOperators.removeFront();
    }

    string valid = "";
    char el;
    //now we put the necessary spaces between the elements
    for (int i = 0; i < trackStackSize; i++) {
        el = prefix_to_infix[i];
        valid += el;
        if (el == '(') {
            while(el == '(') {
                i++;
                el = prefix_to_infix[i];
                if (el != '(') {
                    valid += " ";
                }
                valid += el;
            }
        } else if (el == ')') {
            while(el == ')') {
                i++;
                el = prefix_to_infix[i];
                if (el != ')') {
                    valid += " ";
                }
                valid += el;
            }
        }
        valid += " ";
    }


    return valid;
}


//prefix notation to prefix notation
string NotationConverter::prefixToPostfix(string inStr) {
    //We can first convert from prefix to infix, and then from infix to postfix
    string prefix_to_infix = prefixToInfix(inStr);
    string infix_to_postfix = infixToPostfix(prefix_to_infix);
    cout<<"\n\n\n\nSTRING IN CONVERSION:::"<<infix_to_postfix;
    string valid = "";
    char el;
    //now we put the necessary spaces between the elements
    for (unsigned int i = 0; i < infix_to_postfix.length(); i++) {
        el = infix_to_postfix[i];
        valid += el;
        if (el == '(') {
            while(el == '(') {
                i++;
                el = infix_to_postfix[i];
                if (el != '(') {
                    valid += " ";
                }
                valid += el;
            }
        } else if (el == ')') {
            while(el == ')') {
                i++;
                el = infix_to_postfix[i];
                if (el != ')') {
                    valid += " ";
                }
                valid += el;
            }
        }
        valid += " ";
    }


    return valid;
}







