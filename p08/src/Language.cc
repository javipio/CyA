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
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/21198/mod_assign/introattachment/0/CyA_2021_2022_P06_DFA_Simulacion.pdf?forcedownload=1
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

/**
 * @brief Returns the length of the language.
 */
int Language::length() const { return language_.size(); }

/**
 * @brief Appends a chain to the end of the language.
 * @param[in] chain
 */
void Language::push_back(Chain chain) { language_.push_back(chain); }

/**
 * @brief Operator to access individual chains of the language.
 */
const Chain& Language::operator[](int index) const { return language_[index]; }

/**
 * @brief Operator to output the language to a stream.
 * @param[in] output_stream Stream where the language will be introduced.
 * @param[in] language Language to introduce.
 */
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
