#include "matrix.h"

int eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (A->matrix == NULL || B->matrix == NULL) {
    return FAILURE;
  }
  if (A->rows != B->rows || A->columns != B->columns) {
    return FAILURE;
  }
  if (A->rows < 1 || B->rows < 1 || A->columns < 1 || B->columns < 1) {
    return FAILURE;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (A->matrix[i][j] != B->matrix[i][j]) {
        if (module(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
          res = FAILURE;
        }
      }
    }
  }
  return res;
}

double module(double number) {
  if (number < 0) number *= -1;
  return number;
}
