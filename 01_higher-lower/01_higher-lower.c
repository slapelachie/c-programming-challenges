#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int check_valid(char *);

void main(int argc, char *argv[]) {
  srand(time(NULL));

  char *rangeptr = (char *)malloc(sizeof(char) * 5);
  int range = 0;
  do {
    printf("Enter range: ");
    if (!fgets(rangeptr, 5, stdin) || !check_valid(rangeptr) ||
        atoi(rangeptr) <= 0) {
      printf("Please enter a valid number!\n");
      continue;
    }
    range = atoi(rangeptr);
  } while (range == 0);

  int random_number = (rand() % range) + 1;

  char *guessptr = (char *)malloc(sizeof(char) * 5);
  int guessed_number = 0;

  do {
    printf("Guess: ");
    if (!fgets(guessptr, 5, stdin) || !check_valid(guessptr)) {
      printf("Please enter a valid number!\n");
      continue;
    }

    guessed_number = atoi(guessptr);

    if (guessed_number == random_number) {
      printf("Correct!\n");
      exit(0);
    } else if (guessed_number > random_number) {
      printf("Too high!\n");
    } else if (guessed_number < random_number) {
      printf("Too low!\n");
    }
  } while (1);
}

int check_valid(char *input) {
  for (size_t i = 0; i < strlen(input); i++) {
    if (!isdigit(input[i]) && input[i] != '\n') {
      return 0;
    }
  }
  return 1;
}
