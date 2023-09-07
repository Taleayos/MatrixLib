#include "matrix.h"

int calc_complements(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (A->rows < 1 || A->columns < 1) {
    return 1;
  }
  if (A->rows != A->columns) {
    return 2;
  }
  create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < result->rows; i++)
    for (int j = 0; j < result->columns; j++) {
      Minor(i, j, A, &(result->matrix[i][j]));
      result->matrix[i][j] *= pow(-1, i + j);
    }
  return res;
}

void Minor(int row, int col, matrix_t *A, double *result) {
  matrix_t B;
  create_matrix(A->rows - 1, A->columns - 1, &B);
  for (int x = 0, i = 0; i < A->rows; i++) {
    if (i != row) {
      for (int y = 0, j = 0; j < A->columns; j++)
        if (j != col) B.matrix[x][y++] = A->matrix[i][j];
      x++;
    }
  }
  determinant(&B, result);
  remove_matrix(&B);
}
