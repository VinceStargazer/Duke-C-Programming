#include <stdio.h>
#include <stdlib.h>

void rotate(char mat[10][10]) {
  for (int r = 0; r < 5; r++)
    for (int c = r; c < 9 - r; c++) {
      int temp = mat[r][c];
      mat[r][c] = mat[9 - c][r];
      mat[9 - c][r] = mat[9 - r][9 - c];
      mat[9 - r][9 - c] = mat[c][9 - r];
      mat[c][9 - r] = temp;
    }
}
