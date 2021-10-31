/**
 * @author Javier Padilla Pío
 * @date 16/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Alphabet.cc file: Alphabet class is the data structure used to store all the
 *                 symbols of an alphabet.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                16/10/2021 - Creation (first version) of the code
 */

#include "Alphabet.h"

Alphabet::Alphabet(std::vector<std::string> raw_alphabet) {
  for (const auto symbol : raw_alphabet) {
    alphabet_.insert(Symbol(symbol));
  }
}

bool Alphabet::symbol_exists(const Symbol& needle) const {
  for (const auto symbol : alphabet_) {
    if (symbol.to_string() == needle.to_string()) return true;
  }
  return false;
}

void Alphabet::insert(Symbol symbol) { alphabet_.insert(symbol); }

bool Alphabet::contains(Alphabet alphabet) const {
  for (const auto& symbol : alphabet) {
    if (!symbol_exists(symbol)) {
      return false;
    }
  }
  return true;
}

std::set<Symbol>::iterator Alphabet::begin() { return alphabet_.begin(); }

std::set<Symbol>::iterator Alphabet::end() { return alphabet_.end(); }