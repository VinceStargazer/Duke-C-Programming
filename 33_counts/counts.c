#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t * res = malloc(sizeof(*res));
  res -> arr = malloc(sizeof(*(res -> arr)));
  res -> size = 0;
  return res;
}

void addCount(counts_t * c, const char * name) {
  if (c == NULL) return;
  char * str = NULL;
  if (name == NULL) str = strdup("unknown");
  else str = strdup(name);
  for (size_t i = 0; i < c -> size; i++) {
    if (strcmp(c -> arr[i] -> target, str) == 0) {
      c -> arr[i] -> count++;
      free(str);
      return;
    }
  }
  c -> arr = realloc(c -> arr, (c -> size + 1) * sizeof(*(c -> arr)));
  c -> arr[c -> size] = malloc(sizeof(*(c -> arr[c -> size])));
  c -> arr[c -> size] -> target = strdup(str);
  c -> arr[c -> size] -> count = 1;
  c -> size++;
  free(str);
}

void printCounts(counts_t * c, FILE * outFile) {
  if (c == NULL || outFile == NULL) return;
  int unknown = -1;
  for (size_t i = 0; i < c -> size; i++) {
    if (strcmp(c -> arr[i] -> target, "unknown") == 0) {
      unknown = i;
      continue;
    }
    fprintf(outFile, "%s: %d\n", c -> arr[i] -> target, c -> arr[i] -> count);
  }
  if (unknown > -1) {
    fprintf(outFile, "<unknown> : %d\n", c -> arr[unknown] -> count);
  }
}

void freeCounts(counts_t * c) {
  if (c == NULL) return;
  for (size_t i = 0; i < c -> size; i++) {
    free(c -> arr[i] -> target);
    free(c -> arr[i]);
  }
  free(c -> arr);
  free(c);
}
