// #include <stdexcept>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include "s21_matrix_oop.h"

// Base constructor with no arguments.
// It create a 3x3 zero matrix.
S21Matrix::S21Matrix()
  : rows_(3),
    columns_(3),
    matrix_(new double[rows_ * columns_]) {
  std::fill<double *>(matrix_, matrix_ + rows_ * columns_, 0.0);
}

// Constructor with two arguments, rows and columns.
// It create a RxC zero matrix.
S21Matrix::S21Matrix(int rows, int cols)
  : rows_(rows),
    columns_(cols),
    matrix_(nullptr) {
  if (rows_ <= 0 || columns_ <= 0) {
    rows_ = 0;
    columns_ = 0;
    throw std::invalid_argument("Matrix has the wrong size");
  }
  matrix_ = new double[rows_ * columns_];
  std::fill(matrix_, matrix_ + (rows_ * columns_), 0.0);
}

// Copy constructor with const S21Matrix& argument.
// It allocates a new matrix and copy other matrix.
S21Matrix::S21Matrix(const S21Matrix& other)
  : rows_(other.rows_),
    columns_(other.columns_),
    matrix_(nullptr) {
  if (!other.is_empty_object()) {
    matrix_ = new double[rows_ * columns_];
    for (int i = 0; i < rows_ * columns_; ++i) {
      matrix_[i] = other.matrix_[i];
    }
  }
}

// Move constructor.
S21Matrix::S21Matrix(S21Matrix&& other)
  : rows_(other.rows_),
    columns_(other.columns_),
    matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.columns_ = 0;
}

// Move assignment.
S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  rows_ = other.rows_;
  columns_ = other.columns_;
  delete[] matrix_;
  matrix_ = other.matrix_;

  other.rows_ = 0;
  other.columns_ = 0;
  other.matrix_ = nullptr;
  return *this;
}

// Copy assignment
S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    if (matrix_ == nullptr || (rows_ * columns_ != other.rows_ * other.columns_)) {
      delete[] matrix_;
      matrix_ = new double[other.rows_ * other.columns_];
    }
    rows_ = other.rows_;
    columns_ = other.columns_;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < columns_; ++j) {
        (*this)(i, j) = other(i, j);
      }
    }
  }
  return *this;
}

// Destructor.
S21Matrix::~S21Matrix() {
  rows_ = 0;
  columns_ = 0;
  delete [] matrix_;
  matrix_ = nullptr;
}

int S21Matrix::get_rows() const {
  return rows_;
}

int S21Matrix::get_columns() const {
  return columns_;
}

void S21Matrix::set_rows(const int& new_rows) {
  if (new_rows <= 0) {
    throw std::out_of_range("value cannot be less than or equal to zero");
  }

  S21Matrix new_matrix(new_rows, columns_);
  double limit = new_rows > rows_ ? rows_ : new_rows;
  for (int i = 0; i < limit; ++i) {
    for (int j = 0; j < columns_; ++j) {
      new_matrix(i, j) = (*this)(i, j);
    }
  }
  (*this) = std::move(new_matrix);
}

void S21Matrix::set_columns(const int& new_cols) {
  if (new_cols <= 0) {
    throw std::out_of_range("value cannot be less than or equal to zero");
  }

  S21Matrix new_matrix(rows_, new_cols);
  double limit = new_cols > columns_ ? columns_ : new_cols;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < limit; ++j) {
      new_matrix(i, j) = (*this)(i, j);
    }
  }
  (*this) = std::move(new_matrix);
}

void S21Matrix::set_values(std::initializer_list<double> list) {
  if (static_cast<int>(list.size()) != rows_ * columns_) {
    throw std::out_of_range("index is out of range");
  }
  for (int i = 0; i < rows_ * columns_; ++i) {
    matrix_[i] = list.begin()[i];
  }
}

void S21Matrix::set_values(std::initializer_list<std::initializer_list<double>> list) {
  if (static_cast<int>(list.size()) != rows_) {
    throw std::out_of_range("index is out of range");
  }

  for (int i = 0; i < static_cast<int>(list.size()); ++i) {
    if (static_cast<int>(list.begin()->size()) != columns_) {
      throw std::out_of_range("index is out of range");
    }
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      // m_matrix[i][j] = list[i][j];
      matrix_[index(i, j)] = *((list.begin() + i)->begin() + j);
    }
  }
}

