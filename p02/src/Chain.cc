/**
 * @author Javier Padilla Pío
 * @date 09/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 2 - Símbolos alfabetos y cadenas.
 * Email: alu0101410463@ull.edu.es
 * Chain.cc file: Chain class contains the logic to operate with a chain.
 *                 This file contains the implementation of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                09/10/2021 - Creation (first version) of the code
 */

#include "Chain.h"

#include <cassert>
#include <iostream>
#include <vector>

const Chain EMPTY_CHAIN = Chain("&");
const char SPACE = ' ';

Chain::Chain(std::string line) {
  std::vector<std::string> alfabeto;
  std::string temp;
  std::string chain;

  for (const auto &character : line) {
    if (character == SPACE) {
      alfabeto.push_back(temp);
      temp = "";
    } else {
      temp += character;
    }
  }

  chain = temp;

  if (alfabeto.size() == 0) {
    for (const auto &character : temp) {
      alfabeto.push_back(std::string(1, character));
    }
  }
  alfabet_ = Alfabet(alfabeto);

  temp = "";
  for (const auto character : chain) {
    temp += character;
    if (alfabet_.simbol_exists(Simbol(temp))) {
      cadena_.push_back(Simbol(temp));
      temp = "";
    }
  }
}

Chain::Chain(std::vector<Simbol> raw_chain) { cadena_ = raw_chain; }

void Chain::push_back(Simbol new_simbol) { cadena_.push_back(new_simbol); }

int Chain::length() const { return cadena_.size(); }

Chain Chain::substr(int start, int size) const {
  assert(start >= 0 && size >= 0);
  std::vector<Simbol> new_chain = {
      cadena_.begin() + start,
      cadena_.end() - (cadena_.size() - (start + size))};
  return Chain(new_chain);
}

Chain Chain::inverse() const {
  Chain inverted_string;

  for (int i = length() - 1; i >= 0; i--) {
    inverted_string.push_back(cadena_[i]);
  }

  return inverted_string;
}

std::vector<Chain> Chain::prefixes() const {
  std::vector<Chain> prefixes;
  prefixes.push_back(EMPTY_CHAIN);

  for (int i = 1; i <= length(); i++) {
    prefixes.push_back(substr(0, i));
  }

  return prefixes;
}

std::vector<Chain> Chain::sufixes() const {
  std::vector<Chain> sufixes;
  sufixes.push_back(EMPTY_CHAIN);

  for (int i = length() - 1; i >= 0; i--) {
    sufixes.push_back(substr(i, length() - i));
  }

  return sufixes;
}

std::vector<Chain> Chain::sub_chains() const {
  std::vector<Chain> sub_chains;
  sub_chains.push_back(EMPTY_CHAIN);

  for (int i = 0; i < length(); i++) {
    for (int j = i; j < length(); j++) {
      sub_chains.push_back(substr(i, length() - j));
    }
  }

  return sub_chains;
}

std::string Chain::to_string() const {
  std::string output_string;
  for (const auto simbol : cadena_) {
    output_string += simbol.get();
  }

  return output_string;
}

std::string Chain::_vector_to_string(std::vector<Chain> chains) const {
  std::string output_string;
  for (const auto chain : chains) {
    output_string += chain.to_string() + SPACE;
  }

  return output_string;
}

std::string Chain::operate(const int opcode) const {
  switch (opcode) {
    case 1:
      return std::to_string(length());
    case 2:
      return inverse().to_string();
    case 3:
      return _vector_to_string(prefixes());
    case 4:
      return _vector_to_string(sufixes());
    case 5:
      return _vector_to_string(sub_chains());
    default:
      throw std::invalid_argument("Solo se aceptan OPCODES del 1 al 5");
  }
}
