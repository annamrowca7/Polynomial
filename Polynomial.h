//Anna Mrowca
#pragma once
#include "Z2.h"
#include <iostream>

class Polynomial
{
private:
	unsigned int m_degree;
	Z2* m_coefficiens;
	std::string temp;

public:
	Polynomial();
	Polynomial(const Polynomial& a);
	Polynomial(unsigned int size, Z2* array);
	Polynomial& operator = (const Polynomial& a);
	//Polynomial& copy(Polynomial& a, const Polynomial& b);
	//Z2 get_coefficien(unsigned int i) { return m_coefficiens[i]; };
	unsigned int degree() const { return m_degree; };
	const  Z2 operator [](unsigned int index) const;
	Z2 operator [] (unsigned int index);
	Polynomial& operator += (const Polynomial& poly);
	Polynomial& operator *= (const Polynomial& poly);
	std::string toString(const std::string xVar);
	//void SetToZero();

	friend Polynomial& operator+(const Polynomial& poly1, const Polynomial& poly2);
	friend Polynomial& operator*(const Polynomial& poly1, const Polynomial& poly2);

	friend Polynomial operator/( Polynomial poly1,const Polynomial poly2);
	friend Polynomial operator%( Polynomial poly1,const Polynomial poly2);
	friend void mod(const Polynomial poly1, Polynomial poly2, Polynomial& q, Polynomial& r);

	friend std::ostream& operator <<(std::ostream& os, const Polynomial& poly);
	friend std::istream& operator >>(std::istream& in, Polynomial& poly);

	~Polynomial();

};

