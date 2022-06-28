#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n <= 1) return n;
  size_t res = 1, len = 1;
  for (int i = 1; i < n; i++) {
    if (array[i] > array[i - 1]) {
      len++;
      if (len > res) res = len;
    } else {
      len = 1;
    }
  }
  return res;
}
