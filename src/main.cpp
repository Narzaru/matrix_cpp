#include <iostream>
#include <iomanip>
#include "matrix.h"

int main() {
  try {
    S21Matrix matrix1(1, 2);
    S21Matrix matrix2(2, 1);
    S21Matrix answerMatrix(1, 1);

    matrix1.set_values({1, 2});
    matrix2.set_values({3, 4});
    answerMatrix.set_values({11});

    matrix1.mul_matrix(matrix2);
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
