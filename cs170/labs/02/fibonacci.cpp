/*!
filename   fibonacci.cpp
author     Marcus Meng
DP email   marcus.meng@digipen.edu
course     CS170
section    B
assignment lab2
due date   January 29, 2010

\brief
	Contains some code to calculate and display fibonacci numbers.
*/

#include <iostream> // cout
#include <iomanip>  // 

/*!
\brief
	Collects sane input for the fibonacci function to calculate.

\param max
	The upper bound on calculations.

\return
	The highest fibonacci number index to calculate to.
*/
int get_fib_input(int max)
{
  int input;

  do
  {
    std::cout << "Enter the Fibonacci number to calculate.\n";
    std::cout << "The number must be between 2 and " << max << ".";
    std::cout << " Enter 1 to quit: ";
    std::cin >> input;
  } while (input < 1 || input > max);

  return input;
}

/*!
\brief
	Displays a formatted table of fibonacci numbers and quotients.

\param max
	The fibonacci number to calculate up to.
*/
void fibonacci(int max)
{
  std::cout << "           Fibonacci        Fibonacci" << std::endl;
  std::cout << " N           number          quotient" << std::endl;
  std::cout << "-------------------------------------" << std::endl;
  std::cout << " 0             0                  N/A" << std::endl;
  std::cout << " 1             1                  N/A" << std::endl;

  int count = max;
  int fib1 = 0, fib2 = 1;
  for (int i = 2; i <= count; i++)
  {
    int next = fib1 + fib2;
    
    // Add statements to print here...
    // "%2i%14.0f%21.16f\n"
    std::cout << std::setw(2) << i;
    std::cout << std::setw(14) << next;
    std::cout << std::setw(21) << std::setprecision(16) << std::showpoint;
    std::cout << static_cast<double>(next) / fib2 << std::endl;
    std::cout.unsetf(std::ios_base::showpoint);

    fib1 = fib2;
    fib2 = next;
  }
}

