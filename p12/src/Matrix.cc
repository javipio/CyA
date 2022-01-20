/**
 * @author Javier Padilla Pío
 * @date 16/01/2022
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en ingeniería informática
 * Curso: 2º
 * Practice 12 - DyV
 * Email: alu0101410463@ull.edu.es
 * Matrix.cc: Implementación de la clase Matrix para operar con matrices cuadradas.
 * Revision history:
 *                16/01/2022 - Creation (first version) of the code
 */

#include "Matrix.h"

Matrix::Matrix() = default;

Matrix::Matrix(std::vector<float> matrix, int n) : n_{n} {
  matrix_.resize(n * n);
  memcpy(matrix_.data(), matrix.data(), sizeof(float) * matrix.size());
}

Matrix::Matrix(int n) : n_{n} { matrix_.resize(n * n, 0); }

void Matrix::ingest(std::ifstream& input_filestream) {
  std::string line;
  getline(input_filestream, line);

  n_ = stoi(line);

  if (matrix_.size() != stoi(line)) {
    matrix_.resize(n_ * n_);
  }

  int i = 0;

  while (getline(input_filestream, line)) {
    auto parsed_line = Split(line, ",");

    if (parsed_line.size() < n_) {
      throw std::invalid_argument(
          "Parsing error: El tamaño de la matriz no concuerda con la especificación del archivo.");
    }

    for (const auto num : parsed_line) {
      matrix_[i++] = std::stof(num);
    }
  }

  if (i != n_ * n_) {
    throw std::invalid_argument(
        "Parsing error: El tamaño de la matriz no concuerda con la especificación del archivo.");
  }
}

void Matrix::print(std::ostream& output_stream) const {
  output_stream << n_ << "\n";

  for (int i = 0; i < n_; i++) {
    for (int j = 0; j < n_; j++) {
      output_stream << at(i, j);
      if (j + 1 < n_) {
        output_stream << ", ";
      }
    }
    output_stream << "\n";
  }
  output_stream << std::endl;
}

Matrix Matrix::subMatrix(int position) const {
  int new_n = n_ / 2 + (n_ % 2 > 0) * 1;
  Matrix result(new_n);

  for (int new_i = 0, orig_i = (position > 1) * new_n; new_i < new_n; orig_i++, new_i++) {
    for (int new_j = 0, orig_j = (position % 2 > 0) * new_n; new_j < new_n; orig_j++, new_j++) {
      if ((orig_i * n_ + orig_j) > n_ * n_ ||
          (new_j + 1) % new_n == 0 && orig_j % n_ == 0 && new_n > 1) {
        continue;
      }
      result(new_i, new_j) = at(orig_i, orig_j);
    }
  }

  return result;
}

Matrix Matrix::clasicMultiplication(const Matrix& lhs, const Matrix& rhs, int* real_mult_count) {
  assert(lhs.n() == rhs.n());
  float acc = 0;
  Matrix result(lhs.n());

  for (int i = 0; i < lhs.n(); i++) {
    for (int j = 0; j < lhs.n(); j++) {
      for (int k = 0; k < lhs.n(); k++) {
        if (real_mult_count != nullptr) (*real_mult_count)++;
        acc += lhs.at(i, k) * rhs.at(k, j);
      }

      result(i, j) = acc;
      acc = 0;
    }
  }

  return result;
}

Matrix Matrix::DyV(const Matrix& lhs, const Matrix& rhs, int* real_mult_count) {
  assert(lhs.n() == rhs.n());

  if (lhs.n() == 1) {
    (*real_mult_count)++;
    return Matrix({lhs.at(0, 0) * rhs.at(0, 0)}, 1);
  };

  // GENERAR LAS SUBMATRICES RECURSIVAMENTE
  auto res_1 = DyV(lhs.subMatrix(0), rhs.subMatrix(0), real_mult_count) +
               DyV(lhs.subMatrix(1), rhs.subMatrix(2), real_mult_count);
  auto res_2 = DyV(lhs.subMatrix(0), rhs.subMatrix(1), real_mult_count) +
               DyV(lhs.subMatrix(1), rhs.subMatrix(3), real_mult_count);
  auto res_3 = DyV(lhs.subMatrix(2), rhs.subMatrix(0), real_mult_count) +
               DyV(lhs.subMatrix(3), rhs.subMatrix(2), real_mult_count);
  auto res_4 = DyV(lhs.subMatrix(2), rhs.subMatrix(1), real_mult_count) +
               DyV(lhs.subMatrix(3), rhs.subMatrix(3), real_mult_count);

  return joinSubMatrixes(res_1, res_2, res_3, res_4, lhs.n());
}

