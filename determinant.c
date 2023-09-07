#include "matrix.h"

int determinant(matrix_t *A, double *result) {
  int flag = 0;
  if (A->rows < 1 || A->columns < 1) {
    return 1;
  }
  if (A->rows != A->columns) {
    return 2;
  }
  if (A->rows == 1 && A->columns == 1) {
    *result = A->matrix[0][0];
  } else {
    matrix_t B;
    double det = 0;
    calc_complements(A, &B);
    for (int j = 0; j < A->columns; j++)
      det += A->matrix[0][j] * B.matrix[0][j];
    *result = det;
    remove_matrix(&B);
  }
  return flag;
}
