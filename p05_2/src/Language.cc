/**
 * @author Javier Padilla Pío
 * @date 29/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Language.cc file: Language class contains the logic to operate with a
 * language. This file contains the implementation of the class. References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/20878/mod_assign/introattachment/0/CyA_2021_2022_P05_DFAsPatrones.pdf?forcedownload=1
 * Revision history:
 *                29/10/2021 - Creation (first version) of the code
 */

#include "Language.h"

#include <fstream>

Language::Language() = default;

Language::Language(std::string filename) {
  std::ifstream input_file(filename);
  std::string line;

  while (std::getline(input_file, line)) {
    language_.push_back(Chain(line));
  }

  input_file.close();
}

Language::Language(std::vector<Chain> raw_language) {
  language_ = raw_language;
}

int Language::length() const { return language_.size(); }

const Chain& Language::operator[](int index) const { return language_[index]; }

std::ostream& operator<<(std::ostream& output_stream,
                         const Language& language) {
  output_stream << "{";
  // We iterate over every chain of the language adding them to the stream.
  for (int i = 0; i < language.length(); i++) {
    output_stream << language[i].to_string();

    if (i + 1 < language.length()) {
      output_stream << COMMA + SPACE;
    }  // The comma isn't needed in the last chain.
  }
  output_stream << "}";
  return output_stream;
}

void Language::write_file(std::string output_filename, int opcode) {
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

  for (int i = 0; i < language_.size(); i++) {
    switch (opcode) {
      case 1:
        output_file << std::to_string(language_[i].length()) << std::endl;
        break;
      case 2:
        output_file << language_[i].inverse() << std::endl;
        break;
      case 3:
        output_file << language_[i].prefixes() << std::endl;
        break;
      case 4:
        output_file << language_[i].sufixes() << std::endl;
        break;
      case 5:
        output_file << language_[i].sub_chains() << std::endl;
        break;
      case 6: {
        const Chain auxiliar_chain = Chain(aux);
        std::string operador;

        if (language_[i] == auxiliar_chain) {
          operador = " == ";
        } else if (language_[i] > auxiliar_chain) {
          operador = " > ";
        } else if (language_[i] < auxiliar_chain) {
          operador = " < ";
        } else {
          operador = " != ";
        }

        output_file << language_[i] << operador << auxiliar_chain << std::endl;
        break;
      }
      case 7: {
        output_file << (language_[i] * Chain(aux)) << std::endl;
        break;
      }
      case 8: {
        output_file << language_[i].pow(n) << std::endl;
        break;
      }
      default:
        throw std::invalid_argument("Solo se aceptan OPCODES del 1 al 8");
    }
  }
  output_file.close();
}

void Language::push_back(Chain chain) { language_.push_back(chain); }
