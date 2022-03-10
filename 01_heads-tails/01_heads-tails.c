#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(void) {
  srand(time(NULL));

  int heads = (rand() % 2);

  if (heads) {
    printf("Heads!\n");
  } else {
    printf("Tails!\n");
  }
}
