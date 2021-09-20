#ifndef CALCLISTINTERFACE_H
#define CALCLISTINTERFACE_H

#include <string>

// Enum that contains all the arithmetic functions needed for newOperation
typedef enum { ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION } FUNCTIONS;

// Abstract class for inheritance
class CalcListInterface {
public:
    virtual double total() const = 0;
    virtual void newOperation(const FUNCTIONS func, const double operand) = 0;
    virtual void removeLastOperation() = 0;
    virtual std::string toString(unsigned short precision) const = 0;
};

#endif /* CALCLISTINTERFACE_H */
