#include <limits>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include "matrix.h"

/********************
 * FRIEND FUNCTIONS *
 ********************/
std::ostream& operator<<(std::ostream& os, const S21Matrix& matrix) {
  for (int i = 0; i < matrix.m_rows; ++i) {
    for (int j = 0; j < matrix.m_columns; ++j) {
      os << std::setw(2) << matrix(i, j) << " ";
    }
    os << std::endl;
  }
  return os;
}

/****************
 * CONSTRUCTORS *
 ****************/
// Base constructor with no arguments.
// It create a 3x3 zero matrix.
S21Matrix::S21Matrix()
  : m_rows(3),
    m_columns(3),
    m_matrix(new double[m_rows * m_columns]) {
  std::fill<double *>(m_matrix, m_matrix + m_rows * m_columns, 0.0);
}

// Constructor with two arguments, rows and columns.
// It create a RxC zero matrix.
S21Matrix::S21Matrix(int rows, int cols)
  : m_rows(rows),
    m_columns(cols),
    m_matrix(nullptr) {
  if (m_rows > 0 && m_columns > 0) {
    m_matrix = new double[m_rows * m_columns];
    std::fill(m_matrix, m_matrix + (m_rows * m_columns), 0.0);
  } else {
    m_rows = 0;
    m_columns = 0;
    throw std::invalid_argument("Matrix has the wrong size");
  }
}

// Copy constructor with const S21Matrix& argument.
// It allocates a new matrix and copy other matrix.
S21Matrix::S21Matrix(const S21Matrix& other)
  : m_rows(other.m_rows),
    m_columns(other.m_columns),
    m_matrix(nullptr) {
  if (!other.is_empty_object()) {
    m_matrix = new double[m_rows * m_columns];
    for (int i = 0; i < m_rows * m_columns; ++i) {
      m_matrix[i] = other.m_matrix[i];
    }
  }
}

// Destructor.
S21Matrix::~S21Matrix() {
  m_rows = 0;
  m_columns = 0;
  delete [] m_matrix;
  m_matrix = nullptr;
}

// Move constructor.
S21Matrix::S21Matrix(S21Matrix&& other)
  : m_rows(other.m_rows),
    m_columns(other.m_columns),
    m_matrix(other.m_matrix) {
  other.m_matrix = nullptr;
  other.m_rows = 0;
  other.m_columns = 0;
}

/*******
 * ANY *
 *******/
// converts i and j into single array`s koefficient.
int S21Matrix::index(int i, int j) const {
      return i + j + i * (m_columns - 1);
  }

/*************
 * ACCESSORS *
 *************/
int S21Matrix::get_rows() const {
  return m_rows;
}

int S21Matrix::get_columns() const {
  return m_columns;
}

bool S21Matrix::is_empty_object() const {
  return (m_matrix == nullptr);
}

/************
 * MUTATORS *
 ************/
void S21Matrix::set_values(std::initializer_list<double> list) {
  if (list.size() == m_rows * m_columns) {
    for (int i = 0; i < m_rows * m_columns; ++i) {
      m_matrix[i] = list.begin()[i];
    }
  } else {
    throw std::out_of_range("index is out of range");
  }
}

void S21Matrix::set_values(std::initializer_list<std::initializer_list<double>> list) {
  if (list.size() == m_rows) {
    for (int i = 0; i < list.size(); ++i) {
      if (list.begin()->size() != m_columns) {
        throw std::out_of_range("index is out of range");
      }
    }
    for (int i = 0; i < m_rows; ++i) {
      for (int j = 0; j < m_columns; ++j) {
        // m_matrix[i][j] = list[i][j];
        m_matrix[index(i, j)] = *((list.begin() + i)->begin() + j);
      }
    }
  } else {
    throw std::out_of_range("index is out of range");
  }
}

/***********
 * METHODS *
 ***********/
bool S21Matrix::eq_matrix(const S21Matrix& other) const {
  bool is_same = true;
  if (m_rows == other.m_rows && m_columns == other.m_columns) {
    for (int i = 0; i < m_rows * m_columns; ++i) {
      if (std::abs(m_matrix[i] - other.m_matrix[i]) > std::numeric_limits<float>::epsilon()) {
        is_same = false;
      }
    }
  } else {
    is_same = false;
  }
  return is_same;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
  if (m_rows == other.m_rows && m_columns == other.m_columns) {
    for (int i = 0; i < m_rows * m_columns; ++i) {
        m_matrix[i] += other.m_matrix[i];
    }
  } else {
    throw std::out_of_range("index is out of range");
  }
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
  if (m_rows == other.m_rows && m_columns == other.m_columns) {
    for (int i = 0; i < m_rows * m_columns; ++i) {
        m_matrix[i] -= other.m_matrix[i];
    }
  } else {
    throw std::out_of_range("index is out of range");
  }
}

