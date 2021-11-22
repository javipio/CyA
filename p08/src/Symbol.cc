/**
 * @author Javier Padilla Pío
 * @date 29/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Symbol.cc file: Symbol class is the atomic element of a chain or alphabet.
 *                 This file contains the implementatino of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/21198/mod_assign/introattachment/0/CyA_2021_2022_P06_DFA_Simulacion.pdf?forcedownload=1
 * Revision history:
 *                29/10/2021 - Creation (first version) of the code
 */

#include "Symbol.h"

#include <iostream>

Symbol::Symbol() = default;

Symbol::Symbol(std::string value) : value_(value){};

Symbol::Symbol(char value) : value_(std::string(1, value)){};

/**
 * @brief Returns the value of the symbol.
 */
const std::string Symbol::to_string() const { return value_; };

/**
 * @brief Operator to compare if symbol_1 previous in alphabetic order than
 * symbol_2.
 */
bool operator<(const Symbol& symbol_1, const Symbol& symbol_2) {
  return symbol_1.to_string() < symbol_2.to_string();
}

/**
 * @brief Operator to compare if symbol_1 previous in alphabetic order than
 * symbol_2.
 */
bool operator>(const Symbol& symbol_1, const Symbol& symbol_2) {
  return symbol_1.to_string() > symbol_2.to_string();
}

/**
 * @brief Operator to compare if symbol_1 is equal to symbol_2.
 */
bool Symbol::operator==(const Symbol other) const {
  return to_string() == other.to_string();
}
/**
 * @brief Operator to hash a symbol.
 */
size_t std::hash<Symbol>::operator()(const Symbol& symbol) const {
  return std::hash<std::string>()(symbol.to_string());
}