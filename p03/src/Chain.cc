/**
 * @author Javier Padilla Pío
 * @date 16/10/2021
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
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                16/10/2021 - Creation (first version) of the code
 */

#include "Chain.h"

#include <cassert>
#include <iostream>
#include <vector>

const Chain EMPTY_CHAIN = Chain("&");

Chain::Chain() = default;

Chain::Chain(std::string line) {
  std::vector<std::string> alfabeto;
  std::string temp;
  std::string chain;

  for (const auto& character : line) {
    if (character == SPACE) {
      alfabeto.push_back(temp);
      temp = "";
    } else {
      temp += character;
    }
  }

  chain = temp;
  // If there is no alfabet it will be extracted from the chain.
  if (alfabeto.size() == 0) {
    for (const auto& character : temp) {
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
  std::vector<Chain> prefixes_;
  prefixes_.push_back(EMPTY_CHAIN);

  for (int i = 1; i <= length(); i++) {
    prefixes_.push_back(substr(0, i));
  }

  return prefixes_;
}

std::vector<Chain> Chain::sufixes() const {
  std::vector<Chain> sufixes_;
  sufixes_.push_back(EMPTY_CHAIN);

  for (int i = length() - 1; i >= 0; i--) {
    sufixes_.push_back(substr(i, length() - i));
  }

  return sufixes_;
}

std::vector<Chain> Chain::sub_chains() const {
  std::vector<Chain> sub_chains_;
  sub_chains_.push_back(EMPTY_CHAIN);

  for (int i = 0; i < length(); i++) {
    for (int j = i; j < length(); j++) {
      sub_chains_.push_back(substr(i, length() - j));
    }
  }

  return sub_chains_;
}

std::string Chain::to_string() const {
  std::string output_string;
  for (const auto simbol : cadena_) {
    output_string += simbol.get();
  }

  return output_string;
}

Chain Chain::pow(int power) const {
  if (!power) return Chain("");

  return (*this) * pow(power - 1);
}

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
  std::vector<Chain> chains = chain_2.sub_chains();

  for (auto const& prefix : chains) {
    if (chain_1 == prefix) return true;
  }
  return false;
}

bool operator>(const Chain& chain_1, const Chain& chain_2) {
  std::vector<Chain> chains = chain_1.sub_chains();

  for (auto const& prefix : chains) {
    if (chain_2 == prefix) return true;
  }
  return false;
}

std::ostream& operator<<(std::ostream& output_stream, const Chain& chain) {
  return output_stream << chain.to_string();
}