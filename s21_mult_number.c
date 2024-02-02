#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;
  if (A == NULL) {
    error = INCORRECT_MATRIX;
  } else if (!isfinite(number)) {
    error = CALC_ERROR;
  } else if (s21_create_matrix(A->rows, A->columns, result) == OK) {
    for (int i = 0; i < A->rows && !error; i++) {
      for (int j = 0; j < A->columns && !error; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
        if (!isfinite(result->matrix[i][j])) error = CALC_ERROR;
      }
    }
  }
  return error;
}