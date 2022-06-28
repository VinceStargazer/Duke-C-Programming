#include <stdio.h>
#include <stdlib.h>

void rotate(int mat[10][10]) {
  for (int r = 0; r < 5; r++)
    for (int c = r; c < 9 - r; c++) {
      int temp = mat[r][c];
      mat[r][c] = mat[9 - c][r];
      mat[9 - c][r] = mat[9 - r][9 - c];
      mat[9 - r][9 - c] = mat[c][9 - r];
      mat[c][9 - r] = temp;
    }
}

int main(int argc, char ** argv) {
  if (argc != 2) {    
    fprintf(stderr,"Usage: rotate inputFileName\n");    
    return EXIT_FAILURE;  
  }
  FILE * f = fopen(argv[1], "r");  
  if (f == NULL) {    
    fprintf(stderr, "Could not open file");    
    return EXIT_FAILURE;  
  }  
  int mat[10][10];
  for (int r = 0; r < 10; r++) {
    for (int c = 0; c < 10; c++) {
      if ((mat[r][c] = fgetc(f)) == EOF || mat[r][c] == '\n') {
	fprintf(stderr, "Incorrect format");
	return EXIT_FAILURE;
      }
    }
    if (fgetc(f) != '\n') {
      fprintf(stderr, "Incorrect format");
      return EXIT_FAILURE;
    }
  }
  if (fgetc(f) != EOF) {
    fprintf(stderr, "Incorrect format");
    return EXIT_FAILURE;
  }
  rotate(mat);
  for (int r = 0; r < 10; r++) {
    for (int c = 0; c < 10; c++)
      printf("%c", mat[r][c]);
    printf("\n");
  }
  if (fclose(f) != 0) {    
    fprintf(stderr, "Failed to close the input file!");    
    return EXIT_FAILURE;  
  }  
  return EXIT_SUCCESS;
}
