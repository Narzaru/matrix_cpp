#include <iostream>
#include <iomanip>
#include "s21_matrix_oop.h"

int main() {
  try {
    S21Matrix matrix1(1, 2);
    S21Matrix matrix2(2, 1);
    matrix1.set_values({1, 10});
    matrix2.set_values({3, 4});
    S21Matrix matrix3(std::move(matrix1 * matrix2));
    std::cout << matrix1 << std::endl << matrix2 << std::endl << matrix3;
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
