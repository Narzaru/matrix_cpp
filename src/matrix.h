#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <exception>

class S21Matrix {
 private:
  int m_rows;
  int m_columns;
  double *m_matrix;

 public:
    /* default constructor */
    S21Matrix();
    /* size dependent constructor */
    S21Matrix(int rows, int cols);
    /* copy constructor */
    S21Matrix(const S21Matrix& other);
    /* move constructor */
    S21Matrix(S21Matrix&& other);
    /* destructor */
    ~S21Matrix();

    /* accessors */
    int get_rows() const;
    int get_columns() const;

    /* mathematical methods */
    bool eq_matrix(const S21Matrix& other) const;
    void sum_matrix(const S21Matrix& other);
    void sub_matrix(const S21Matrix& other);
    void mul_number(const double num);
    void mul_matrix(const S21Matrix& other);
    S21Matrix transpose() const;
    S21Matrix calc_complements() const;
    double determinant() const;
    S21Matrix inverse_matrix() const;

    S21Matrix& operator+(S21Matrix other) const;
    S21Matrix& operator-(S21Matrix other) const;
    S21Matrix& operator*(S21Matrix other) const;
    S21Matrix& operator==(S21Matrix other) const;
    S21Matrix& operator=(S21Matrix other) const;
    S21Matrix& operator+=(S21Matrix other);
    S21Matrix& operator-=(S21Matrix other);
    S21Matrix& operator*=(S21Matrix other);
    double& operator()(int i, int j);

    /* get class state */
    bool is_empty_object() const;
};

#endif  /* SRC_MATRIX_H_ */
