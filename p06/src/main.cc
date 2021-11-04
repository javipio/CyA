/**
 * @author Javier Padilla Pío
 * @date 29/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * main.cc: Entrypoint for the program.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/20878/mod_assign/introattachment/0/CyA_2021_2022_P05_DFAsPatrones.pdf?forcedownload=1
 * Revision history:
 *                29/10/2021 - Creation (first version) of the code
 */

#include <fstream>
#include <iostream>

#include "Dfa.h"
int main(int argc, char* argv[]) {
  if (argc == 2) {
    std::string input_file = argv[1];

    if (input_file == "--help" || input_file == "-h") {
      std::cout << "Usage: " << argv[0] << "DEFINITION CHAINS_FILE DEST\n";
      std::cout << "Reads a file containing the formal definition of the DFA "
                   "from DEFINITION, then cheks for subsequences in CHAIN and "
                   "stores them in DEST"
                << std::endl;
      return 0;
    }
  }

  if (argc < 4) {
    std::cout << argv[0] << ": missing operand\n";
    std::cout << "Try '" << argv[0] << " --help' for mor information."
              << std::endl;
    return 1;
  }

  std::string input_filename = argv[1];
  std::string chains_filename = argv[2];
  std::string output_filename = argv[3];
  std::ifstream input_file(input_filename);
  std::string chain;

  Dfa dfa(input_file);
  input_file.close();

  std::ifstream chains_file(chains_filename);
  std::ofstream output_file(output_filename);

  while (getline(chains_file, chain)) {
    output_file << chain << " -- " << (dfa.run(chain) ? "Accepted" : "Rejected")
                << std::endl;
  }

  chains_file.close();
  output_file.close();

  return 0;
}