Matrix Matrix::strassen(const Matrix& lhs, const Matrix& rhs, int* real_mult_count, int min) {
  assert(lhs.n() == rhs.n());

  if (lhs.n() <= min) {
    return Matrix::clasicMultiplication(lhs, rhs, real_mult_count);
  };

  Matrix result(lhs.n());

  // SE GENERAN LAS MATRICES TEMPORALES DEFINIDAS POR EL ALGORITMO
  auto m_1 = strassen(lhs.subMatrix(0) + lhs.subMatrix(3), rhs.subMatrix(0) + rhs.subMatrix(3),
                      real_mult_count, min);
  auto m_2 = strassen(lhs.subMatrix(2) + lhs.subMatrix(3), rhs.subMatrix(0), real_mult_count, min);
  auto m_3 = strassen(lhs.subMatrix(0), rhs.subMatrix(1) - rhs.subMatrix(3), real_mult_count, min);
  auto m_4 = strassen(lhs.subMatrix(3), rhs.subMatrix(2) - rhs.subMatrix(0), real_mult_count, min);
  auto m_5 = strassen(lhs.subMatrix(0) + lhs.subMatrix(1), rhs.subMatrix(3), real_mult_count, min);
  auto m_6 = strassen(lhs.subMatrix(2) - lhs.subMatrix(0), rhs.subMatrix(0) + rhs.subMatrix(1),
                      real_mult_count, min);
  auto m_7 = strassen(lhs.subMatrix(1) - lhs.subMatrix(3), rhs.subMatrix(2) + rhs.subMatrix(3),
                      real_mult_count, min);

  // SE OPERA CON LAS MATRICES TEMPORALES PARA FORMAR LOS CUATRO CUADRANTES DEL RESULTADO
  auto res_1 = m_1 + m_4 - m_5 + m_7;
  auto res_2 = m_3 + m_5;
  auto res_3 = m_2 + m_4;
  auto res_4 = m_1 - m_2 + m_3 + m_6;

  return joinSubMatrixes(res_1, res_2, res_3, res_4, lhs.n());
}

float Matrix::at(int i, int j) const { return matrix_[i * n_ + j]; }

float& Matrix::at(int i, int j) { return matrix_[i * n_ + j]; }

float& Matrix::operator()(int i, int j) { return at(i, j); }

float Matrix::operator()(int i, int j) const { return at(i, j); }

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
  assert(lhs.n() == rhs.n());
  Matrix result(lhs.n());
  for (int i = 0; i < lhs.n(); i++) {
    for (int j = 0; j < lhs.n(); j++) {
      result(i, j) = lhs.at(i, j) + rhs.at(i, j);
    }
  }

  return result;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
  assert(lhs.n() == rhs.n());
  Matrix result(lhs.n());
  for (int i = 0; i < lhs.n(); i++) {
    for (int j = 0; j < lhs.n(); j++) {
      result(i, j) = lhs.at(i, j) - rhs.at(i, j);
    }
  }

  return result;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
  return Matrix::clasicMultiplication(lhs, rhs);
}

int Matrix::n() const { return n_; }

Matrix Matrix::joinSubMatrixes(const Matrix& top_left, const Matrix& top_right,
                               const Matrix& bottom_left, const Matrix& bottom_right, int n) {
  Matrix result(n);

  int sub_n = top_left.n();

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i < sub_n && j < sub_n) {
        result(i, j) = top_left(i, j);
      } else if (i < sub_n && j >= sub_n) {
        result(i, j) = top_right(i, j - sub_n);
      } else if (i >= sub_n && j < sub_n) {
        result(i, j) = bottom_left(i - sub_n, j);
      } else if (i >= sub_n && j >= sub_n) {
        result(i, j) = bottom_right(i - sub_n, j - sub_n);
      }
    }
  }

  return result;
}

std::vector<std::string> Matrix::Split(const std::string& chain,
                                       const std::string seperator) const {
  std::vector<std::string> output;
  size_t prev_pos = 0, pos = 0;

  while ((pos = chain.find(seperator, pos)) != std::string::npos) {
    std::string substring(chain.substr(prev_pos, pos - prev_pos));
    output.push_back(substring);
    pos += seperator.length();
    prev_pos = pos;
  }

  output.push_back(chain.substr(prev_pos, pos - prev_pos));  // Last word

  return output;
}