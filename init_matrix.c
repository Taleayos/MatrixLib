#include "matrix.h"

void init_matrix_line(int rows, int colums, double mass[], matrix_t *res) {
  res->rows = rows;
  res->columns = colums;
  int k = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < colums; j++) {
      res->matrix[i][j] = mass[k];
      k++;
    }
  }
}

void init_matrix(int rows, int colums, int x, matrix_t *a) {
  a->rows = rows;
  a->columns = colums;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < colums; j++) {
      a->matrix[i][j] = x;
      x++;
    }
  }
}
void init_matrix_rand(int rows, int colums, matrix_t *a) {
  //    srand(time(NULL));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < colums; j++) {
      a->matrix[i][j] = (double)(rand() % 10000000 - 5000000) / 100000;
      //            a->matrix[i][j] = rand() % 100;
    }
  }
  a->rows = rows;
  a->columns = colums;
}
