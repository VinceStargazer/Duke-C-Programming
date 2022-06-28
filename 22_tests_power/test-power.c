#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

int main(void) {
  if (power(5, 0) != 1) exit(EXIT_FAILURE);
  if (power(47, 5) != 229345007) exit(EXIT_FAILURE);
  if (power(2, 15) != 32768) exit(EXIT_FAILURE);
  if (power(0, 0) != 1) exit(EXIT_FAILURE);
  if (power(0, 50) != 0) exit(EXIT_FAILURE);
  printf("All passed!\n");
  return EXIT_SUCCESS;
}
