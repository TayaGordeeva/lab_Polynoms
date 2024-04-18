// Polinoms.cpp 

#include <iostream>
#include "polinom.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

    Polynom p1("x^2+y^2");
	Polynom p2("x");
	Polynom p3 = p1 + p2;
	p3.Print();
    cout << endl;
    
    Polynom p4("yz");
    Polynom p5("x^5");
    Polynom p6 = p3+p5*p4;
    p6.Print();
    return 0;

	

}

