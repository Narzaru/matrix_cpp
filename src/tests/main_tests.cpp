#include <matrix.h>
#include <gtest/gtest.h>
#include <iostream>

namespace MatrixConstructorsSutie {
  TEST(ConstructorsSutie, ConstructorTest) {
    ASSERT_NO_THROW(S21Matrix matrix);
  }

  TEST(ConstructorsSutie, DestructorTest) {
    S21Matrix matrix;
    matrix.~S21Matrix();
    ASSERT_NO_THROW(matrix.~S21Matrix());
  }

  TEST(ConstructorsSutie, ConstructorTest2) {
    S21Matrix matrix(4, 1);
    ASSERT_EQ(matrix.get_rows(), 4);
    ASSERT_EQ(matrix.get_columns(), 1);
  }

  TEST(ConstructorsSutie, CopyTest) {
    S21Matrix matrix1(2, 2);
    matrix1.set_values({{1, 2}, {3, 4}});

    S21Matrix matrix2(matrix1);

    ASSERT_EQ(matrix2.get_rows(), 2);
    ASSERT_EQ(matrix2.get_columns(), 2);

    for (int i = 0; i < matrix2.get_rows(); ++i) {
      for (int j = 0; j < matrix2.get_columns(); ++j) {
        ASSERT_FLOAT_EQ(matrix2(i, j), matrix1(i, j));
      }
    }
  }

  TEST(ConstructorsSutie, MoveTest1) {
    S21Matrix matrix1(2, 2);
    matrix1.set_values({{1, 2}, {3, 4}});
    S21Matrix answer_matrix(2, 2);
    answer_matrix.set_values({{1, 2}, {3, 4}});

    S21Matrix matrix2(std::move(matrix1));

    for (int i = 0; i < matrix2.get_rows(); ++i) {
      for (int j = 0; j < matrix2.get_columns(); ++j) {
        ASSERT_FLOAT_EQ(matrix2(i, j), answer_matrix(i, j));
      }
    }
  }

  TEST(ConstructorsSutie, MoveTest2) {
    S21Matrix matrix1 {6, 6};
    S21Matrix matrix2(std::move(matrix1));

    ASSERT_EQ(matrix1.get_rows(), 0);
    ASSERT_EQ(matrix1.get_columns(), 0);
    ASSERT_EQ(matrix1.is_empty_object(), true);

    ASSERT_EQ(matrix2.get_rows(), 6);
    ASSERT_EQ(matrix2.get_columns(), 6);
    ASSERT_EQ(matrix2.is_empty_object(), false);
  }

  TEST(ConstructorsSutie, MoveTest3) {
    S21Matrix matrix1 {10, 1};
    S21Matrix matrix2(std::move(matrix1));

    ASSERT_EQ(matrix1.get_rows(), 0);
    ASSERT_EQ(matrix1.get_columns(), 0);
    ASSERT_EQ(matrix1.is_empty_object(), true);

    ASSERT_EQ(matrix2.get_rows(), 10);
    ASSERT_EQ(matrix2.get_columns(), 1);
    ASSERT_EQ(matrix2.is_empty_object(), false);
  }
}  // namespace MatrixConstructorsSutie

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
      for (int j = 0; j < matrix1.get_columns(); ++j) {
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

  TEST(EqualSuite, Test4) {
    S21Matrix matrix1;
    S21Matrix matrix2(4, 3);

    ASSERT_EQ(matrix1.eq_matrix(matrix2), false);
  }
}  // namespace MatrixEqualSuite

namespace MatrixSumSuite {
  TEST(SumSuite, Test1) {
    S21Matrix matrix1;
    S21Matrix matrix2;

    matrix1.sum_matrix(matrix2);
    for (int i = 0; i < matrix1.get_rows(); ++i) {
      for (int j = 0; j < matrix1.get_columns(); ++j) {
        ASSERT_FLOAT_EQ(matrix1(i, j), 0.0);
      }
    }
  }

  TEST(SumSuite, Test2) {
    S21Matrix matrix1;
    S21Matrix matrix2;
    S21Matrix answerMatrix;

    matrix1.set_values({1, 2, 3, 4, 5, 6, 7, 8, 9});
    matrix2.set_values({1, 2, 3, 4, 5, 6, 7, 8, 9});
    answerMatrix.set_values({2, 4, 6, 8, 10, 12, 14, 16, 18});

    matrix1.sum_matrix(matrix2);
    for (int i = 0; i < matrix1.get_rows(); ++i) {
      for (int j = 0; j < matrix1.get_columns(); ++j) {
        ASSERT_FLOAT_EQ(matrix1(i, j), answerMatrix(i, j));
      }
    }
  }

