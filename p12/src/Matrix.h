/**
 * @author Javier Padilla Pío
 * @date 16/01/2022
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en ingeniería informática
 * Curso: 2º
 * Practice 12 - DyV
 * Email: alu0101410463@ull.edu.es
 * Matrix.h: Interfaz de la clase Matrix para operar con matrices cuadradas.
 * Revision history:
 *                16/01/2022 - Creation (first version) of the code
 */

#ifndef MATRIX_H_
#define MATRIX_H_
#include <assert.h>
#include <string.h>

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
class Matrix {
 public:
  Matrix();
  Matrix(std::vector<float> matrix, int n);

  Matrix(int n);

  /**
   * @brief Extrae una matriz de un stream de entrada.
   * @param[in] input_filestream Stream con la matriz.
   */
  void ingest(std::ifstream& input_filestream);

  /**
   * @brief Imprime la matriz a través de un stream de salida.
   * @param[in] output_stream Stream en el que escribir.
   */
  void print(std::ostream& output_stream = std::cout) const;

  /**
   * @brief Calcula la multiplicación de dos matrices con el método base.
   */
  static Matrix clasicMultiplication(const Matrix& lhs, const Matrix& rhs,
                                     int* real_mult_count = nullptr);

  /**
   * @brief Multiplica dos matrices utilizando la estrategia divide y vencerás.
   */
  static Matrix DyV(const Matrix& lhs, const Matrix& rhs, int* real_mult_count = 0);

  /**
   * @brief Multiplica dos matrices utilizando la estrategia divide y vencerás de manera iterativa.
   * @todo NO IMPLEMENTADO
   */
  static Matrix iterativeDyV(const Matrix& lhs, const Matrix& rhs);

  /**
   * @brief Multiplica dos matrices utilizando la estrategia strassen.
   */
  static Matrix strassen(const Matrix& lhs, const Matrix& rhs, int* real_mult_count = 0,
                         int min = 1);

  /**
   * @brief Multiplica dos matrices utilizando la estrategia strassen de manera iterativa.
   * @todo NO IMPLEMENTADO
   */
  static Matrix iterativestrassen(const Matrix& lhs, const Matrix& rhs, int min = 1);

  /**
   * @brief Devuelve el elemento de la matriz en la posición i, j.
   * @param[in] i Fila de la matriz.
   * @param[in] j Columna de la matriz.
   */
  inline float& at(int i, int j);

  /**
   * @brief Devuelve el elemento de la matriz en la posición i, j.
   * @param[in] i Fila de la matriz.
   * @param[in] j Columna de la matriz.
   */
  inline float at(int i, int j) const;

  /**
   * @brief Devuelve el elemento de la matriz en la posición i, j.
   * @param[in] i Fila de la matriz.
   * @param[in] j Columna de la matriz.
   */
  float& operator()(int i, int j);

  /**
   * @brief Devuelve el elemento de la matriz en la posición i, j.
   * @param[in] i Fila de la matriz.
   * @param[in] j Columna de la matriz.
   */
  float operator()(int i, int j) const;

  // GETTERS
  int n() const;

 private:
  std::vector<float> matrix_;
  int n_;

  /**
   * @brief Devuelve la submatriz ubicada en una de las esquinas de la matriz.
   * @param[in] position Esquina de la que extraer la submatriz.
   */
  Matrix subMatrix(int position) const;

  /**
   * @brief Dadas 4 submatrices las une formando una matriz.
   * @param[in] top_left Matriz del cuadrante superior izquierdo.
   * @param[in] top_right Matriz del cuadrante superior derecho.
   * @param[in] bottom_left Matriz del cuadrante inferior izquierdo.
   * @param[in] bottom_right Matriz del cuadrante inferior derecho.
   * @param[in] n Número de columnas de la matriz resultante por si las submatrices tienen padding.
   */
  static Matrix joinSubMatrixes(const Matrix& top_left, const Matrix& top_right,
                                const Matrix& bottom_left, const Matrix& bottom_right, int n);

  /**
   * @brief Divide una cadena de texto en cada ocurrencia de un separador.
   * @param[in] chain Cadena a dividir.
   * @param[in] separator Delimitador.
   */
  std::vector<std::string> Split(const std::string& chain, const std::string separator) const;
};

/**
 * @brief Operador para sumar matrices.
 */
Matrix operator+(const Matrix& lhs, const Matrix& rhs);

/**
 * @brief Operador para restar matrices.
 */
Matrix operator-(const Matrix& lhs, const Matrix& rhs);

/**
 * @brief Operador para multiplicar matrices por el método básico.
 */
Matrix operator*(const Matrix& lhs, const Matrix& rhs);

#endif
