#include <matrix.h>
#include <gtest/gtest.h>

TEST(MatrixAccessorSuite, Test1) {
  S21Matrix matrix1 {3, 3};
  ASSERT_EQ(matrix1.get_rows(), 3);
  ASSERT_EQ(matrix1.get_columns(), 3);
}

TEST(MatrixAccessorSuite, Test2) {
  S21Matrix matrix1 {4, 1};
  ASSERT_EQ(matrix1.get_rows(), 4);
  ASSERT_EQ(matrix1.get_columns(), 1);
}

TEST(MatrixAccessorSuite, Test3) {
  S21Matrix matrix1 {1, 4};
  ASSERT_EQ(matrix1.get_rows(), 1);
  ASSERT_EQ(matrix1.get_columns(), 4);
}

TEST(MatrixAccessorSuite, Test4) {
  S21Matrix matrix1;
  matrix1.~S21Matrix();
  ASSERT_EQ(matrix1.get_rows(), 0);
  ASSERT_EQ(matrix1.get_columns(), 0);
}

TEST(MatrixAccessorSuite, Test5) {
  const S21Matrix matrix1;
  ASSERT_EQ(matrix1.get_rows(), 3);
  ASSERT_EQ(matrix1.get_columns(), 3);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
