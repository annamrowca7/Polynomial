//Anna Mrowca
#include <iostream>
#include "Polynomial.h"
#include "Z2.h"
#include <sstream>
#include <string>

Polynomial::Polynomial()
{
	m_degree = 0;

	m_coefficiens = new Z2[1];
	m_coefficiens[0] = Z2(0);

//	m_coefficiens = tmp;
}

Polynomial::Polynomial(const Polynomial& a)
{
	m_degree = a.degree();
	m_coefficiens = new Z2[m_degree+1];

	for (unsigned int i = 0; i <= m_degree; i++)
		m_coefficiens[i] = a.m_coefficiens[i];

}
//
//void Polynomial::SetToZero()
//{
//	for (unsigned int i = 0; i <= m_degree; i++)
//	{ 
//		
//		m_coefficiens[i] = 0;
//	}
//}


Polynomial::Polynomial(unsigned int size, Z2* array)
{
	m_degree = size;
	m_coefficiens = new Z2[m_degree+1];

	for (unsigned int i = 0; i <= m_degree; i++)
		m_coefficiens[i] = array[i];
	

}


Polynomial& Polynomial::operator = (const Polynomial& a) {
	m_degree = a.m_degree;
	delete[] m_coefficiens;
	m_coefficiens = new Z2[m_degree + 1];
	for (unsigned int i = 0; i <= m_degree; i++)
		m_coefficiens[i] = a.m_coefficiens[i];
	return*this;
};

Polynomial::~Polynomial()
{

	delete[]m_coefficiens;
}

const Z2 Polynomial:: operator [](unsigned int index) const
{
	if (index<0 || index > m_degree)
	{
		std::cout << "Niepoprawny indeks wielomianu\n";
		return m_coefficiens[0];
	}
	else
		return m_coefficiens[index];
}

Z2 Polynomial:: operator [](unsigned int index)
{
	if (index<0 || index > m_degree)
	{
		std::cout << "Niepoprawny indeks wielomianu" << std::endl;
		return m_coefficiens[0];
	}
	else
		return m_coefficiens[index];	
}

Polynomial& Polynomial::operator+=(const Polynomial& poly)
{
	unsigned int new_degree = (poly.m_degree > m_degree) ? poly.m_degree : m_degree;
	Z2* prod = new Z2[new_degree + 1];

	for (unsigned int i = 0; i <= new_degree; i++)
	{
		prod[i] = 0;
	}

	for (unsigned int i = 0; i <= poly.m_degree; i++)
	{
		prod[i] += poly.m_coefficiens[i];
	}
	for (unsigned int i = 0; i <= m_degree; i++)
	{
		prod[i] += m_coefficiens[i];
	}


	m_coefficiens = prod;
	m_degree = new_degree;
	
	return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& poly)
{

	Z2* coef = new Z2[m_degree + poly.m_degree+1];

	for (unsigned int i = 0; i <= m_degree + poly.m_degree ; i++)
		coef[i] = Z2(0);

	for (unsigned int i = 0; i <= m_degree; i++)
	{
		for (unsigned int j = 0; j <= poly.m_degree; j++)
			coef[i + j] += Z2(m_coefficiens[i] * poly.m_coefficiens[j]);
	}

	this->m_coefficiens = coef;
	this->m_degree = m_degree + poly.m_degree;
	
	return *this;
}

Polynomial operator/(Polynomial poly1,const Polynomial poly2)
{
	if (poly2.m_degree == 0 && poly2.m_coefficiens[0] == 0)
	{
		std::cout << "Dzielenie przez zero\n";
		return poly2;
	}
	else if (poly1.m_degree == 0 && poly2.m_degree == 0 && poly1.m_coefficiens[0] == 0)
	{
		Polynomial q;
		return q;
	}
	else if (poly2.m_degree == 0 && poly2.m_coefficiens[0] == 1)
	{
		return poly1;
	}
	else
	{
		Polynomial q, r;
		q.m_degree = poly1.m_degree - poly2.m_degree;
		r.m_degree = poly1.m_degree - poly2.m_degree;
		unsigned int d_degree = 0;
		Z2* poly2_resize = new Z2[poly1.m_degree + 1];
		for (unsigned int i = 0; i <= poly2.m_degree; i++)
			poly2_resize[i] = poly2.m_coefficiens[i];
		Z2* q_tab = new Z2[q.m_degree + 1];
		Z2* r_tab = new Z2[r.m_degree + 1];
		Z2* d = new Z2[poly1.m_degree + 1];
		Polynomial to_print;

		if (poly1.m_degree >= poly2.m_degree)
		{
			while (poly1.m_degree >= poly2.m_degree)
			{/*
				std::cout << "-------------" << std::endl;*/
				for (unsigned int i = 0; i <= poly2.m_degree; i++)
					d[i + poly1.m_degree - poly2.m_degree] = poly2.m_coefficiens[i];

				d_degree = poly1.m_degree;

			/*	d_degree = poly1.m_degree;
				to_print.m_coefficiens = d;
				to_print.m_degree = d_degree;
				std::cout << to_print << std::endl;*/

				q_tab[poly1.m_degree - poly2.m_degree] = poly1[poly1.m_degree] / d[d_degree];

				/*to_print.m_coefficiens = q_tab;
				to_print.m_degree = q.m_degree;
				std::cout << to_print << std::endl;*/

				for (unsigned int i = 0; i <= q.m_degree; i++)
					d[i] = d[i] * q_tab[poly1.m_degree - poly2.m_degree];

			/*	to_print.m_coefficiens = d;
				to_print.m_degree = d_degree;
				std::cout << to_print << std::endl;*/

				for (unsigned int i = 0; i <= poly1.m_degree; i++)
					poly1.m_coefficiens[i] = poly1.m_coefficiens[i] - d[i];

				//std::cout << poly1 << std::endl;

				poly1.m_degree--;

			}
		}
		for (unsigned int i = 0; i <= poly1.m_degree; i++)
			r_tab[i] = poly1.m_coefficiens[i];

		q.m_coefficiens = q_tab;
		r.m_coefficiens = r_tab;

		return q;
	}
}

