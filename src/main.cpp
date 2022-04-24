#include <iostream>
#include <iomanip>
#include "matrix.h"

int main() {
  try {
    S21Matrix matrix(5, 5);
    for (int i = 0; i < matrix.get_rows(); ++i) {
      for (int j = 0; j < matrix.get_columns(); ++j) {
        matrix(i, j) = i + j + i * (matrix.get_columns() - 1);
      }
    }

    for (int i = 0; i < matrix.get_rows(); ++i) {
      for (int j = 0; j < matrix.get_columns(); ++j) {
        std::cout << std::setw(2) << matrix(i, j) << " ";
      }
      std::cout << std::endl;
    }

    S21Matrix matrix2(matrix);

    for (int i = 0; i < matrix2.get_rows(); ++i) {
      for (int j = 0; j < matrix2.get_columns(); ++j) {
        std::cout << std::setw(2) << matrix2(i, j) << " ";
      }
      std::cout << std::endl;
    }
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
