#include <iostream> // cout
#include <cstdlib>  // atoi

void fibonacci(int max);
int get_fib_input(int max);

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cout << "Please specify a value.\n";
    return -1;
  }

  int max = std::atoi(argv[1]);
  int size = get_fib_input(max);
  if (size != 1)
    fibonacci(size);

  return 0;
}