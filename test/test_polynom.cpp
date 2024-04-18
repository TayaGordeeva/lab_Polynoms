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