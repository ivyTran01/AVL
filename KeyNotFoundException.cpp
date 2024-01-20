#include "KeyNotFoundException.h"
using namespace std;

KeyNotFoundException::KeyNotFoundException(const std::string &error)
{
	mes = error;
}

std::string KeyNotFoundException::getMessage() const
{
	return mes;
}
