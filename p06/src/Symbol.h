/**
 * @author Javier Padilla Pío
 * @date 29/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Symbol.h file: Symbol class is the atomic element of a chain or alphabet.
 *                 This file contains the interface of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/20878/mod_assign/introattachment/0/CyA_2021_2022_P05_DFAsPatrones.pdf?forcedownload=1
 * Revision history:
 *                29/10/2021 - Creation (first version) of the code
 */

#include <iostream>

#ifndef SYMBOL_H_
#define SYMBOL_H_
class Symbol {
 public:
  Symbol();
  Symbol(std::string value);
  Symbol(char value);

  /**
   * @brief Returns the value of the symbol.
   */
  const std::string to_string() const;

 private:
  std::string value_;
};
#endif

/**
 * @brief Operator to compare if symbol_1 previous in alphabetic order than
 * symbol_2.
 */
bool operator<(const Symbol& symbol_1, const Symbol& symbol_2);

/**
 * @brief Operator to compare if symbol_1 previous in alphabetic order than
 * symbol_2.
 */
bool operator>(const Symbol& symbol_1, const Symbol& symbol_2);

/**
 * @brief Operator to compare if symbol_1 is equal to symbol_2.
 */
bool operator==(const Symbol& symbol_1, const std::string& symbol_2);
