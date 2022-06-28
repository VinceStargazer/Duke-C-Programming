#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  int arr[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  if (maxSeq(arr, 10) != 4) {
    printf("Failed on 1");
    return EXIT_FAILURE;
  }
  int arr2[] = {3, 7, 9, 732, 918, 2, 4, 67, 93, 94, 102};
  if (maxSeq(arr2, 11) != 6) {
    printf("Failed on 2");
    return EXIT_FAILURE;
  }
  int arr3[] = {8, 8, 8, 8, 8};
  if (maxSeq(arr3, 5) != 1) {
    printf("Failed on 3");
    return EXIT_FAILURE;
  }
  int arr4[] = {};
  if (maxSeq(arr4, 0) != 0) {
    printf("Failed on 4");
    return EXIT_FAILURE;
  }
  int arr5[] = {4, 8, 9, 12, -13, -11, -5, 0, 2};
  if (maxSeq(arr5, 9) != 5) {
    printf("Failed on 5");
    return EXIT_FAILURE;
  }
  printf("All passed!");
  return EXIT_SUCCESS;
}