Polynomial operator%( Polynomial poly1 ,const  Polynomial poly2)
{

	if (poly2.m_degree == 0 && poly2.m_coefficiens[0] == 0)
	{
		std::cout << "Dzielenie przez zero\n";
		return poly2;
	}
	else if (poly1.m_degree == 0 && poly2.m_degree == 0 && poly1.m_coefficiens[0] == 0)
	{
		Polynomial r;
		return r;
	}
	else if (poly2.m_degree == 0 && poly2.m_coefficiens[0] == 1)
	{
		Polynomial r;
		return r;
	}
	else
	{
		Polynomial q, r;
		q.m_degree = poly1.m_degree - poly2.m_degree;
		r.m_degree = poly1.m_degree - poly2.m_degree;
		unsigned int d_degree = 0;
		Z2* poly2_resize = new Z2[poly1.m_degree + 1];
		for (unsigned int i = 0; i <= poly2.m_degree; i++)
			poly2_resize[i] = poly2.m_coefficiens[i];
		Z2* q_tab = new Z2[q.m_degree + 1];
		Z2* r_tab = new Z2[r.m_degree + 1];
		Z2* d = new Z2[poly1.m_degree + 1];
		Polynomial to_print;

		if (poly1.m_degree >= poly2.m_degree)
		{
			while (poly1.m_degree >= poly2.m_degree)
			{
				/*std::cout << "-------------" << std::endl;*/
				for (unsigned int i = 0; i <= poly2.m_degree; i++)
					d[i + poly1.m_degree - poly2.m_degree] = poly2.m_coefficiens[i];

		/*		d_degree = poly1.m_degree;
				to_print.m_coefficiens = d;
				to_print.m_degree = d_degree;
				std::cout << to_print << std::endl;*/

				q_tab[poly1.m_degree - poly2.m_degree] = poly1[poly1.m_degree] / d[d_degree];

			/*	to_print.m_coefficiens = q_tab;
				to_print.m_degree = q.m_degree;
				std::cout << to_print << std::endl;*/

				for (unsigned int i = 0; i <= q.m_degree; i++)
					d[i] = d[i] * q_tab[poly1.m_degree - poly2.m_degree];

			/*	d_degree = poly1.m_degree;
				to_print.m_coefficiens = d;
				to_print.m_degree = d_degree;
				std::cout << to_print << std::endl;*/

				for (unsigned int i = 0; i <= poly1.m_degree; i++)
					poly1.m_coefficiens[i] = poly1.m_coefficiens[i] - d[i];

				poly1.m_degree--;
			}
		}
		for (unsigned int i = 0; i <= poly1.m_degree; i++)
			r_tab[i] = poly1.m_coefficiens[i];

		q.m_coefficiens = q_tab;
		r.m_coefficiens = r_tab;



		return r;
	}
}

