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

/**
 * @brief Reads from the input file and returns each line as a chain.
 */
Language read_file(std::string filename) {
  std::ifstream input_file(filename);
  std::string line;
  Language chains;

  while (std::getline(input_file, line)) {
    chains.push_back(Chain(line));
  }

  input_file.close();
  return chains;
}

/**
 * @brief Writes to the output file taking into account the opcode given.
 */
void write_file(std::string output_filename, int opcode, Language chains) {
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

  for (int i = 0; i < chains.length(); i++) {
    switch (opcode) {
      case 1:
        output_file << std::to_string(chains[i].length()) << std::endl;
        break;
      case 2:
        output_file << chains[i].inverse() << std::endl;
        break;
      case 3:
        output_file << chains[i].prefixes() << std::endl;
        break;
      case 4:
        output_file << chains[i].sufixes() << std::endl;
        break;
      case 5:
        output_file << chains[i].sub_chains() << std::endl;
        break;
      case 6: {
        const Chain auxiliar_chain = Chain(aux);
        std::string operador;

        if (chains[i] == auxiliar_chain) {
          operador = " == ";
        } else if (chains[i] > auxiliar_chain) {
          operador = " > ";
        } else if (chains[i] < auxiliar_chain) {
          operador = " < ";
        } else {
          operador = " != ";
        }

        output_file << chains[i] << operador << auxiliar_chain << std::endl;
        break;
      }
      case 7: {
        output_file << (chains[i] * Chain(aux)) << std::endl;
        break;
      }
      case 8: {
        output_file << chains[i].pow(n) << std::endl;
        break;
      }
      default:
        throw std::invalid_argument("Solo se aceptan OPCODES del 1 al 8");
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

  Language chains = read_file(input_filename);

  write_file(output_filename, opcode, chains);

  return 0;
}
