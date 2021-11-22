/**
 * @author Javier Padilla Pío
 * @date 29/10/2021
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
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/21198/mod_assign/introattachment/0/CyA_2021_2022_P06_DFA_Simulacion.pdf?forcedownload=1
 * Revision history:
 *                29/10/2021 - Creation (first version) of the code
 */

#include "Alphabet.h"

Alphabet::Alphabet(std::vector<std::string> raw_alphabet) {
  for (const auto symbol : raw_alphabet) {
    alphabet_.insert(Symbol(symbol));
  }
}

Alphabet::Alphabet(std::set<Symbol> raw_copy) : alphabet_(raw_copy) {}

/**
 * @brief Checks if a symbol exists in an alphabet.
 * @param[in] needle
 */
bool Alphabet::symbol_exists(const Symbol& needle) const {
  for (const auto symbol : alphabet_) {
    if (symbol.to_string() == needle.to_string()) return true;
  }
  return false;
}

/**
 * @brief Appends a new symbol to the alphabet.
 * @param[in] symbol Symbol to insert.
 */
void Alphabet::insert(Symbol symbol) { alphabet_.insert(symbol); }

/**
 * @brief Checks wether an alphabet is contained in another one.
 * @param[in] alphabet Other alphabet to compare with.
 */
bool Alphabet::contains(Alphabet alphabet) const {
  for (const auto& symbol : alphabet) {
    if (!symbol_exists(symbol)) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Returns the beginning of the alphabet_ set.
 */
std::set<Symbol>::iterator Alphabet::begin() { return alphabet_.begin(); }

/**
 * @brief Returns the end of the alphabet_ set.
 */
std::set<Symbol>::iterator Alphabet::end() { return alphabet_.end(); }

/**
 * @brief Returns the beginning of the alphabet_ set.
 */
std::set<Symbol>::const_iterator Alphabet::begin() const {
  return alphabet_.begin();
}

/**
 * @brief Returns the end of the alphabet_ set.
 */
std::set<Symbol>::const_iterator Alphabet::end() const {
  return alphabet_.end();
}

/**
 * @brief Joins two alphaets.
 * @param[in] alphabet_1 First alphabet to join.
 * @param[in] alphabet_2 Second alphabet to join.
 * @return Joined alphabet.
 */
Alphabet operator|(const Alphabet& alphabet_1, const Alphabet& alphabet_2) {
  std::set<Symbol> join;
  std::set_union(alphabet_1.begin(), alphabet_1.end(), alphabet_2.begin(),
                 alphabet_2.end(), std::inserter(join, std::begin(join)));
  return Alphabet(join);
}
