#include <stdio.h>  /* printf, scanf, getchar */
#include <stdlib.h> /* rand, srand, atoi     */
#include <time.h>   /* time                  */

/* flush out bad input */
void myfflush(void)
{
  int c;
  while((c = getchar()) != '\n' && c != EOF)
    /* discard */ ;
}

/* generate random numbers between low and high */
int RandomInt(int low, int high)
{
  int number;
  number = rand() % (high - low + 1) + low;
  return number;
}

int get_input(int low, int high)
{
	int input, got_input = 0;

	got_input = scanf("%d", &input);

	myfflush();

	if (got_input < 1 || ((input < low || input > high) && (input != 0)))
	{
		return -1;
	}

	return input;
}

void game_loop(int low, int high)
{
	int input;

	do
	{
		int number, guess, counter = 0;
		int current_low = low, current_high = high;

		do
		{
			printf("Pick a number for me to guess "
				"(between %d and %d, 0=quit): ", low, high);
			input = get_input(low, high);
		} while (input != 0 && input == -1);

		number = input;
		guess = low + (high - low) / 2;

		while (input != 0 && input != 3)
		{
			printf("Is the number %d? (1=too low, 2=too high, 3=correct, "
				"0=quit): ", guess);
			input = get_input(low, high);

			switch (input)
			{
				case 1:
					current_low = guess;
					guess = (current_high + guess) / 2;
					break;
				case 2:
					current_high = guess;
					guess = (guess +  current_low) / 2;
					break;
				case 0:
					return;
				default:
					break;
			}
			++counter;
		}

		if (input != 0)
		{
			printf("I guessed the number in %d tries!\n", counter);
			printf("Play again? (1=yes, 0=no): ");
			input = get_input(0, 1);
		}

	} while (input != 0);
}

int main(int argc, char **argv)
{
  int low;  /* the lower bound */
  int high; /* the upper bound */

    /* If the user didn't provide any arguments, quit */
  if (argc < 2)
  {
    printf("Usage: %s low high\n", argv[0]);
    printf("       low  - the lower bound\n");
    printf("       high - the upper bound\n\n");
    return -1;
  }

    /* Convert strings to integers */
  low = atoi(argv[1]);  
  high = atoi(argv[2]); 

  srand((unsigned)time(0));

  game_loop(low, high);
  
  return 0;
}

