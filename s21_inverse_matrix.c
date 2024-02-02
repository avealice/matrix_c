#include "s21_matrix.h"

// int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
//   double det = 0.0;
//   int error = s21_determinant(A, &det);
//   if (A == NULL || A->matrix == NULL || A->columns < 1 || result == NULL) {
//     error = INCORRECT_MATRIX;
//   } else if (A->rows == 1 || A->columns == 1 || fabs(det) < EPS) {
//     error = CALC_ERROR;
//   } else {
//     matrix_t tmp1 = {0}, tmp2 = {0};
//     s21_calc_complements(A, &tmp1);
//     s21_transpose(&tmp1, &tmp2);
//     s21_remove_matrix(&tmp1);
//     s21_mult_number(&tmp2, 1 / det, result);
//     s21_remove_matrix(&tmp2);
//   }
//   return error;
// }

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (result == NULL || A == NULL || A->matrix == NULL || A->rows < 1 ||
      A->columns < 1) {
    error = INCORRECT_MATRIX;
  } else {
    double det = 0;
    error = s21_determinant(A, &det);
    if (det == 0) {
      error = INCORRECT_MATRIX;
    } else if (error == OK) {
      if ((A->columns == 1) && (A->rows == 1)) {
        s21_create_matrix(1, 1, result);
        result->matrix[0][0] = 1 / det;
      } else {
        matrix_t tmp1, tmp2;
        s21_calc_complements(A, &tmp1);
        s21_transpose(&tmp1, &tmp2);
        s21_remove_matrix(&tmp1);
        s21_mult_number(&tmp2, 1 / det, result);
        s21_remove_matrix(&tmp2);
      }
    }
  }
  return error;
}