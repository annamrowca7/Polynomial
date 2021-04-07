//Anna Mrowca
#include <iostream>
#include "Z2.h"

Z2::operator short int() const
{
	short int output;
	output = (short int)modulo;
	return output;
}

Z2& Z2::operator +=(const Z2& number)
{
	modulo = (modulo + number.modulo) % 2;
	return *this;
}
Z2& Z2::operator *=(const Z2& number)
{
	modulo = (modulo * number.modulo) % 2;
	return *this;
}
Z2& Z2::operator /=(const Z2& number)
{
	if (number.modulo == 0)
	{
		std::cout << "Dzielenie przez zero" << std::endl;
		return *this;
	}
	else
		modulo = (modulo / number.modulo) % 2;
	return *this;
}
Z2 operator +(Z2 number1, const Z2& number2)
{
	return Z2((short)number1 + (short)number2);
}
Z2 operator /(Z2 number1, const Z2& number2)
{
	if (number2.modulo == 0)
	{
		std::cout << "Dzielenie przez zero" << std::endl;
		return number1;
	}
	else
	{
		return Z2((short)number1 / (short)number2);
	}
}
Z2 operator *(Z2 number1, const Z2& number2)
{
	return Z2((short)number1 * (short)number2);
}

std::ostream& operator << (std::ostream& os, const Z2& number)
{
	os << number.modulo;
	return os;
}


