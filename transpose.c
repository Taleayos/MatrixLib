#include "matrix.h"

int transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (A->matrix == NULL || A->rows < 1 || A->columns < 1) {
    res = 1;
  } else {
    create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}
