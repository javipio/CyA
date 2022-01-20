/**
 * @author Javier Padilla Pío
 * @date 16/01/2022
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en ingeniería informática
 * Curso: 2º
 * Practice 12 - DyV
 * Email: alu0101410463@ull.edu.es
 * main.cc: Punto de entrada del programa.
 * Revision history:
 *                16/01/2022 - Creation (first version) of the code
 */

#include <chrono>
#include <iostream>
#include <vector>

#include "Matrix.h"

int main(int argc, char* argv[]) {
  if (argc < 4) {
    std::cerr << "Faltan argumentos." << std::endl;
    return 1;
  }

  Matrix matrix_1;
  Matrix matrix_2;
  Matrix result;

  int skip_param = 0;
  std::string type = argv[1];
  int dimension = 1;

  if (type == "-s\0" && std::string(argv[2]) == "-n") {
    if (argc < 6) {
      std::cerr << "Faltan argumentos." << std::endl;
      return 1;
    }

    skip_param = 2;
    dimension = atoi(argv[3]);
  }

  std::ifstream file_1(argv[2 + skip_param]);
  std::ifstream file_2(argv[3 + skip_param]);
  std::ofstream output_file(argv[4 + skip_param]);

  matrix_1.ingest(file_1);
  matrix_2.ingest(file_2);
  file_1.close();
  file_2.close();

  std::chrono::_V2::system_clock::time_point t1;
  std::chrono::_V2::system_clock::time_point t2;

  int count = 0;

  if (type == "-c") {
    t1 = std::chrono::high_resolution_clock::now();
    result = Matrix::clasicMultiplication(matrix_1, matrix_2, &count);
    t2 = std::chrono::high_resolution_clock::now();
  } else if (type == "-d") {
    t1 = std::chrono::high_resolution_clock::now();
    result = Matrix::DyV(matrix_1, matrix_2, &count);
    t2 = std::chrono::high_resolution_clock::now();
  } else if (type == "-s") {
    t1 = std::chrono::high_resolution_clock::now();
    result = Matrix::strassen(matrix_1, matrix_2, &count, dimension);
    t2 = std::chrono::high_resolution_clock::now();
  }

  std::cout << "Tiempo de ejecución: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms\n";
  std::cout << "Número de mutltiplicaciones de enteros: " << count << std::endl;
  // result.print();
  result.print(output_file);

  output_file.close();

  return 0;
}
