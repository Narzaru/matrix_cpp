#include <iostream>
#include <iomanip>
#include "matrix.h"

int main() {
  try {
    S21Matrix matrix1(2, 2);
    matrix1.set_values({1, 2, 3, 4});
    S21Matrix new_matrix = matrix1.calc_complements();
    std::cout << new_matrix;
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
