//Anna Mrowca
#pragma once
#include <iostream>
class Z2 {
public:
	Z2() { modulo = 0; };
	Z2(short int a) { if (a > 0) modulo = a % 2; else modulo = -a % 2; };
	Z2& operator=(const Z2& a) { modulo = a.modulo; return *this; }
	operator short int() const;
	Z2& operator +=(const Z2&);
	Z2& operator *=(const Z2&);
	Z2& operator /=(const Z2&);
	friend Z2 operator +(Z2, const Z2&);
	friend Z2 operator /(Z2, const Z2&);
	friend Z2 operator *(Z2, const Z2&);
	friend std::ostream& operator << (std::ostream& os, const Z2&);


	int modulo;
};


