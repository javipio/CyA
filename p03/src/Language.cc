/**
 * @author Javier Padilla Pío
 * @date 16/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Language.cc file: Language class contains the logic to operate with a
 * language. This file contains the implementation of the class. References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                16/10/2021 - Creation (first version) of the code
 */

#include "Language.h"

Language::Language() = default;

Language::Language(std::vector<Chain> raw_language) {
  language_ = raw_language;
}

int Language::length() const { return language_.size(); }

const Chain& Language::operator[](int index) const { return language_[index]; }

std::ostream& operator<<(std::ostream& output_stream,
                         const Language& language) {
  output_stream << "{";
  for (int i = 0; i < language.length(); i++) {
    output_stream << language[i].to_string();
    if (i + 1 < language.length()) {
      output_stream << COMMA + SPACE;
    }  // La coma no se pone en el último elemento
  }
  output_stream << "}";
  return output_stream;
}
