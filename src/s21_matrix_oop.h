#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <initializer_list>
#include <ostream>

class S21Matrix {
 public:
  // default constructor
  S21Matrix();
  // size dependent constructor
  S21Matrix(int rows, int cols);
  // copy constructor
  S21Matrix(const S21Matrix& other);
  // move constructor
  S21Matrix(S21Matrix&& other);
  // move assignment
  S21Matrix& operator=(S21Matrix&& other);
  // copy assignment
  S21Matrix& operator=(const S21Matrix& other);
  // destructor
  ~S21Matrix();

  // accessors
  int get_rows() const;
  int get_columns() const;
  void set_rows(const int& new_rows);
  void set_columns(const int& new_rows);
  // mutators
  void set_values(std::initializer_list<double> list);
  void set_values(std::initializer_list<std::initializer_list<double>> list);
  // mathematical methods
  bool eq_matrix(const S21Matrix& other) const;
  void sum_matrix(const S21Matrix& other);
  void sub_matrix(const S21Matrix& other);
  void mul_number(const double& num);
  void mul_matrix(const S21Matrix& other);
  S21Matrix transpose() const;
  S21Matrix calc_complements() const;
  double determinant() const;
  S21Matrix inverse_matrix() const;
  // opearators
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num);
  double& operator()(int i, int j);
  double operator()(int i, int j) const;

  // get class state
  bool is_empty_object() const;

 private:
  int rows_;
  int columns_;
  double *matrix_;

  // useful methods
  int index(int i, int j) const;
  S21Matrix minor_at(int m, int n) const;

  friend S21Matrix operator*(const double& num, const S21Matrix& matrix);
  friend std::ostream& operator<<(std::ostream& os, const S21Matrix& matrix);
};

#endif  // SRC_S21_MATRIX_OOP_H_
