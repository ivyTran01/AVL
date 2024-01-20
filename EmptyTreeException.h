#ifndef EMPTYTREEEXCEPTION_H
#define EMPTYTREEEXCEPTION_H
#include<iostream>
#include<string>

class EmptyTreeException
{
private:
	std::string mes;
public:
	EmptyTreeException(const std::string& error);
	std::string getMessage() const;
};

#endif
