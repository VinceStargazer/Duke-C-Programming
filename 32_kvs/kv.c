#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "kv.h"

void strip_line(char * line) {
  char * p = strchr(line, '\n');
  assert(p != NULL);
  *p = '\0';
}

kvpair_t * pair_from_line(char * line) {
  kvpair_t * res = malloc(sizeof(*res));
  strip_line(line);
  char * equal = strchr(line, '=');
  assert(equal != NULL);
  res -> key = strndup(line, strlen(line) - strlen(equal));
  res -> val = strdup(equal + 1);
  return res;
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Can not open file '%s'\n", fname);
    return NULL;
  }
  kvarray_t * res = malloc(sizeof(*res));
  res -> arr = NULL;
  res -> size = 0;
  char * line = NULL;
  size_t sz = 0, n = 0;
  while (getline(&line, &sz, f) >= 0) {
    n++;
    res -> arr = realloc(res -> arr, n * sizeof(*(res -> arr)));
    res -> arr[n - 1] = pair_from_line(line);
    res -> size++;
  }
  
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "Can not close file '%s'\n", fname);
    return NULL;
  }
  return res;
}

void freeKVs(kvarray_t * pairs) {
  assert(pairs != NULL);
  for (size_t i = 0; i < pairs -> size; i++) {
    free(pairs -> arr[i] -> key);
    free(pairs -> arr[i] -> val);
    free(pairs -> arr[i]);
  }
  free(pairs -> arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  assert(pairs != NULL);
  for (size_t i = 0; i < pairs -> size; i++) {
    printf("key = '%s' value = '%s'\n", pairs -> arr[i] -> key, pairs -> arr[i] -> val);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  assert(pairs != NULL && key != NULL);
  for (size_t i = 0; i < pairs -> size; i++) {
    if (strcmp(pairs -> arr[i] -> key, key) == 0)
	return pairs -> arr[i] -> val;
  }
  return NULL;
}
