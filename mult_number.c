#include "matrix.h"

int mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 2;
  if (A->matrix == NULL) {
    res = 1;
  } else if (A->rows < 1 || A->columns < 1) {
    res = 1;
  } else {
    res = 0;
    create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}
