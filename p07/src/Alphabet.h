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

#include <set>
#include <vector>

#include "Symbol.h"

#ifndef ALPHABET_H_
#define ALPHABET_H_
class Alphabet {
 public:
  Alphabet() {}
  Alphabet(std::vector<std::string> raw_alphabet);

  /**
   * @brief Checks if a symbol exists in an alphabet.
   * @param[in] needle
   */
  bool symbol_exists(const Symbol& needle) const;

  /**
   * @brief Appends a new symbol to the alphabet.
   * @param[in] symbol Symbol to insert.
   */
  void insert(Symbol symbol);

  bool contains(Alphabet alphabet) const;

  /**
   * @brief Returns the beginning of the alphabet_ set.
   */
  std::set<Symbol>::iterator begin();

  /**
   * @brief Returns the end of the alphabet_ set.
   */
  std::set<Symbol>::iterator end();

 private:
  std::set<Symbol> alphabet_;
};
#endif
