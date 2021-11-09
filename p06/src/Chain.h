/**
 * @author Javier Padilla Pío
 * @date 29/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Chain.h file: Chain class contains the logic to operate with a chain.
 *                 This file contains the interface of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/21198/mod_assign/introattachment/0/CyA_2021_2022_P06_DFA_Simulacion.pdf?forcedownload=1
 * Revision history:
 *                29/10/2021 - Creation (first version) of the code
 */

#include <iostream>
#include <vector>

#include "Alphabet.h"
#include "Symbol.h"

#ifndef CHAIN_H_
#define CHAIN_H_

// Forward declaration so that Chain and language can import each other.
#ifndef CHAIN_D_
#define CHAIN_D_
class Chain;
#include "Language.h"
#endif

const char SPACE = ' ';
const std::string COMMA = ",";

class Chain {
 public:
  Chain();
  Chain(std::string);

  Chain(std::vector<Symbol>);

  /**
   * @brief Inserts a new character at the end of the chain.
   * @param[in] new_symbol
   */
  void push_back(Symbol new_symbol);

  /**
   * @brief Returns a substring of the chain.
   * @param[in] start
   * @param[in] size
   */
  Chain substr(int start, int size) const;

  /**
   * @brief Returns the length of the chain.
   */
  int length() const;

  /**
   * @brief Returns the string with the symbols in the inverted order.
   */
  Chain inverse() const;

  /**
   * @brief Returns the prefixes of the chain.
   */
  Language prefixes() const;

  /**
   * @brief Returns the sufixes of the chain.
   */
  Language sufixes() const;

  /**
   * @brief Returns all the possible subchains of the chain.
   */
  Language sub_chains() const;

  /**
   * @brief
   * @param[in] power
   */
  Chain pow(int power) const;

  /**
   * @brief Returns the chain as a plain string.
   */
  std::string to_string() const;

  /**
   * @brief Operator to access individual elements of the alphabet.
   */
  Symbol operator[](int index);

  /**
   * @brief Simple getter.
   */
  Alphabet alphabet() const;

  std::vector<Symbol>::const_iterator begin() const;

  std::vector<Symbol>::const_iterator end() const;

 private:
  std::vector<Symbol> chain_;
  Alphabet alphabet_;
};

/**
 * @brief Operator to concatenate two chains.
 */
Chain operator*(const Chain& chain_1, const Chain& chain_2);

/**
 * @brief Operator to compare if two chains are equal.
 */
bool operator==(const Chain& chain_1, const Chain& chain_2);

/**
 * @brief Operator to compare if two chains are not equal.
 */
bool operator!=(const Chain& chain_1, const Chain& chain_2);

/**
 * @brief Operator to compare if the first chain is subchain of the second.
 */
bool operator<(const Chain& chain_1, const Chain& chain_2);

/**
 * @brief Operator to compare if chain_1 previous in alphabetic order than
 * chain_2.
 */
bool operator>(const Chain& chain_1, const Chain& chain_2);

Chain operator+(const Chain& chain_1, const Chain& chain_2);

/**
 * @brief Operator to compare if chain_2 previous in alphabetic order than
 * chain_1.
 */
std::ostream& operator<<(std::ostream& output_stream, const Chain& chain);
#endif
