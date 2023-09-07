#include "matrix.h"

int inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (A->rows < 1 || A->columns < 1) {
    return 1;
  }
  if (A->columns != A->rows) {
    return 2;
  }
  double det = 0;
  determinant(A, &det);
  if (det == 0.000000) {
    return 2;
  }
  matrix_t new = {0}, new_trans = {0};
  calc_complements(A, &new);
  transpose(&new, &new_trans);
  create_matrix(A->rows, A->rows, result);
  for (int x = 0; x < A->rows; x += 1) {
    for (int y = 0; y < A->rows; y += 1) {
      result->matrix[x][y] = new_trans.matrix[x][y] / det;
    }
  }
  remove_matrix(&new_trans);
  remove_matrix(&new);
  return res;
}
