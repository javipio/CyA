/**
 * @author Javier Padilla Pío
 * @date 29/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Alphabet.h file: Alphabet class is the data structure used to store all the
 *                 symbols of an alphabet.
 *                 This file contains the interface of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/21198/mod_assign/introattachment/0/CyA_2021_2022_P06_DFA_Simulacion.pdf?forcedownload=1
 * Revision history:
 *                29/10/2021 - Creation (first version) of the code
 */

#include <algorithm>
#include <set>
#include <vector>

#include "Symbol.h"

#ifndef ALPHABET_H_
#define ALPHABET_H_
class Alphabet {
 public:
  Alphabet() {}

  Alphabet(std::vector<std::string> raw_alphabet);

  Alphabet(std::set<Symbol> raw_copy);

  bool symbol_exists(const Symbol& needle) const;

  void insert(Symbol symbol);

  bool contains(Alphabet alphabet) const;

  std::set<Symbol>::iterator begin();

  std::set<Symbol>::iterator end();

  std::set<Symbol>::const_iterator begin() const;

  std::set<Symbol>::const_iterator end() const;

 private:
  std::set<Symbol> alphabet_;
};
Alphabet operator|(const Alphabet& alphabet_1, const Alphabet& alphabet_2);

#endif
