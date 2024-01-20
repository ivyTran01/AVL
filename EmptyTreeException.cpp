#include "EmptyTreeException.h"
using namespace std;

EmptyTreeException::EmptyTreeException(const string& error)
{
	mes = error;
}

string EmptyTreeException::getMessage() const
{
	return mes;
}