void S21Matrix::mul_number(const double num) {
  for (int i = 0; i < m_rows * m_columns; ++i) {
    m_matrix[i] *= num;
  }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
  if (m_columns == other.m_rows) {
    S21Matrix new_matrix(m_rows, other.m_columns);
    for (int k = 0; k < m_columns; ++k) {
      for (int i = 0; i < new_matrix.m_rows; ++i) {
        for (int j = 0; j < new_matrix.m_columns; ++j) {
          new_matrix(i, j) += (*this)(i, k) * other(k, j);
        }
      }
    }
    (*this) = std::move(new_matrix);
  } else {
    throw std::range_error("matrix size error");
  }
}

S21Matrix S21Matrix::transpose() const {
  S21Matrix new_matrix(m_columns, m_rows);
  for (int i = 0; i < m_rows; ++i) {
    for (int j = 0; j < m_columns; ++j) {
      new_matrix(j, i) = (*this)(i, j);
    }
  }
  return new_matrix;
}

S21Matrix S21Matrix::calc_complements() const {
  if (m_rows == m_columns && m_rows != 0) {
    S21Matrix new_matrix(m_columns, m_rows);
    if (m_rows == 1) {
      new_matrix.m_matrix[0] = 1;
    } else {
        for (int i = 0; i < m_rows; i++) {
          for (int j = 0; j < m_columns; j++) {
              S21Matrix minor = minor_at(i, j);
              new_matrix(i, j) = std::pow(-1, i + j) * minor.determinant();
          }
        }
    }
    return new_matrix;
  } else {
    throw std::range_error("matrix is not square");
  }
}

double S21Matrix::determinant() const {
  if (m_rows == m_columns && m_rows != 0) {
    double determinant;
    if (m_rows == 1) {
      determinant = (*this)(0, 0);
    } else if (m_rows == 2) {
      determinant += (*this)(0, 0) * (*this)(1, 1);
      determinant -= (*this)(1, 0) * (*this)(0, 1);
    } else {
      for (int i = 0; i < m_columns; i++) {
        S21Matrix minor = minor_at(0, i);
        determinant += std::pow(-1, i) * (*this)(0, i) * minor.determinant();
      }
    }
    return determinant;
  } else {
    throw std::range_error("Matrix is not square");
  }
}

S21Matrix S21Matrix::minor_at(int m, int n) const {
  S21Matrix new_matrix(m_rows - 1, m_columns - 1);
  for (int i = 0; i < m_rows; i++) {
    for (int j = 0; j < m_columns; j++) {
      if (i != m && j != n) {
        if (i > m && j > n) {
          new_matrix(i - 1, j - 1) = (*this)(i, j);
        } else if (i > m) {
          new_matrix(i - 1, j) = (*this)(i, j);
        } else if (j > n) {
          new_matrix(i, j - 1) = (*this)(i, j);
        } else {
          new_matrix(i, j) = (*this)(i, j);
        }
      }
    }
  }
  return new_matrix;
}

S21Matrix S21Matrix::inverse_matrix() const {
  double deter = determinant();
  if (fabs(deter) > std::numeric_limits<float>::epsilon()) {
    S21Matrix new_matrix(std::move(calc_complements().transpose()));
    new_matrix.mul_number(1./deter);
    return new_matrix;
  } else {
    throw std::logic_error("determinant is zero");
  }
}

/*************
 * OPERATORS *
 *************/
double& S21Matrix::operator()(int i, int j) {
  if (m_matrix != nullptr) {
    if (i >= 0 && i < m_rows && j >= 0 && j < m_columns) {
      return m_matrix[index(i, j)];
    } else {
      throw std::out_of_range("index is out of range");
    }
  } else {
    throw std::invalid_argument("calling a bad allocated or an already deleted object");
  }
}

double S21Matrix::operator()(int i, int j) const {
  if (m_matrix != nullptr) {
    if (i >= 0 && i < m_rows && j >= 0 && j < m_columns) {
      return m_matrix[index(i, j)];
    } else {
      throw std::out_of_range("index is out of range");
    }
  } else {
    throw std::invalid_argument("calling a bad allocated or an already deleted object");
  }
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  m_rows = other.m_rows;
  m_columns = other.m_columns;
  delete [] m_matrix;
  m_matrix = other.m_matrix;
  other.m_rows = 0;
  other.m_columns = 0;
  other.m_matrix = nullptr;
  return *this;
}
