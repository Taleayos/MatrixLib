#include "test_matrix.h"

START_TEST(create_matrix_1) {
  matrix_t a;
  int res = create_matrix(3, 3, &a);
  init_matrix(3, 3, 4, &a);
  ck_assert_int_eq(res, 0);
  remove_matrix(&a);
}
END_TEST

START_TEST(create_matrix_2) {
  matrix_t a;
  int res = create_matrix(10, 10, &a);
  init_matrix_rand(10, 10, &a);
  ck_assert_int_eq(res, 0);
  remove_matrix(&a);
}
END_TEST

START_TEST(create_matrix_err) {
  matrix_t a;
  int res = create_matrix(0, 3, &a);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(eq_matrix_1) {
  matrix_t a, b;
  create_matrix(4, 4, &a);
  create_matrix(4, 4, &b);
  init_matrix(4, 4, 1, &a);
  init_matrix(4, 4, 1, &b);
  int res = eq_matrix(&a, &b);
  ck_assert_int_eq(res, 1);
  remove_matrix(&a);
  remove_matrix(&b);
}
END_TEST

START_TEST(eq_matrix_2) {
  matrix_t a, b;
  create_matrix(4, 2, &a);
  create_matrix(4, 4, &b);
  init_matrix_rand(4, 2, &a);
  init_matrix_rand(4, 4, &b);
  int res = eq_matrix(&a, &b);
  ck_assert_int_eq(res, 0);
  remove_matrix(&a);
  remove_matrix(&b);
}
END_TEST

START_TEST(eq_matrix_3) {
  matrix_t a, b;
  create_matrix(2, 3, &a);
  create_matrix(2, 3, &b);
  double x[] = {0.000001, 0, 0, 0, 0, 0};
  double y[] = {0, 0, 0, 0, 0, 0};
  init_matrix_line(2, 3, x, &a);
  init_matrix_line(2, 3, y, &b);
  int res = eq_matrix(&a, &b);
  ck_assert_int_eq(res, 0);
  remove_matrix(&a);
  remove_matrix(&b);
}
END_TEST

START_TEST(eq_matrix_4) {
  matrix_t a, b;
  create_matrix(2, 3, &a);
  create_matrix(2, 3, &b);
  double x[] = {0.00000001, 0, 0, 0, 0, 0};
  double y[] = {0, 0, 0, 0, 0, 0};
  init_matrix_line(2, 3, x, &a);
  init_matrix_line(2, 3, y, &b);
  int res = eq_matrix(&a, &b);
  ck_assert_int_eq(res, 1);
  remove_matrix(&a);
  remove_matrix(&b);
}
END_TEST

START_TEST(eq_matrix_NULL) {
  matrix_t a, b;
  create_matrix(0, 3, &a);
  create_matrix(0, 3, &b);
  init_matrix_rand(0, 3, &a);
  init_matrix_rand(0, 3, &b);
  int res = eq_matrix(&a, &b);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(sum_matrix_1) {
  matrix_t a, b, result;
  create_matrix(2, 3, &a);
  create_matrix(3, 3, &b);
  init_matrix_rand(2, 3, &a);
  init_matrix_rand(3, 3, &b);
  int res = sum_matrix(&a, &b, &result);
  ck_assert_int_eq(res, 2);
  remove_matrix(&a);
  remove_matrix(&b);
}
END_TEST

START_TEST(sum_matrix_2) {
  matrix_t a, b, result;
  create_matrix(0, 3, &a);
  create_matrix(3, 3, &b);
  init_matrix_rand(0, 3, &a);
  init_matrix_rand(3, 3, &b);
  int res = sum_matrix(&a, &b, &result);
  ck_assert_int_eq(res, 1);
  remove_matrix(&b);
}
END_TEST

START_TEST(sum_matrix_3) {
  matrix_t a, b, result, tmp;
  create_matrix(3, 3, &a);
  create_matrix(3, 3, &b);
  create_matrix(3, 3, &tmp);
  init_matrix(3, 3, 1, &a);
  init_matrix(3, 3, 1, &b);
  double mass[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
  init_matrix_line(3, 3, mass, &tmp);
  int res = sum_matrix(&a, &b, &result);
  int eq = eq_matrix(&result, &tmp);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(eq, 1);

  remove_matrix(&a);
  remove_matrix(&b);
  remove_matrix(&result);
  remove_matrix(&tmp);
}
END_TEST

START_TEST(sum_matrix_4) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  matrix_t res;
  int result1 = create_matrix(3, 2, &matrix_00);
  int result2 = create_matrix(3, 2, &matrix_01);
  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = 1e19;
  matrix_00.matrix[2][0] = 0 / 0.0;
  matrix_00.matrix[2][1] = 1.1234567;

  matrix_01.matrix[0][0] = 451.4866;
  matrix_01.matrix[0][1] = -24.564;
  matrix_01.matrix[1][0] = 3456e-5;
  matrix_01.matrix[1][1] = -.045461e19;
  matrix_01.matrix[2][0] = 0.0;
  matrix_01.matrix[2][1] = 1123.4567;

  int result = sum_matrix(&matrix_00, &matrix_01, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);

  remove_matrix(&matrix_00);
  remove_matrix(&matrix_01);

  ck_assert_double_eq(res.matrix[0][0], 453.3526);
  ck_assert_double_eq(res.matrix[0][1], 24539.436);
  ck_assert_double_eq(res.matrix[1][0], 0.03459);
  ck_assert_double_eq(res.matrix[1][1], 954539e13);
  ck_assert_double_nan(res.matrix[2][0]);
  ck_assert_double_eq(res.matrix[2][1], 1124.5801566999999);

  remove_matrix(&res);
}
END_TEST

START_TEST(sub_matrix_1) {
  matrix_t a, b, result;
  create_matrix(8, 3, &a);
  create_matrix(3, 3, &b);
  init_matrix_rand(8, 3, &a);
  init_matrix_rand(3, 3, &b);
  int res = sub_matrix(&a, &b, &result);
  ck_assert_int_eq(res, 2);
  remove_matrix(&a);
  remove_matrix(&b);
}
END_TEST

START_TEST(sub_matrix_2) {
  matrix_t a, b, result;
  create_matrix(0, 3, &a);
  create_matrix(3, 3, &b);
  init_matrix_rand(0, 3, &a);
  init_matrix_rand(3, 3, &b);
  int res = sub_matrix(&a, &b, &result);
  ck_assert_int_eq(res, 1);
  remove_matrix(&b);
}
END_TEST

START_TEST(sub_matrix_3) {
  matrix_t a, b, result, tmp;
  create_matrix(3, 3, &a);
  create_matrix(3, 3, &b);
  create_matrix(3, 3, &tmp);
  init_matrix(3, 3, 1, &a);
  init_matrix(3, 3, 1, &b);
  double mass[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
  init_matrix_line(3, 3, mass, &tmp);
  int res = sub_matrix(&tmp, &a, &result);
  int eq = eq_matrix(&result, &b);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(eq, 1);

  remove_matrix(&a);
  remove_matrix(&b);
  remove_matrix(&result);
  remove_matrix(&tmp);
}
END_TEST

START_TEST(sub_matrix_4) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  matrix_t res;
  int result1 = create_matrix(3, 2, &matrix_00);
  int result2 = create_matrix(3, 2, &matrix_01);
  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = 1e19;
  matrix_00.matrix[2][0] = 0.0;
  matrix_00.matrix[2][1] = 1.1234567;

  matrix_01.matrix[0][0] = 451.4866;
  matrix_01.matrix[0][1] = -24.564;
  matrix_01.matrix[1][0] = 3456e-5;
  matrix_01.matrix[1][1] = -.045461e19;
  matrix_01.matrix[2][0] = 1 / 0.0;
  matrix_01.matrix[2][1] = 1123.4567;

  int result = sub_matrix(&matrix_00, &matrix_01, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);

  remove_matrix(&matrix_00);
  remove_matrix(&matrix_01);

  ck_assert_double_eq(res.matrix[0][0], -449.6206);
  ck_assert_double_eq(res.matrix[0][1], 24588.564);
  ck_assert_double_eq(res.matrix[1][0], -0.03453);
  ck_assert_double_eq(res.matrix[1][1], 1.045461e19);
  ck_assert_double_eq(res.matrix[2][0], -1 / 0.0);
  ck_assert_double_eq(res.matrix[2][1], -1122.3332433);

  remove_matrix(&res);
}
END_TEST

START_TEST(mult_number_1) {
  matrix_t a, result, tmp;
  double number = 1.01;
  create_matrix(3, 3, &a);
  create_matrix(3, 3, &tmp);
  init_matrix(3, 3, 1, &a);
  double mass[] = {1.01, 2.02, 3.03, 4.04, 5.05, 6.06, 7.07, 8.08, 9.09};
  init_matrix_line(3, 3, mass, &tmp);
  int res = mult_number(&a, number, &result);
  int eq = eq_matrix(&result, &tmp);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(eq, 1);

  remove_matrix(&a);
  remove_matrix(&result);
  remove_matrix(&tmp);
}
END_TEST

START_TEST(mult_number_2) {
  matrix_t a, result;
  double number = 1000;
  create_matrix(0, 3, &a);
  init_matrix(0, 3, 1, &a);
  int res = mult_number(&a, number, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(mult_number_3) {
  matrix_t matrix_00;
  double number = 0.1456e6;
  matrix_t res;
  int result1 = create_matrix(3, 2, &matrix_00);
  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = -24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = -1e19;
  matrix_00.matrix[2][0] = 1 / 0.0;
  matrix_00.matrix[2][1] = 0 / 0.0;

  int result = mult_number(&matrix_00, number, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);

  remove_matrix(&matrix_00);

  ck_assert_double_eq(res.matrix[0][0], 271689.60000000003);
  ck_assert_double_eq(res.matrix[0][1], -3576518400);
  ck_assert_double_eq(res.matrix[1][0], 4.368);
  ck_assert_double_eq(res.matrix[1][1], -1.456e+24);
  ck_assert_double_eq(res.matrix[2][0], 1 / 0.0);
  ck_assert_double_nan(res.matrix[2][1]);

  remove_matrix(&res);
}
END_TEST

START_TEST(mult_matrix_1) {
  matrix_t a, b, result, tmp;
  create_matrix(3, 2, &a);
  create_matrix(2, 3, &b);
  create_matrix(3, 3, &tmp);
  double mass1[] = {1, 4, 2, 5, 3, 6};
  init_matrix_line(3, 2, mass1, &a);
  double mass2[] = {1, -1, 1, 2, 3, 4};
  init_matrix_line(2, 3, mass2, &b);
  double mass[] = {9, 11, 17, 12, 13, 22, 15, 15, 27};
  init_matrix_line(3, 3, mass, &tmp);
  int res = mult_matrix(&a, &b, &result);
  int eq = eq_matrix(&result, &tmp);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(eq, 1);

  remove_matrix(&a);
  remove_matrix(&b);
  remove_matrix(&result);
  remove_matrix(&tmp);
}
END_TEST

START_TEST(mult_matrix_2) {
  matrix_t a, b, result;
  create_matrix(0, 2, &a);
  create_matrix(2, 3, &b);
  init_matrix_rand(0, 2, &a);
  double mass2[] = {1, -1, 1, 2, 3, 4};
  init_matrix_line(2, 3, mass2, &b);
  int res = mult_matrix(&a, &b, &result);
  ck_assert_int_eq(res, 1);

  remove_matrix(&b);
}
END_TEST

START_TEST(mult_matrix_3) {
  matrix_t a, b, result;
  create_matrix(3, 5, &a);
  create_matrix(2, 3, &b);
  init_matrix_rand(3, 5, &a);
  init_matrix_rand(2, 3, &b);
  int res = mult_matrix(&a, &b, &result);
  ck_assert_int_eq(res, 2);

  remove_matrix(&a);
  remove_matrix(&b);
}
END_TEST

START_TEST(mult_matrix_4) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  matrix_t res;
  int result1 = create_matrix(3, 2, &matrix_00);
  int result2 = create_matrix(2, 3, &matrix_01);
  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = 1e19;
  matrix_00.matrix[2][0] = 0.0;
  matrix_00.matrix[2][1] = 1.1234567;

  matrix_01.matrix[0][0] = 451.4866;
  matrix_01.matrix[0][1] = -24.564;
  matrix_01.matrix[0][2] = 3456e-5;
  matrix_01.matrix[1][0] = -.045461e19;
  matrix_01.matrix[1][1] = 56;
  matrix_01.matrix[1][2] = 1123.4567;

  int result = mult_matrix(&matrix_00, &matrix_01, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);

  remove_matrix(&matrix_00);
  remove_matrix(&matrix_01);

  ck_assert_double_eq(res.matrix[0][0], -1.116704004e+22);
  ck_assert_double_eq(res.matrix[0][1], 1375538.163576);
  ck_assert_double_eq(res.matrix[0][2], 27596590.443288956);
  ck_assert_double_eq(res.matrix[1][0], -4.5461e+36);
  ck_assert_double_eq(res.matrix[1][1], 5.6e+20);
  ck_assert_double_eq(res.matrix[1][2], 1.1234567e+22);
  ck_assert_double_eq(res.matrix[2][0], -510734650387000000);
  ck_assert_double_eq(res.matrix[2][1], 62.9135752);
  ck_assert_double_eq(res.matrix[2][2], 1262.15495677489);

  remove_matrix(&res);
}
END_TEST

START_TEST(mult_matrix_5) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  matrix_t res;
  int result1 = create_matrix(3, 2, &matrix_00);
  int result2 = create_matrix(2, 3, &matrix_01);
  matrix_00.matrix[0][0] = 1.866;
  matrix_00.matrix[0][1] = 24564;
  matrix_00.matrix[1][0] = 3e-5;
  matrix_00.matrix[1][1] = 1e19;
  matrix_00.matrix[2][0] = 0.0;
  matrix_00.matrix[2][1] = 1.1234567;

  matrix_01.matrix[0][0] = 451.4866;
  matrix_01.matrix[0][1] = -24.564;
  matrix_01.matrix[0][2] = 3456e-5;
  matrix_01.matrix[1][0] = -.045461e19;
  matrix_01.matrix[1][1] = 56;
  matrix_01.matrix[1][2] = 1123.4567;

  int result = mult_matrix(&matrix_00, &matrix_01, &res);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);

  remove_matrix(&matrix_00);
  remove_matrix(&matrix_01);

  ck_assert_double_eq(res.matrix[0][0], -1.116704004e+22);
  ck_assert_double_eq(res.matrix[0][1], 1375538.163576);
  ck_assert_double_eq(res.matrix[0][2], 27596590.443288956);
  ck_assert_double_eq(res.matrix[1][0], -4.5461e+36);
  ck_assert_double_eq(res.matrix[1][1], 5.6e+20);
  ck_assert_double_eq(res.matrix[1][2], 1.1234567e+22);
  ck_assert_double_eq(res.matrix[2][0], -510734650387000000);
  ck_assert_double_eq(res.matrix[2][1], 62.9135752);
  ck_assert_double_eq(res.matrix[2][2], 1262.15495677489);

  remove_matrix(&res);
}
END_TEST

START_TEST(transpose_1) {
  matrix_t a, result, tmp;
  create_matrix(3, 3, &a);
  create_matrix(3, 3, &tmp);
  init_matrix(3, 3, 1, &a);
  double mass[] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
  init_matrix_line(3, 3, mass, &tmp);
  int res = transpose(&a, &result);
  int eq = eq_matrix(&result, &tmp);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(eq, 1);

  remove_matrix(&a);
  remove_matrix(&result);
  remove_matrix(&tmp);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t a = {0}, result;
  create_matrix(0, 3, &a);
  init_matrix_rand(0, 3, &a);
  int res = transpose(&a, &result);
  ck_assert_int_eq(res, 1);

  remove_matrix(&a);
}
END_TEST

START_TEST(calc_compl_1) {
  matrix_t a, result, tmp;
  create_matrix(2, 2, &a);
  create_matrix(2, 2, &tmp);
  init_matrix(2, 2, 1, &a);
  double mass[] = {4, -3, -2, 1};
  init_matrix_line(2, 2, mass, &tmp);
  int res = calc_complements(&a, &result);
  int eq = eq_matrix(&result, &tmp);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(eq, 1);

  remove_matrix(&a);
  remove_matrix(&result);
  remove_matrix(&tmp);
}
END_TEST

START_TEST(calc_compl_2) {
  matrix_t a, result;
  create_matrix(3, 2, &a);
  init_matrix(3, 2, 1, &a);
  int res = calc_complements(&a, &result);
  ck_assert_int_eq(res, 2);

  remove_matrix(&a);
}
END_TEST

START_TEST(calc_compl_3) {
  matrix_t a, result;
  create_matrix(1, 0, &a);
  init_matrix(1, 0, 1, &a);
  int res = calc_complements(&a, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(det_1) {
  matrix_t a;
  double result;
  create_matrix(2, 2, &a);
  init_matrix(2, 2, 1, &a);
  double tmp = -2;
  int res = determinant(&a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq(result, tmp);

  remove_matrix(&a);
}
END_TEST

START_TEST(det_2) {
  matrix_t a;
  double result;
  create_matrix(3, 3, &a);
  init_matrix(3, 3, 1, &a);
  double tmp = 0;
  int res = determinant(&a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq(result, tmp);

  remove_matrix(&a);
}
END_TEST

START_TEST(det_3) {
  matrix_t a;
  double result;
  create_matrix(1, 1, &a);
  init_matrix(1, 1, 326, &a);
  double tmp = 326;
  int res = determinant(&a, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_double_eq(result, tmp);

  remove_matrix(&a);
}
END_TEST
START_TEST(det_4) {
  double det = 0.0;
  matrix_t A = {0};
  create_matrix(1, 2, &A);
  int res = determinant(&A, &det);
  ck_assert_int_eq(res, 2);
  remove_matrix(&A);
}
END_TEST

START_TEST(det_5) {
  double det = 0.0;
  matrix_t A = {0};
  create_matrix(1, 1, &A);
  A.matrix[0][0] = 1.0;
  determinant(&A, &det);
  ck_assert_double_eq(det, 1.0);
  remove_matrix(&A);
}
END_TEST

START_TEST(inv_err) {
  matrix_t matrix_00;
  matrix_t matrix_01;
  matrix_t res;
  int result1 = create_matrix(3, 3, &matrix_00);
  int result2 = create_matrix(2, 3, &matrix_01);

  matrix_00.matrix[0][0] = 1;
  matrix_00.matrix[0][1] = 2;
  matrix_00.matrix[0][2] = 3;
  matrix_00.matrix[1][0] = 4;
  matrix_00.matrix[1][1] = 5;
  matrix_00.matrix[1][2] = 6;
  matrix_00.matrix[2][0] = 7;
  matrix_00.matrix[2][1] = 8;
  matrix_00.matrix[2][2] = 9;

  int result = inverse_matrix(&matrix_00, &res);
  int result3 = inverse_matrix(&matrix_01, &res);

  ck_assert_int_eq(result, 2);
  ck_assert_int_eq(result1, 0);
  ck_assert_int_eq(result2, 0);
  ck_assert_int_eq(result3, 2);

  remove_matrix(&matrix_00);
  remove_matrix(&matrix_01);
}
END_TEST

START_TEST(inv_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  int result = inverse_matrix(&A, &B);
  ck_assert_int_eq(result, 0);
  remove_matrix(&A);
  ck_assert_double_eq(B.matrix[0][0], 1);
  ck_assert_double_eq(B.matrix[0][1], -1);
  ck_assert_double_eq(B.matrix[0][2], 1);
  ck_assert_double_eq(B.matrix[1][0], -38);
  ck_assert_double_eq(B.matrix[1][1], 41);
  ck_assert_double_eq(B.matrix[1][2], -34);
  ck_assert_double_eq(B.matrix[2][0], 27);
  ck_assert_double_eq(B.matrix[2][1], -29);
  ck_assert_double_eq(B.matrix[2][2], 24);
  remove_matrix(&B);
}
END_TEST

START_TEST(inv_2) {
  matrix_t a, result;
  create_matrix(3, 3, &a);
  init_matrix(3, 3, 0, &a);
  int res = inverse_matrix(&a, &result);
  ck_assert_int_eq(res, 2);

  remove_matrix(&a);
}
END_TEST

START_TEST(inv_4) {
  matrix_t a, result, tmp;
  create_matrix(4, 4, &a);
  create_matrix(4, 4, &tmp);
  double mass[] = {2, 12, -4, -1, 5, 0, 6, 19, -0.5, 1, 4, 8, 7, 7, -3.5, 16};
  init_matrix_line(4, 4, mass, &a);
  double mass1[] = {0.10294329,  0.28011486,  -0.41923905, -0.11658291,
                    0.09913855,  0.01313711,  0.04953338,  -0.03417085,
                    0.11471644,  0.2005743,   -0.09619526, -0.18291457,
                    -0.06331658, -0.08442211, 0.14070352,  0.08844221};
  init_matrix_line(4, 4, mass1, &tmp);
  int res = inverse_matrix(&a, &result);
  int eq = eq_matrix(&result, &tmp);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(eq, 1);

  remove_matrix(&a);
  remove_matrix(&result);
  remove_matrix(&tmp);
}
END_TEST

Suite *test_matrix(void) {
  Suite *s = suite_create("matrix");
  TCase *tc = tcase_create("case_matrix");

  tcase_add_test(tc, create_matrix_1);
  tcase_add_test(tc, create_matrix_2);
  tcase_add_test(tc, create_matrix_err);
  tcase_add_test(tc, eq_matrix_1);
  tcase_add_test(tc, eq_matrix_2);
  tcase_add_test(tc, eq_matrix_3);
  tcase_add_test(tc, eq_matrix_4);
  tcase_add_test(tc, eq_matrix_NULL);
  tcase_add_test(tc, sum_matrix_1);
  tcase_add_test(tc, sum_matrix_2);
  tcase_add_test(tc, sum_matrix_3);
  tcase_add_test(tc, sum_matrix_4);
  tcase_add_test(tc, sub_matrix_1);
  tcase_add_test(tc, sub_matrix_2);
  tcase_add_test(tc, sub_matrix_3);
  tcase_add_test(tc, sub_matrix_4);
  tcase_add_test(tc, mult_number_1);
  tcase_add_test(tc, mult_number_2);
  tcase_add_test(tc, mult_number_3);
  tcase_add_test(tc, mult_matrix_1);
  tcase_add_test(tc, mult_matrix_2);
  tcase_add_test(tc, mult_matrix_3);
  tcase_add_test(tc, mult_matrix_4);
  tcase_add_test(tc, mult_matrix_5);
  tcase_add_test(tc, transpose_1);
  tcase_add_test(tc, transpose_2);
  tcase_add_test(tc, calc_compl_1);
  tcase_add_test(tc, calc_compl_2);
  tcase_add_test(tc, calc_compl_3);
  tcase_add_test(tc, det_1);
  tcase_add_test(tc, det_2);
  tcase_add_test(tc, det_3);
  tcase_add_test(tc, det_4);
  tcase_add_test(tc, det_5);
  tcase_add_test(tc, inv_err);
  tcase_add_test(tc, inv_2);
  tcase_add_test(tc, inv_3);
  tcase_add_test(tc, inv_4);

  suite_add_tcase(s, tc);
  return s;
}