void mod( Polynomial poly1,const Polynomial poly2, Polynomial& q, Polynomial& r)
{
	if (poly2.m_degree == 0 && poly2.m_coefficiens[0] == 0)
	{
		std::cout << "Dzielenie przez zero\n";
	}
	else if (poly2.m_degree == 0 && poly2.m_coefficiens[0] == 1)
	{
		q = poly1;		
	}
	else if (poly1.m_degree == 0 && poly2.m_degree == 0 && poly1.m_coefficiens[0] == 0)
	{

	}
	else
	{
		q.m_degree = poly1.m_degree - poly2.m_degree;
		r.m_degree = poly1.m_degree - poly2.m_degree;
		unsigned int d_degree = 0;
		Z2* poly2_resize = new Z2[poly1.m_degree + 1];
		for (unsigned int i = 0; i <= poly2.m_degree; i++)
			poly2_resize[i] = poly2.m_coefficiens[i];
		Z2* q_tab = new Z2[q.m_degree + 1];
		Z2* r_tab = new Z2[r.m_degree + 1];
		Z2* d = new Z2[poly1.m_degree + 1];
		Polynomial to_print;

		if (poly1.m_degree >= poly2.m_degree)
		{
			while (poly1.m_degree >= poly2.m_degree)
			{
				for (unsigned int i = 0; i <= poly2.m_degree; i++)
					d[i + poly1.m_degree - poly2.m_degree] = poly2.m_coefficiens[i];

				d_degree = poly1.m_degree;

				q_tab[poly1.m_degree - poly2.m_degree] = poly1[poly1.m_degree] / d[d_degree];

				for (unsigned int i = 0; i <= q.m_degree; i++)
					d[i] = d[i] * q_tab[poly1.m_degree - poly2.m_degree];

				for (unsigned int i = 0; i <= poly1.m_degree; i++)
					poly1.m_coefficiens[i] = poly1.m_coefficiens[i] - d[i];

				poly1.m_degree--;
			}
		}
		for (unsigned int i = 0; i <= poly1.m_degree; i++)
			r_tab[i] = poly1.m_coefficiens[i];

		q.m_coefficiens = q_tab;
		r.m_coefficiens = r_tab;

	}

}

std::string Polynomial::toString(const std::string xVar)
{
	std::stringstream poly;
	if (m_degree == 0 && m_coefficiens[0] == 0)
	{
		poly << 0;
	}
	else
	{
		bool printed = false;
		if (m_coefficiens[0].modulo != 0)
		{
			poly << m_coefficiens[0];
			printed = true;

		}
		for (unsigned int i = 1; i <= m_degree; i++)
		{
			if (m_coefficiens[i].modulo != 0)
			{
				if (m_coefficiens[0].modulo == 0 && i == 1)
				{
					poly << xVar << "^" << i;
					printed = true;
				}
				else
				{
					if (printed == false)
					{
						poly << xVar << "^" << i;
						printed = true;
					}
					else
						poly << "+" << xVar << "^" << i;
				}
			}
		}
		if (printed == false)
			poly << 0;
	}
	return poly.str();
}

Polynomial& operator+(const Polynomial& poly1, const Polynomial& poly2)
{
	unsigned int new_m_degree = (poly1.m_degree > poly2.m_degree) ? poly1.m_degree : poly2.m_degree;
	Z2* prod = new Z2[new_m_degree + 1];
	Polynomial* temp = new Polynomial();

	for (unsigned int i = 0; i <= new_m_degree; i++)
	{
		prod[i] = Z2(0);
		if (i <= poly1.m_degree)
			prod[i] = prod[i] + poly1.m_coefficiens[i];

		if (i <= poly2.m_degree)
			prod[i] = Z2(prod[i] + poly2.m_coefficiens[i]);
	}

	temp->m_degree = new_m_degree;
	temp->m_coefficiens = prod;

	return *temp;
}

Polynomial& operator*(const Polynomial& poly1, const Polynomial& poly2)
{

	Polynomial* temp = new Polynomial();
	temp->m_degree = poly1.m_degree + poly2.m_degree;
	Z2* prod = new Z2[temp->m_degree + 1];

	for (unsigned int i = 0; i <= temp->m_degree; i++)
		prod[i] = Z2(0);

	for (unsigned int i = 0; i <= poly1.m_degree; i++)
	{
		for (unsigned int j = 0; j <= poly2.m_degree; j++)
		{
			prod[i + j] += Z2(poly1.m_coefficiens[i] * poly2.m_coefficiens[j]);

		}
	}
	temp->m_coefficiens = prod;

	return *temp;
}


std::ostream& operator <<(std::ostream& os, const Polynomial& poly)
{
	
	//return poly.temp;
	os << poly.temp;

	/*os << "{";
	for (unsigned int i = 0; i <= poly.m_degree; i++)
	{
		os << poly.m_coefficiens[i];
		if (i + 1 <= poly.m_degree )
			os << ",";
		else
			os << "}";
	}
	*/
	return os;
}

std::istream& operator >>(std::istream& in, Polynomial& poly)
{

	std::string a(std::istreambuf_iterator<char>(in), {});
	unsigned int start = a.find('{');
	a.erase(0, start+1);
	unsigned int end = a.find('}');
	a.erase(end+1, a.length());

	poly.temp = "{" + a;

	unsigned int i = a.length();

	unsigned int new_degree = i / 2 - 1;

	Z2* coef_new = new Z2[new_degree + 1];
	unsigned int k = 0;
	for (unsigned int j = 0; j < i; j = j + 2)
	{
		int coef = a[j] - '0';
		coef_new[k] = Z2(coef);
		k++;
	}

	poly.m_degree = new_degree;
	poly.m_coefficiens = coef_new;

	return in;
}
