#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int findMax(int * arr, int size) {
  int idx = 0, max = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
      idx = i;
    }
  }
  return idx;
}

void decrypt(FILE * f) {
  int count[26] = {0};
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c) - 'a';
      count[c]++;
    }
  }
  int maxIdx = findMax(count, 26);
  int offset = maxIdx + 'a' - 'e';
  if (offset < 0) offset += 26;
  printf("%d\n", offset);
}

int main(int argc, char ** argv) {  
  if (argc != 2) {    
    fprintf(stderr,"Usage: breaker inputFileName\n");    
    return EXIT_FAILURE;  
  } 
  FILE * f = fopen(argv[1], "r");  
  if (f == NULL) {    
    perror("Could not open file");    
    return EXIT_FAILURE;  
  }  
  decrypt(f);  
  if (fclose(f) != 0) {    
    perror("Failed to close the input file!");    
    return EXIT_FAILURE;  
  }  
  return EXIT_SUCCESS;
}
