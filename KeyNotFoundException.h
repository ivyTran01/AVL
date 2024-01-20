#ifndef KEYNOTFOUNDEXCEPTION_H
#define KEYNOTFOUNDEXCEPTION_H
#include<iostream>
#include<string>

class KeyNotFoundException
{
private:
	std::string mes;
public:
	KeyNotFoundException(const std::string& error);
	std::string getMessage() const;
};

#endif
