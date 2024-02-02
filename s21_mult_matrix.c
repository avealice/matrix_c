#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (A == NULL || B == NULL) {
    error = INCORRECT_MATRIX;
  } else if ((A->columns == B->rows) &&
             s21_create_matrix(A->rows, B->columns, result) == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int n = 0; n < A->columns && !error; n++) {
          result->matrix[i][j] += A->matrix[i][n] * B->matrix[n][j];
          if (!isfinite(result->matrix[i][j])) error = CALC_ERROR;
        }
      }
    }
  } else if (A->columns != B->rows) {
    error = CALC_ERROR;
  }
  return error;
}