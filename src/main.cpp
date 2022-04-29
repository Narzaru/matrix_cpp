#include <iostream>
#include <iomanip>
#include "matrix.h"

int main() {
  try {
    S21Matrix matrix1(3, 2);
    S21Matrix matrix2(3, 2);
    matrix1.set_values({1, 2, 3, 4, 5, 6});
    matrix2.set_values({1, 2, 3, 4, 5, 6});
    S21Matrix matrix3 = matrix1 + matrix2;
    std::cout << matrix3;
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
