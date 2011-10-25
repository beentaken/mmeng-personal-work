#include <stdio.h>     /* printf                         */
#include "fractions.h" /* struct FRACTION, add_fractions */

struct FRACTION make_fraction(int numerator, int denominator)
{
  struct FRACTION f;

  f.numerator = numerator;
  f.denominator = denominator;

  return f;
}

void test_fraction(int numerator1, int denominator1, 
                   int numerator2, int denominator2)
{
  struct FRACTION a = make_fraction(numerator1, denominator1);
  struct FRACTION b = make_fraction(numerator2, denominator2);

  struct FRACTION c = add_fractions(&a, &b);

  printf("%i/%i + %i/%i = %i/%i\n", a.numerator, a.denominator,
                                    b.numerator, b.denominator,
                                    c.numerator, c.denominator);
}

void testGCD(void)
{
  int m, n;

  m = 15; n = 18; /* GCD is 3 */
  printf("GCD of %i and %i is %i\n", m, n, GCD(m, n));
  printf("GCD of %i and %i is %i\n", n, m, GCD(n, m));

  m = 80; n = 20; /* GCD is 20 */
  printf("GCD of %i and %i is %i\n", m, n, GCD(m, n));
  printf("GCD of %i and %i is %i\n", n, m, GCD(n, m));

  m = 21; n = 47; /* GCD is 1 */
  printf("GCD of %i and %i is %i\n", m, n, GCD(m, n));
  printf("GCD of %i and %i is %i\n", n, m, GCD(n, m));

  m = 68; n = 153; /* GCD is 17 */
  printf("GCD of %i and %i is %i\n", m, n, GCD(m, n));
  printf("GCD of %i and %i is %i\n", n, m, GCD(n, m));
}

int main(void)
{
  testGCD();

#if 1
  test_fraction(2, 3, 1, 6);
  test_fraction(1, 5, 4, 9);
  test_fraction(3, 7, 12, 21);
  test_fraction(5, 8, 3, 16);
  test_fraction(7, 8, 3, 12);
  test_fraction(0, 8, 3, 16);
  test_fraction(1, 1, 3, 16);
  test_fraction(5, 8, -3, 16);
  test_fraction(1, 5, -4, 9);
  test_fraction(-1, 5, -4, 9);
#endif

  return 0;
}

