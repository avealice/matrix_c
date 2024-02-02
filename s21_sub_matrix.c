#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (A == NULL || B == NULL) {
    error = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    error = CALC_ERROR;
  } else if ((A->rows == B->rows && A->columns == B->columns) &&
             s21_create_matrix(A->rows, A->columns, result) == OK) {
    for (int i = 0; i < A->rows && !error; i++) {
      for (int j = 0; j < A->columns && !error; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        if (!isfinite(result->matrix[i][j])) error = CALC_ERROR;
      }
    }
  }
  return error;
}