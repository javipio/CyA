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

#include "Alfabet.h"
#include "Language.h"

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

void write_file(std::string output_filename, int opcode,
                std::vector<Chain> chains) {
  std::ofstream output_file(output_filename);
  std::string aux;
  int n;

  if (opcode == 6 || opcode == 7) {
    std::cout << "Cadena auxiliar: ";
    std::cin >> aux;
  }

  if (opcode == 8) {
    std::cout << "n: ";
    std::cin >> n;
  }

  for (const auto chain : chains) {
    switch (opcode) {
      case 1:
        output_file << std::to_string(chain.length()) << std::endl;
        break;
      case 2:
        output_file << chain.inverse() << std::endl;
        break;
      case 3:
        output_file << Language(chain.prefixes()) << std::endl;
        break;
      case 4:
        output_file << Language(chain.sufixes()) << std::endl;
        break;
      case 5:
        output_file << Language(chain.sub_chains()) << std::endl;
        break;
      case 6: {
        const Chain auxiliar_chain = Chain(aux);
        std::string operador;

        if (chain == auxiliar_chain) {
          operador = " == ";
        } else if (chain > auxiliar_chain) {
          operador = " > ";
        } else if (chain < auxiliar_chain) {
          operador = " < ";
        } else {
          operador = " != ";
        }

        output_file << chain << operador << auxiliar_chain << std::endl;
        break;
      }
      case 7: {
        output_file << (chain * Chain(aux)) << std::endl;
        break;
      }
      case 8: {
        output_file << chain.pow(n) << std::endl;
        break;
      }
      default:
        throw std::invalid_argument("Solo se aceptan OPCODES del 1 al ");
    }
  }
  output_file.close();
}

int main(int argc, char* argv[]) {
  if (argc < 4) {
    std::cout << "Uso: ./chains input.txt output.txt opcode\n";
    return 1;
  }

  const std::string input_filename = argv[1];
  const std::string output_filename = argv[2];
  const int opcode = atoi(argv[3]);

  std::vector<Chain> chains = read_file(input_filename);

  write_file(output_filename, opcode, chains);

  return 0;
}
