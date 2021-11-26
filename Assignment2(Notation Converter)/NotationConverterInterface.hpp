#ifndef NOTATIONCONVERTERINTERFACE_H
#define NOTATIONCONVERTERINTERFACE_H

#include <string>

class NotationConverterInterface
{
public:
  virtual std::string postfixToInfix(std::string inStr) = 0;
  virtual std::string postfixToPrefix(std::string inStr) = 0;

  virtual std::string infixToPostfix(std::string inStr) = 0;
  virtual std::string infixToPrefix(std::string inStr) = 0;

  virtual std::string prefixToInfix(std::string inStr) = 0;
  virtual std::string prefixToPostfix(std::string inStr) = 0;
};

#endif /* NOTATIONCONVERTERINTERFACE_H */