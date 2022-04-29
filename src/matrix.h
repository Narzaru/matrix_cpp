#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <exception>
#include <initializer_list>
#include <ostream>

class S21Matrix {
 friend std::ostream& operator<<(std::ostream& os, const S21Matrix& matrix);

 private:
  int m_rows;
  int m_columns;
  double *m_matrix;

  int index(int i, int j) const;
  S21Matrix minor_at(int m, int n) const;

 public:
  // default constructor
  S21Matrix();
  // size dependent constructor
  S21Matrix(int rows, int cols);
  // copy constructor
  S21Matrix(const S21Matrix& other);
  // move constructor
  S21Matrix(S21Matrix&& other);
  // destructor
  ~S21Matrix();

  // accessors
  int get_rows() const;
  int get_columns() const;
  // mutators
  void set_values(std::initializer_list<double> list);
  void set_values(std::initializer_list<std::initializer_list<double>> list);
  // mathematical methods
  bool eq_matrix(const S21Matrix& other) const;
  void sum_matrix(const S21Matrix& other);
  void sub_matrix(const S21Matrix& other);
  void mul_number(double num);
  void mul_matrix(const S21Matrix& other);
  S21Matrix transpose() const;
  S21Matrix calc_complements() const;
  double determinant() const;
  S21Matrix inverse_matrix() const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(S21Matrix&& other);
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  void operator*=(double num);
  double& operator()(int i, int j);
  double operator()(int i, int j) const;

  // get class state
  bool is_empty_object() const;
};

#endif  // SRC_MATRIX_H_
