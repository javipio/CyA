#ifndef GRAMAR_H_
#define GRAMAR_H_
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "Alphabet.h"
#include "Chain.h"
#include "Symbol.h"

const std::string kSpace = " ";
const std::string kDelimiter = " -> ";
const std::string kDrvDelimiter = " : ";

class Grammar {
 public:
  enum Side { Left, Right, Random };

  Grammar();

  Grammar(std::ifstream definition_file);

  void proccess_derivation_file(std::ifstream derivations_file,
                                std::ofstream output_file) const;

  Chain derive(Chain chain, Symbol non_terminal = '&', int offset = 0) const;

 private:
  Alphabet alphabet_;
  Alphabet non_terminals_;
  Symbol initial_symbol_;
  std::unordered_map<Symbol, std::vector<Chain>> productions_;

  void insert_production_(Symbol id, Chain right);

  std::vector<std::string> split_(const std::string& chain,
                                  std::string separator) const;
};
#endif
