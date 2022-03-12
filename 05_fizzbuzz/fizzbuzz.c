#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int range;
  if (argc < 2) {
    printf("Please supply a range!\n");
    exit(1);
  }

  range = atoi(argv[1]);
  if (!range) {
    printf("Please enter a valid range!\n");
    exit(1);
  }

  for (int i = 1; i <= range; i++) {
    if (i % 3 == 0 && i % 5 == 0) {
      printf("FizzBuzz\n");
    } else if (i % 3 == 0) {
      printf("Fizz\n");
    } else if (i % 5 == 0) {
      printf("Buzz\n");
    } else {
      printf("%d\n", i);
    }
  }
}
