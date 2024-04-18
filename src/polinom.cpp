#include "polinom.h"
#include <stdlib.h>

Polynom::Polynom(string polynom) {
	pFirst = nullptr;
	if (polynom == "0") return;

	int coef = 0, sign=1;
	int t = 0, pos=0;
	string deg = "000";
	string num = "";

	for (int i = 0; i < polynom.length(); i++) 
	{
		if ((i == polynom.length()) or (polynom[i] == '-') or (polynom[i] == '+'))
		{
			if (not(num.empty()))
			{
				coef = atoi(num.c_str()) * sign;
				AddMonom(coef, atoi(deg.c_str()));
				num = ""; deg = "000";
			}

			if ((i < polynom.length()) and (polynom[i] == '-'))
				sign = -1;
			else
				sign = 1;
		}

		else if (((int(polynom[i]) - int('0')) >= 0) and ((int(polynom[i]) - int('0')) < 10))
			num += polynom[i];

		else if ((polynom[i] == 'x') or (polynom[i] == 'y') or (polynom[i] == 'z'))
		{
			if ((num.empty()) and ((i == 0) or (polynom[i-1] != '^')))
				num = "1";

			if (polynom[i] == 'x') pos = 0;
			else if (polynom[i] == 'y') pos = 1;
			else if (polynom[i] == 'z') pos = 2;
			i++;

			if ((i < polynom.length()) and (polynom[i] == '^'))
			{
				i++;
				string exp = "";
				while ((i < polynom.length()) and (((int(polynom[i]) - int('0')) >= 0) and ((int(polynom[i]) - int('0')) < 10)))
					exp += polynom[i++];
				i--;
				if (exp.empty()) deg[pos] = '1';
				else deg[pos] = exp[0];
			}
			else
			{
				deg[pos] = '1';
				i--;
			}

			
		}
	}
	if (not(num.empty()))
		{
			coef = atoi(num.c_str()) * sign;
			AddMonom(coef, atoi(deg.c_str()));
			num = ""; deg = "000";
		}
}

void Polynom::AddMonom(int coef, int deg)
{
	Monom *newm = new Monom(deg, coef);

	if ((pFirst == nullptr) or (deg > pFirst->value))
	{
		newm->pNext = pFirst;
		pFirst = newm;
	}
	else
	{
		Monom* tmp = pFirst;
	    Monom* p = nullptr;

		while ((tmp != nullptr) and (tmp->value > deg))
		{
			p = tmp;
			tmp = tmp->pNext;
		}

		if ((tmp != nullptr) and (tmp->value == deg))
		{
			tmp->coeff += coef;
			if (tmp->coeff == 0)
				if (p == nullptr) pFirst = tmp->pNext;
				else p->pNext = tmp->pNext;
		}
		else
		{
			newm->pNext = tmp;
			if (p == nullptr) pFirst = newm;
			else p->pNext = newm;
		}
	}
}

Polynom Polynom::operator +(const Polynom& p) const
{
	Polynom res;
	Monom* m1 = this->pFirst;
	Monom* m2 = p.pFirst;
	while ((m1 != nullptr) or (m2 != nullptr))
	{
		if (m1 == nullptr)
		{
			res.AddMonom(m2->coeff, m2->value);
			m2 = m2->pNext;
		}

		else if (m2 == nullptr)
		{
			res.AddMonom(m1->coeff, m1->value);
			m1 = m1->pNext;
		}

		else if (m1->value == m2->value)
		{
			int newcoeff = m1->coeff + m2->coeff;
			if (newcoeff != 0) res.AddMonom(newcoeff, m1->value);
			m1 = m1->pNext;
			m2 = m2->pNext;
		}

		else if (m1->value < m2->value)
		{
			res.AddMonom(m2->coeff, m2->value);
			m2 = m2->pNext;
		}

		else
		{
			res.AddMonom(m1->coeff, m1->value);
			m1 = m1->pNext;
		}
	}
	return res;
}

Polynom Polynom::operator*(double c) const
{
	Polynom res;
	if (c == 0) return res;

	for (Monom* i = pFirst; i != nullptr; i = i->pNext)
		res.AddMonom((i->coeff) * c, i->value);
	
	return res;
}

Polynom Polynom::operator -(const Polynom& p) const
{
	Polynom res;
	res = *this + p * (-1);
	return res;
}

Polynom Polynom::operator* (const Polynom& p) const
{
	Polynom res;
	for (Monom* m1 = pFirst; m1 != nullptr; m1 = m1->pNext)
		for (Monom* m2 = p.pFirst; m2 != nullptr; m2 = m2->pNext)
			res.AddMonom((m1->coeff) * (m2->coeff), (m1->value) + (m2->value));
	return res;
}

bool Polynom::operator ==(const Polynom& p) const
{
	Monom* m1 = pFirst;
	Monom* m2 = p.pFirst;

	while ((m1 != nullptr) and (m2 != nullptr))
	{
		if (((m1->coeff) != (m2->coeff)) or ((m1->value) != (m2->value))) return false;
		m1 = m1->pNext;
		m2 = m2->pNext;
	}

	if ((m1 == nullptr) and (m2 == nullptr))
		return true;
	else return false;
}

Iterator Polynom::begin()
{
	return Iterator(pFirst);
}

Iterator Polynom::end()
{
	return Iterator(nullptr);
}


void Polynom::Print()
{
	if (pFirst == nullptr)
	{
		cout << "0";
		return;
	}

	for (auto i = begin(); i != end(); ++i)
	{
		Monom m = *i;

		if ((i != begin()) and (m.coeff > 0)) cout << "+";
		if ((m.coeff == 1) and (m.value == 0)) cout << m.coeff;
		if (m.coeff != 1) cout << m.coeff;

		int v_x = m.value / 100;
		int v_y = (m.value / 10) % 10;
		int v_z = m.value % 10;

		if (v_x > 0)
			if (v_x == 1) cout << "x";
			else cout << "x^" << v_x;

		if (v_y > 0)
			if (v_y == 1) cout << "y";
			else cout << "y^" << v_y;

		if (v_z > 0)
			if (v_z == 1) cout << "z";
			else cout << "z^" << v_z;
	}
}
