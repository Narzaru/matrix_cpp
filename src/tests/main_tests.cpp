#include <matrix.h>
#include <gtest/gtest.h>

namespace MatrixConstructorsSutie {
  TEST(ConstructorsSutie, Test1) {
    S21Matrix matrix;
  }

  TEST(ConstructorsSutie, Test2) {
    S21Matrix matrix;
    matrix.~S21Matrix();
  }

  TEST(ConstructorsSutie, Test3) {
    S21Matrix matrix(1, 5);
    for (int i = 0; i < matrix.get_rows(); ++i) {
      for (int j = 0; j < matrix.get_columns(); ++j) {
        matrix(i, j) = static_cast<double>(i);
      }
    }

    S21Matrix matrix2(matrix);
    for (int i = 0; i < matrix2.get_rows(); ++i) {
      for (int j = 0; j < matrix2.get_columns(); ++j) {
        ASSERT_FLOAT_EQ(matrix2(i, j), static_cast<double>(i));
      }
    }
  }

  TEST(ConstructorsSutie, Test4) {
    S21Matrix matrix(4, 1);
    ASSERT_EQ(matrix.get_rows(), 4);
    ASSERT_EQ(matrix.get_columns(), 1);
  }
}  // namespace MatrixConstructorsSutie

namespace MatrixMoveConstructorSuite {
  TEST(MoveConstructorSuite, Test1) {
    S21Matrix matrix1 {6, 6};
    S21Matrix matrix2(std::move(matrix1));

    ASSERT_EQ(matrix1.get_rows(), 0);
    ASSERT_EQ(matrix1.get_columns(), 0);
    ASSERT_EQ(matrix1.is_empty_object(), true);

    ASSERT_EQ(matrix2.get_rows(), 6);
    ASSERT_EQ(matrix2.get_columns(), 6);
    ASSERT_EQ(matrix2.is_empty_object(), false);
  }

  TEST(MoveConstructorSuite, Test2) {
    S21Matrix matrix1 {10, 1};
    S21Matrix matrix2(std::move(matrix1));

    ASSERT_EQ(matrix1.get_rows(), 0);
    ASSERT_EQ(matrix1.get_columns(), 0);
    ASSERT_EQ(matrix1.is_empty_object(), true);

    ASSERT_EQ(matrix2.get_rows(), 10);
    ASSERT_EQ(matrix2.get_columns(), 1);
    ASSERT_EQ(matrix2.is_empty_object(), false);
  }
}  // namespace MatrixMoveConstructorSuite

namespace MatrixAccessorSuite {
  TEST(AccessorSuite, Test1) {
    S21Matrix matrix1 {3, 3};
    ASSERT_EQ(matrix1.get_rows(), 3);
    ASSERT_EQ(matrix1.get_columns(), 3);
  }

  TEST(AccessorSuite, Test2) {
    S21Matrix matrix1 {4, 1};
    ASSERT_EQ(matrix1.get_rows(), 4);
    ASSERT_EQ(matrix1.get_columns(), 1);
  }

  TEST(AccessorSuite, Test3) {
    S21Matrix matrix1 {1, 4};
    ASSERT_EQ(matrix1.get_rows(), 1);
    ASSERT_EQ(matrix1.get_columns(), 4);
  }

  TEST(AccessorSuite, Test4) {
    S21Matrix matrix1;
    matrix1.~S21Matrix();
    ASSERT_EQ(matrix1.get_rows(), 0);
    ASSERT_EQ(matrix1.get_columns(), 0);
  }

  TEST(AccessorSuite, Test5) {
    const S21Matrix matrix1;
    ASSERT_EQ(matrix1.get_rows(), 3);
    ASSERT_EQ(matrix1.get_columns(), 3);
  }
}  // namespace MatrixAccessorSuite

namespace MatrixOperatorRoundBracketSuite {
  TEST(OperatorRoundBracketSuite, Test1) {
    S21Matrix matrix;

    for (int i = 0; i < matrix.get_rows(); ++i) {
      for (int j = 0; j < matrix.get_columns(); ++j) {
        matrix(i, j) = static_cast<double>(i);
      }
    }

    for (int i = 0; i < matrix.get_rows(); ++i) {
      for (int j = 0; j < matrix.get_columns(); ++j) {
        ASSERT_FLOAT_EQ(matrix(i, j), static_cast<double>(i));
      }
    }
  }
}  // namespace MatrixOperatorRoundBracketSuite

namespace MatrixEqualSuite {
  TEST(EqualSuite, Test1) {
    S21Matrix matrix1;
    S21Matrix matrix2;

    for (int i = 0; i < matrix1.get_rows(); ++i) {
      for (int j = 0; j < matrix1.get_rows(); ++j) {
        matrix1(i, j) = i + j + 2;
        matrix2(i, j) = i + j + 2;
      }
    }
    ASSERT_EQ(matrix1.eq_matrix(matrix2), true);
  }

  TEST(EqualSuite, Test2) {
    S21Matrix matrix1;
    S21Matrix matrix2(3, 4);

    ASSERT_EQ(matrix1.eq_matrix(matrix2), false);
  }

  TEST(EqualSuite, Test3) {
    S21Matrix matrix1;
    S21Matrix matrix2(4, 3);

    ASSERT_EQ(matrix1.eq_matrix(matrix2), false);
  }
}  // namespace MatrixEqualSuite



int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
