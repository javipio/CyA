/**
 * @author Javier Padilla Pío
 * @date 29/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Chain.cc file: Chain class contains the logic to operate with a chain.
 *                 This file contains the implementation of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/20878/mod_assign/introattachment/0/CyA_2021_2022_P05_DFAsPatrones.pdf?forcedownload=1
 * Revision history:
 *                29/10/2021 - Creation (first version) of the code
 */

#include "Chain.h"

#include <cassert>
#include <iostream>
#include <vector>

const Chain EMPTY_CHAIN = Chain("&");

Chain::Chain() = default;

Chain::Chain(std::string line) {
  if (line == "&") return;  // Empty chain

  std::vector<std::string> alphabet;
  std::string temp;
  std::string chain;

  for (const auto& character : line) {
    alphabet.push_back(std::string(1, character));
  }

  alphabet_ = Alphabet(alphabet);

  temp = "";
  for (const auto& character : line) {
    temp += character;
    if (alphabet_.symbol_exists(Symbol(temp))) {
      chain_.push_back(Symbol(temp));
      temp = "";
    }
  }
}

Chain::Chain(std::vector<Symbol> raw_chain) { chain_ = raw_chain; }

void Chain::push_back(Symbol new_symbol) { chain_.push_back(new_symbol); }

int Chain::length() const { return chain_.size(); }

Chain Chain::substr(int start, int size) const {
  assert(start >= 0 && size >= 0);
  std::vector<Symbol> new_chain = {
      chain_.begin() + start, chain_.end() - (chain_.size() - (start + size))};
  return Chain(new_chain);
}

Chain Chain::inverse() const {
  Chain inverted_string;

  for (int i = length() - 1; i >= 0; i--) {
    inverted_string.push_back(chain_[i]);
  }

  return inverted_string;
}

Language Chain::prefixes() const {
  Language prefixes_;
  prefixes_.push_back(EMPTY_CHAIN);

  for (int i = 1; i <= length(); i++) {
    prefixes_.push_back(substr(0, i));
  }

  return prefixes_;
}

Language Chain::sufixes() const {
  Language sufixes_;
  sufixes_.push_back(EMPTY_CHAIN);

  for (int i = length() - 1; i >= 0; i--) {
    sufixes_.push_back(substr(i, length() - i));
  }

  return sufixes_;
}

Language Chain::sub_chains() const {
  Language sub_chains_;
  sub_chains_.push_back(EMPTY_CHAIN);

  for (int i = 0; i < length(); i++) {
    for (int j = i; j < length(); j++) {
      sub_chains_.push_back(substr(i, length() - j));
    }
  }

  return sub_chains_;
}

std::string Chain::to_string() const {
  if (chain_.size() == 0) {  // Empty chain.
    return "&";
  }

  std::string output_string;
  for (const auto symbol : chain_) {
    output_string += symbol.to_string();
  }

  return output_string;
}

Chain Chain::pow(int power) const {
  if (!power) return Chain("");

  return (*this) * pow(power - 1);
}

Alphabet Chain::alphabet() const { return alphabet_; }

// OPERATORS

Chain operator*(const Chain& chain_1, const Chain& chain_2) {
  return Chain(chain_1.to_string() + chain_2.to_string());
}

bool operator==(const Chain& chain_1, const Chain& chain_2) {
  return chain_1.to_string() == chain_2.to_string();
}

bool operator!=(const Chain& chain_1, const Chain& chain_2) {
  return !(chain_1 == chain_2);
}

bool operator<(const Chain& chain_1, const Chain& chain_2) {
  return chain_1.to_string() < chain_2.to_string();
}

bool operator>(const Chain& chain_1, const Chain& chain_2) {
  return chain_1.to_string() > chain_2.to_string();
}

std::ostream& operator<<(std::ostream& output_stream, const Chain& chain) {
  return output_stream << chain.to_string();
}

Symbol Chain::operator[](int index) { return chain_[index]; };

Chain operator+(const Chain& chain_1, const Chain& chain_2) {
  return chain_1.to_string() + chain_2.to_string();
}