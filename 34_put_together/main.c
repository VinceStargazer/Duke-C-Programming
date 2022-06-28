#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Can not open file '%s'\n", filename);
    return NULL;
  }
  counts_t * c = createCounts();
  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    char * p = strchr(line, '\n');
    *p = '\0';
    addCount(c, lookupValue(kvPairs, line));
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "Can not close file '%s'\n", filename);
    return NULL;
  }
  return c;
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    fprintf(stderr, "Lacking arguments");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  for (size_t i = 2; i < argc; i++) {
    counts_t * c = countFile(argv[i], kv);
    char * outName = malloc(strlen(argv[i]) + strlen(".counts") + 1);
    outName[0] = '\0';
    outName = strcat(outName, argv[i]);
    outName = strcat(outName, ".counts");
    FILE * f = fopen(outName, "w");
    printCounts(c, f);
    if (fclose(f) != 0) {
      fprintf(stderr, "Can not close file '%s'\n", outName);
      return EXIT_FAILURE;
    }
    free(outName);
    freeCounts(c);
  }
  freeKVs(kv);
  return EXIT_SUCCESS;
}
