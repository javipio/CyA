/**
 * @author Javier Padilla Pío
 * @date 09/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 2 - Símbolos alfabetos y cadenas.
 * Email: alu0101410463@ull.edu.es
 * main.cc file: Entrypoint for the program.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                09/10/2021 - Creation (first version) of the code
 */

#include <fstream>
#include <iostream>
#include <vector>

#include "Alfabet.h"
#include "Chain.h"

std::vector<Chain> read_file(std::string filename) {
  std::ifstream input_file(filename);
  std::string line;
  std::vector<Chain> chains;

  while (std::getline(input_file, line)) {
    chains.push_back(Chain(line));
  }

  input_file.close();
  return chains;
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Faltan parámetros" << std::endl;
    return 1;
  }

  const std::string input_filename = argv[1];
  const std::string output_filename = argv[2];
  const int opcode = atoi(argv[3]);

  std::vector<Chain> chains = read_file(input_filename);

  std::ofstream output_file(output_filename);

  for (const auto chain : chains) {
    output_file << chain.operate(opcode) << std::endl;
  }

  output_file.close();

  return 0;
}
