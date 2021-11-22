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
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/21198/mod_assign/introattachment/0/CyA_2021_2022_P06_DFA_Simulacion.pdf?forcedownload=1
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

Chain::Chain(Symbol symbol) : chain_({symbol}) { alphabet_.insert(symbol); }

Chain::Chain(std::vector<Symbol> raw_chain) { chain_ = raw_chain; }

/**
 * @brief Inserts a new character at the end of the chain.
 * @param[in] new_symbol
 */
void Chain::push_back(Symbol new_symbol) { chain_.push_back(new_symbol); }

/**
 * @brief Returns the length of the chain.
 */
int Chain::length() const { return chain_.size(); }

/**
 * @brief Returns a substring of the chain.
 * @param[in] start
 * @param[in] size
 */
Chain Chain::substr(int start, int size) const {
  assert(start >= 0 && size >= 0);
  std::vector<Symbol> new_chain = {
      chain_.begin() + start, chain_.end() - (chain_.size() - (start + size))};
  return Chain(new_chain);
}

/**
 * @brief Returns the string with the symbols in the inverted order.
 */
Chain Chain::inverse() const {
  Chain inverted_string;

  for (int i = length() - 1; i >= 0; i--) {
    inverted_string.push_back(chain_[i]);
  }

  return inverted_string;
}

/**
 * @brief Returns the prefixes of the chain.
 */
Language Chain::prefixes() const {
  Language prefixes_;
  prefixes_.push_back(EMPTY_CHAIN);

  for (int i = 1; i <= length(); i++) {
    prefixes_.push_back(substr(0, i));
  }

  return prefixes_;
}

/**
 * @brief Returns the sufixes of the chain.
 */
Language Chain::sufixes() const {
  Language sufixes_;
  sufixes_.push_back(EMPTY_CHAIN);

  for (int i = length() - 1; i >= 0; i--) {
    sufixes_.push_back(substr(i, length() - i));
  }

  return sufixes_;
}

/**
 * @brief Returns all the possible subchains of the chain.
 */
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

/**
 * @brief Returns the chain as a plain string.
 */
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

/**
 * @brief
 * @param[in] power
 */
Chain Chain::pow(int power) const {
  if (!power) return Chain("");

  return (*this) * pow(power - 1);
}

/**
 * @brief Simple getter.
 */
Alphabet Chain::alphabet() const { return alphabet_; }

/**
 * @brief Returns an interator to the begining of the inner vector.
 */
std::vector<Symbol>::const_iterator Chain::begin() const {
  return chain_.begin();
}

/**
 * @brief Returns an interator to the ending of the inner vector.
 */
std::vector<Symbol>::const_iterator Chain::end() const { return chain_.end(); }

/**
 * @brief Replaces the given subchain with another chain.
 * @param[in] needle Subchain to replace.
 * @param[in] chain The chain to replace the subchain with.
 */
void Chain::replace(Chain needle, Chain chain) {
  int starting_pos = 0;
  int i = 0;

  for (const auto symbol : chain_) {
    if (symbol == needle[i]) {
      if (i == needle.length() - 1) {
        for (int j = chain.length() - 1; j >= 0; j--) {
          chain_.insert(begin() + starting_pos, chain[j]);
        }

        for (int j = 0; j < needle.length(); j++) {
          chain_.erase(begin() + (starting_pos + chain.length()));
        }
        break;
      };

      i++;
    }
    if (i == 0) starting_pos++;
  }

  alphabet_ = alphabet_ | chain.alphabet();
}

/**
 * @brief Operator to concatenate two chains.
 */
Chain operator*(const Chain& chain_1, const Chain& chain_2) {
  return Chain(chain_1.to_string() + chain_2.to_string());
}

/**
 * @brief Operator to compare if two chains are equal.
 */
bool operator==(const Chain& chain_1, const Chain& chain_2) {
  return chain_1.to_string() == chain_2.to_string();
}

/**
 * @brief Operator to compare if two chains are not equal.
 */
bool operator!=(const Chain& chain_1, const Chain& chain_2) {
  return !(chain_1 == chain_2);
}

/**
 * @brief Operator to compare if the first chain is subchain of the second.
 */
bool operator<(const Chain& chain_1, const Chain& chain_2) {
  return chain_1.to_string() < chain_2.to_string();
}

/**
 * @brief Operator to compare if chain_1 previous in alphabetic order than
 * chain_2.
 */
bool operator>(const Chain& chain_1, const Chain& chain_2) {
  return chain_1.to_string() > chain_2.to_string();
}

/**
 * @brief Operator to compare if chain_2 previous in alphabetic order than
 * chain_1.
 */
std::ostream& operator<<(std::ostream& output_stream, const Chain& chain) {
  return output_stream << chain.to_string();
}

/**
 * @brief Operator to access individual elements of the alphabet.
 */
Symbol Chain::operator[](int index) { return chain_[index]; };

/**
 * @brief Operator to join two chains.
 */
Chain operator+(const Chain& chain_1, const Chain& chain_2) {
  return chain_1.to_string() + chain_2.to_string();
}