#include <gtest.h>
#include "polinom.h"

TEST(Polynom, create_polynom) 
{
    ASSERT_NO_THROW(Polynom("5x^2y^2z+13x^3-z+24"));
}

TEST(Polynom, create_empty_polynom) 
{
    ASSERT_NO_THROW(Polynom());
}

TEST(Polynom, can_add_polynoms) 
{
    Polynom p1("x^2+y^2");
    Polynom p2("x");
    Polynom p3 = p1 + p2;
    Polynom p4("x^2+x+y^2");
    ASSERT_EQ(p3, p4);
}

TEST(Polynom, can_sub_polynoms)
{
    Polynom p1("x^2+y^2");
    Polynom p2("x");
    Polynom p3 = p1 - p2;
    Polynom p4("x^2-x+y^2");
    ASSERT_EQ(p3, p4);
}

TEST(Polynom, can_mul_scalar_and_polynom)
{
    Polynom p1("x^2+y^2");
    Polynom p2 = p1 * 12;
    Polynom p3("12x^2+12y^2");
    ASSERT_EQ(p2, p3);
}

TEST(Polynom, can_mul_zero_and_polynom)
{
    Polynom p1("x^2+y^2");
    Polynom p2 = p1 * 0;
    Polynom p3("0");
    ASSERT_EQ(p2, p3);
}

TEST(Polynom, can_mul_polynom_and_polynom)
{
    Polynom p1("yz");
    Polynom p2("x^5");
    Polynom p3 = p1 * p2;
    Polynom p4("x^5yz");
    ASSERT_EQ(p3, p4);
}

TEST(Polynom, can_right_count_example)
{
    Polynom p1("x^2+y^2");
    Polynom p2("x");
    Polynom p3 = p1 + p2;

    Polynom p4("yz");
    Polynom p5("x^5");
    Polynom p6 = p3 + p5 * p4;

    Polynom p7("x^5yz+x^2+x+y^2");
    ASSERT_EQ(p6, p7);
}

TEST(Polynom, can_right_count_double_value)
{
    Polynom p1("x^5yz+x^2+x+y^2");
    double a= p1.value_pol(1, 2, 2);
    ASSERT_EQ(a, 10);
}

TEST(Polynom, can_right_count_example_and_double_value)
{
    Polynom p1("3x^2yz^2+10xy^2-7yz+x-12");
    Polynom p2("x+2");

    Polynom p3("-5xyz+7yz+18");
    Polynom p4("-x^4yz^3-8xy^2z+3z");

    Polynom p5 = p4 + p3 * (-4);
    Polynom p6 = p1 * p2 - p5;

    Polynom p7("x^4yz^3+3x^3yz^2+10x^2y^2+6x^2yz^2+x^2+8xy^2z+20xy^2-27xyz-10x+14yz-3z+48");
    ASSERT_EQ(p6, p7);

    double a = p6.value_pol(1, 1, 1);
    ASSERT_EQ(a, 71);
}