  TEST(SumSuite, Test3) {
    S21Matrix matrix1(1, 2);
    S21Matrix matrix2(2, 1);

    ASSERT_ANY_THROW(matrix1.sum_matrix(matrix2));
  }

  TEST(SumSuite, Test4) {
    S21Matrix matrix1(1, 2);
    S21Matrix matrix2(2, 1);

    matrix2.~S21Matrix();

    ASSERT_ANY_THROW(matrix1.sum_matrix(matrix2));
  }
}  // namespace MatrixSumSuite

namespace MatrixSubSuite {
  TEST(SubSuite, Test1) {
    S21Matrix matrix1;
    S21Matrix matrix2;

    matrix1.sub_matrix(matrix2);
    for (int i = 0; i < matrix1.get_rows(); ++i) {
      for (int j = 0; j < matrix1.get_columns(); ++j) {
        ASSERT_FLOAT_EQ(matrix1(i, j), 0.0);
      }
    }
  }

  TEST(SubSuite, Test2) {
    S21Matrix matrix1;
    S21Matrix matrix2;
    S21Matrix matrix3;

    matrix1.set_values({1, 2, 3, 4, 5, 6, 7, 8, 9});
    matrix2.set_values({1, 2, 3, 4, 5, 6, 7, 8, 9});
    matrix3.set_values({0, 0, 0, 0, 0, 0, 0, 0, 0});

    matrix1.sub_matrix(matrix2);
    for (int i = 0; i < matrix1.get_rows(); ++i) {
      for (int j = 0; j < matrix1.get_columns(); ++j) {
        ASSERT_FLOAT_EQ(matrix1(i, j), matrix3(i, j));
      }
    }
  }
}  // namespace MatrixSubSuite

namespace MatrixMulNumberSuite {
  TEST(MulNumberSuite, Test1) {
    S21Matrix matrix;
    S21Matrix answerMatrix;

    matrix.set_values({1, 2, 3, 1, 2, 3, 1, 2, 3});
    matrix.mul_number(1);
    answerMatrix.set_values({1, 2, 3, 1, 2, 3, 1, 2, 3});

    for (int i = 0; i < matrix.get_rows(); ++i) {
      for (int j = 0; j < matrix.get_columns(); ++j) {
        ASSERT_FLOAT_EQ(matrix(i, j), answerMatrix(i, j));
      }
    }

    matrix.~S21Matrix();
    ASSERT_NO_THROW(matrix.mul_number(1));
  }
}  // namespace MatrixMulNumberSuite

namespace MatrixMulSuite {
  TEST(MulSuite, Test1) {
    S21Matrix matrix1(2, 2);
    S21Matrix matrix2(2, 2);
    S21Matrix answerMatrix(2, 2);

    matrix1.set_values({1, 2, 3, 4});
    matrix2.set_values({4, 3, 2, 1});
    answerMatrix.set_values({8, 5, 20, 13});

    matrix1.mul_matrix(matrix2);
    for (int i = 0; i < matrix1.get_rows(); ++i) {
      for (int j = 0; j < matrix1.get_columns(); ++j) {
        ASSERT_FLOAT_EQ(matrix1(i, j), answerMatrix(i, j));
      }
    }
  }

  TEST(MulSuite, Test2) {
    S21Matrix matrix1(1, 2);
    S21Matrix matrix2(2, 1);
    S21Matrix answerMatrix(1, 1);

    matrix1.set_values({1, 2});
    matrix2.set_values({3, 4});
    answerMatrix.set_values({11});

    matrix1.mul_matrix(matrix2);
    for (int i = 0; i < matrix1.get_rows(); ++i) {
      for (int j = 0; j < matrix1.get_columns(); ++j) {
        ASSERT_FLOAT_EQ(matrix1(i, j), answerMatrix(i, j));
      }
    }
  }

  TEST(MulSuite, Test3) {
    S21Matrix matrix1(2, 1);
    S21Matrix matrix2(1, 2);
    S21Matrix answerMatrix(2, 2);

    matrix1.set_values({1, 2});
    matrix2.set_values({3, 4});
    answerMatrix.set_values({3, 4, 6, 8});

    matrix1.mul_matrix(matrix2);
    for (int i = 0; i < matrix1.get_rows(); ++i) {
      for (int j = 0; j < matrix1.get_columns(); ++j) {
        ASSERT_FLOAT_EQ(matrix1(i, j), answerMatrix(i, j));
      }
    }
  }

  TEST(MulSuite, Test4) {
    S21Matrix matrix1(2, 2);
    S21Matrix matrix2(3, 3);

    ASSERT_THROW(matrix1.mul_matrix(matrix2), std::range_error);
  }
}  // namespace MatrixMulSuite

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
