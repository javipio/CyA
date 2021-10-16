/**
 * @author Javier Padilla Pío
 * @date 09/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 2 - Símbolos alfabetos y cadenas.
 * Email: alu0101410463@ull.edu.es
 * Chain.h file: Chain class contains the logic to operate with a chain.
 *                 This file contains the interface of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                09/10/2021 - Creation (first version) of the code
 */

#include <iostream>
#include <vector>

#include "Alfabet.h"
#include "Simbol.h"

#ifndef CHAIN_H
#define CHAIN_H
class Chain {
 public:
  Chain() {}
  Chain(std::string);

  Chain(std::vector<Simbol>);

  /**
   * @brief Inserts a new character at the end of the chain.
   */
  void push_back(Simbol new_simbol);

  /**
   * @brief Returns a substring of the chain.
   */
  Chain substr(int start, int size) const;

  /**
   * @brief Returns the length of the chain.
   */
  int length() const;

  Chain inverse() const;

  /**
   * @brief Returns the prefixes of the chain.
   */
  std::vector<Chain> prefixes() const;

  /**
   * @brief Returns the sufixes of the chain.
   */
  std::vector<Chain> sufixes() const;

  /**
   * @brief Returns all the possible subchains of the chain.
   */
  std::vector<Chain> sub_chains() const;

  /**
   * @brief Given a certain opcode it will run a different operation on the
   * chain:
   *     - prefixes()
   *     - sufixes()
   *     - sub_chains()
   *     - length()
   *     - inverse()
   */
  std::string operate(const int opcode) const;

  /**
   * @brief Returns the chain as a plain string.
   */
  std::string to_string() const;

 private:
  std::vector<Simbol> cadena_;
  Alfabet alfabet_;

  /**
   * @brief Converts a vector of chains to a plain string separated by spaces.
   */
  std::string _vector_to_string(std::vector<Chain> chains) const;
};
#endif