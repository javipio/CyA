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
  static const char kEmpty = '&';

  Chain();
  Chain(Symbol);

  Chain(std::string);

  Chain(std::vector<Symbol>);

  void push_back(Symbol new_symbol);

  Chain substr(int start, int size) const;

  int length() const;

  Chain inverse() const;

  Language prefixes() const;

  Language sufixes() const;

  Language sub_chains() const;

  Chain pow(int power) const;

  std::string to_string() const;

  Symbol operator[](int index);

  Alphabet alphabet() const;

  std::vector<Symbol>::const_iterator begin() const;

  std::vector<Symbol>::const_iterator end() const;

  void replace(Chain needle, Chain chain);

 private:
  std::vector<Symbol> chain_;
  Alphabet alphabet_;
};

Chain operator*(const Chain& chain_1, const Chain& chain_2);

bool operator==(const Chain& chain_1, const Chain& chain_2);

bool operator!=(const Chain& chain_1, const Chain& chain_2);

bool operator<(const Chain& chain_1, const Chain& chain_2);

bool operator>(const Chain& chain_1, const Chain& chain_2);

Chain operator+(const Chain& chain_1, const Chain& chain_2);

std::ostream& operator<<(std::ostream& output_stream, const Chain& chain);

#endif
