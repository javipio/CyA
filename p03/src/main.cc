/**
 * @author Javier Padilla Pío
 * @date 16/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * main.cc file: Entrypoint for the program.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                16/10/2021 - Creation (first version) of the code
 */

#include <fstream>
#include <iostream>
#include <vector>

#include "Language.h"

int main(int argc, char* argv[]) {
  if (argc < 4) {
    std::cout << "Uso: ./chains input.txt output.txt opcode\n";
    return 1;
  }

  const std::string input_filename = argv[1];
  const std::string output_filename = argv[2];
  const int opcode = atoi(argv[3]);

  Language chains = Language(input_filename);

  chains.write_file(output_filename, opcode);

  return 0;
}
