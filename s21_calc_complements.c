#include "s21_matrix.h"

void create_minor_matrix(matrix_t A, matrix_t *result, int remove_row,
                         int remove_col) {
  s21_create_matrix(A.rows - 1, A.columns - 1, result);
  int row = 0;
  for (int i = 0; i < A.rows; i++) {
    int columns = 0;
    for (int j = 0; j < A.columns; j++) {
      if (i != remove_row && j != remove_col) {
        result->matrix[row][columns] = A.matrix[i][j];
        columns++;
      }
    }
    if (i != remove_row) row++;
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (A == NULL || A->rows < 1 || A->columns < 1 || result == NULL) {
    error = INCORRECT_MATRIX;
  } else if (A->columns != A->rows || A->rows == 1 || A->columns == 1) {
    error = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
  }
  for (int i = 0; !error && i < A->rows; i++) {
    for (int j = 0; !error && j < A->columns; j++) {
      matrix_t tmp;
      double det = 0.0;
      create_minor_matrix(*A, &tmp, i, j);
      s21_determinant(&tmp, &det);
      result->matrix[i][j] = det * pow(-1, i + j);
      s21_remove_matrix(&tmp);
    }
  }
  return error;
}