bool S21Matrix::eq_matrix(const S21Matrix& other) const {
  bool is_same = true;
  if (rows_ == other.rows_ && columns_ == other.columns_) {
    for (int i = 0; i < rows_ * columns_; ++i) {
      if (std::abs(matrix_[i] - other.matrix_[i]) > std::numeric_limits<float>::epsilon()) {
        is_same = false;
      }
    }
  } else {
    is_same = false;
  }
  return is_same;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    throw std::out_of_range("matrices have different size");
  }
  for (int i = 0; i < rows_ * columns_; ++i) {
      matrix_[i] += other.matrix_[i];
  }
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || columns_ != other.columns_) {
    throw std::out_of_range("matrices have different size");
  }
  for (int i = 0; i < rows_ * columns_; ++i) {
      matrix_[i] -= other.matrix_[i];
  }
}

void S21Matrix::mul_number(const double& num) {
  for (int i = 0; i < rows_ * columns_; ++i) {
    matrix_[i] *= num;
  }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
  if (columns_ != other.rows_) {
    throw std::range_error("matrix size error");
  }
  S21Matrix new_matrix(rows_, other.columns_);
  for (int k = 0; k < columns_; ++k) {
    for (int i = 0; i < new_matrix.rows_; ++i) {
      for (int j = 0; j < new_matrix.columns_; ++j) {
        new_matrix(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  (*this) = std::move(new_matrix);
}

S21Matrix S21Matrix::transpose() const {
  S21Matrix new_matrix(columns_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns_; ++j) {
      new_matrix(j, i) = (*this)(i, j);
    }
  }
  return new_matrix;
}

S21Matrix S21Matrix::calc_complements() const {
  if (rows_ != columns_ || rows_ == 0) {
    throw std::range_error("matrix is not square");
  }
  S21Matrix new_matrix(columns_, rows_);
  if (rows_ == 1) {
    new_matrix.matrix_[0] = 1;
  } else {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            new_matrix(i, j) = std::pow(-1, i + j) * minor_at(i, j).determinant();
        }
      }
  }
  return new_matrix;
}

double S21Matrix::determinant() const {
  if (rows_ != columns_ || rows_ == 0) {
    throw std::range_error("Matrix is not square");
  }
  double determinant = 0.0;
  if (rows_ == 1) {
    determinant = (*this)(0, 0);
  } else {
    for (int i = 0; i < columns_; i++) {
      S21Matrix minor = minor_at(0, i);
      determinant += std::pow(-1, i) * (*this)(0, i) * minor.determinant();
    }
  }
  return determinant;
}

S21Matrix S21Matrix::inverse_matrix() const {
  double deter = determinant();
  if (std::abs(deter) < std::numeric_limits<float>::epsilon()) {
    throw std::logic_error("determinant is zero");
  }
  S21Matrix new_matrix(std::move(calc_complements().transpose()));
  new_matrix.mul_number(1./deter);
  return new_matrix;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix new_matrix(*this);
  new_matrix.sum_matrix(other);
  return new_matrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix new_matrix(*this);
  new_matrix.sub_matrix(other);
  return new_matrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix new_matrix(*this);
  new_matrix.mul_matrix(other);
  return new_matrix;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return eq_matrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  sum_matrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  sub_matrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  mul_matrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  mul_number(num);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (matrix_ == nullptr) {
    throw std::invalid_argument("calling a bad allocated or an already deleted object");
  }
  if (i < 0 || i >= rows_ || j < 0 || j >= columns_) {
    throw std::out_of_range("index is out of range");
  }
  return matrix_[index(i, j)];
}

double S21Matrix::operator()(int i, int j) const {
  if (matrix_ == nullptr) {
    throw std::invalid_argument("calling a bad allocated or an already deleted object");
  }
  if (i < 0 || i >= rows_ || j < 0 || j >= columns_) {
    throw std::out_of_range("index is out of range");
  }
  return matrix_[index(i, j)];
}

bool S21Matrix::is_empty_object() const {
  return (matrix_ == nullptr);
}

// converts i and j into single array`s koefficient.
int S21Matrix::index(int i, int j) const {
  return i + j + i * (columns_ - 1);
}

S21Matrix S21Matrix::minor_at(int m, int n) const {
  S21Matrix result(rows_ - 1, columns_ - 1);

  for (int i = 0, i_new = 0; i < rows_; ++i) {
    if (i == m) continue;
    for (int j = 0, j_new = 0; j < columns_; ++j) {
      if (j == n) continue;
      result(i_new, j_new) = (*this)(i, j);
      ++j_new;
    }
    ++i_new;
  }
  return result;
}

S21Matrix operator*(const double& num, const S21Matrix& matrix) {
  S21Matrix new_matrix(matrix);
  new_matrix.mul_number(num);
  return new_matrix;
}

std::ostream& operator<<(std::ostream& os, const S21Matrix& matrix) {
  for (int i = 0; i < matrix.rows_; ++i) {
    for (int j = 0; j < matrix.columns_; ++j) {
      os << std::setw(2) << matrix(i, j) << " ";
    }
    os << std::endl;
  }
  return os;
}
