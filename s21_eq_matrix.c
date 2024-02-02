#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (A == NULL || B == NULL) {
    result = FAILURE;
  } else if (A->columns != B->columns || A->rows != B->rows || !A->matrix ||
             !B->matrix) {
    result = FAILURE;
  } else if (A->rows == B->rows && A->columns == B->rows) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        if (fabsl(A->matrix[i][j] - B->matrix[i][j]) >= EPS) {
          result = FAILURE;
        }
      }
    }
  }
  return result;
}