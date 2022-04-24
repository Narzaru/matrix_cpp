#include <limits>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include "matrix.h"


// Base constructor with no arguments.
// It create a 3x3 zero matrix.
S21Matrix::S21Matrix()
  : m_rows(3),
    m_columns(3),
    m_matrix(new double[m_rows * m_columns]) {
  std::fill<double *>(m_matrix, m_matrix + (m_rows * m_columns), 0.0);
}

// Constructor with two arguments, rows and columns.
// It create a RxC zero matrix
S21Matrix::S21Matrix(int rows, int cols)
  : m_rows(rows),
    m_columns(cols),
    m_matrix(nullptr) {
  if (m_rows > 0 && m_columns > 0) {
    m_matrix = new double[m_rows * m_columns];
    std::fill(m_matrix, m_matrix + (m_rows * m_columns), 0.0);
  } else {
    throw std::invalid_argument("zero matrix size");
  }
}

// Copy constructor with const S21Matrix& argument.
// It allocates a new matrix and copy other matrix.
S21Matrix::S21Matrix(const S21Matrix& other)
  : m_rows(other.m_rows),
    m_columns(other.m_columns),
    m_matrix(nullptr) {
  if (other.m_matrix != nullptr) {
    m_matrix = new double[m_rows * m_columns];
    for (int i = 0; i < m_rows; ++i) {
      for (int j = 0; j < m_columns; ++j) {
        m_matrix[i + j + i * (m_columns - 1)] = other.m_matrix[i + j + i * (m_columns - 1)];
      }
    }
  }
}

S21Matrix::~S21Matrix() {
  m_rows = 0;
  m_columns = 0;
  delete [] m_matrix;
  m_matrix = nullptr;
}

S21Matrix::S21Matrix(S21Matrix&& other)
  : m_rows(other.m_rows),
    m_columns(other.m_columns),
    m_matrix(other.m_matrix) {
  other.m_matrix = nullptr;
  other.m_rows = 0;
  other.m_columns = 0;
}

int S21Matrix::get_rows() const {
  return m_rows;
}

int S21Matrix::get_columns() const {
  return m_columns;
}

bool S21Matrix::eq_matrix(const S21Matrix& other) const {
  bool is_same = true;
  if (m_rows == other.m_rows && m_columns == other.m_columns) {
    for (int i = 0; i < m_rows * m_columns; ++i) {
      if (std::abs(m_matrix[i] - other.m_matrix[i]) > std::numeric_limits<double>::epsilon()) {
        is_same = false;
      }
    }
  } else {
    is_same = false;
  }
  return is_same;
}

double& S21Matrix::operator()(int i, int j) {
  if (m_matrix != nullptr) {
    if (i >= 0 && i < m_rows && j >= 0 && j < m_columns) {
      return m_matrix[i + j + i * (m_columns - 1)];
    } else {
      throw std::out_of_range("indexes out of range");
    }
  } else {
    throw std::invalid_argument("calling a bad allocated or an already deleted object");
  }
}

bool S21Matrix::is_empty_object() const {
  return (m_matrix == nullptr);
}
