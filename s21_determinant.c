#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int error = OK;
  if (A == NULL || A->columns < 1 || A->rows < 1 || result == NULL) {
    error = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    error = CALC_ERROR;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else if (A->columns > 2) {
    double det = 0;
    for (int i = 0; i < A->columns; i++) {
      double subdet = 0.0;
      double cofactor = (i % 2 == 0) ? 1.0 : -1.0;
      matrix_t tmp;
      create_minor_matrix(*A, &tmp, 0, i);
      s21_determinant(&tmp, &subdet);
      det += cofactor * A->matrix[0][i] * subdet;
      s21_remove_matrix(&tmp);
    }
    *result = det;
  }
  return error;
}