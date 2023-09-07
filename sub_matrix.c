#include "matrix.h"

int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (A->matrix == NULL || B->matrix == NULL) {
    res = 1;
  } else if (A->rows < 1 || B->rows < 1 || A->columns < 1 || B->columns < 1) {
    res = 1;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    res = 2;
  } else {
    create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return res;
}
