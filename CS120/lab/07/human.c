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
		int number = RandomInt(low, high);
		int counter = 1;

		/* Initial setup */
		do
		{
			printf("Guess the number I'm thinking of (between %d and %d, "
				"0 = quit): ", low, high);
			input = get_input(low, high);
		} while (input != 0 && input == -1);

		while (input != number && input != 0)
		{
			if (number < input)
			{
				printf("Too high. Guess again: ");
			}
			else if (number > input)
			{
				printf("Too low. Guess again: ");
			}

			input = get_input(low, high);
			++counter;
		}

		if (input)
		{
			printf("You guessed the number in %d tries!\n", counter);

			printf("Play again? (1=yes, 0=no): ");
			scanf("%d", &input);
			myfflush();
		}
	} while (input);
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

