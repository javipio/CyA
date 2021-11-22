#include "Grammar.h"

Grammar::Grammar() = default;

Grammar::Grammar(std::ifstream definition_file) {
  std::string line;

  getline(definition_file, line);
  alphabet_ = split_(line, kSpace);

  getline(definition_file, line);
  non_terminals_ = split_(line, kSpace);

  initial_symbol_ = split_(line, kSpace)[0];

  while (getline(definition_file, line)) {
    auto parsed_line = split_(line, kDelimiter);
    insert_production_(parsed_line[0], parsed_line[1]);
  }
}

/**
 * @brief Given a file with all the derivations, all the derivations will be
 *        processed outputing the proccess to an output_file.
 * @param[in] derivations_file File from where all derivations will be read.
 * @param[in] derivations_file File to output the proccess.
 */
void Grammar::proccess_derivation_file(std::ifstream derivations_file,
                                       std::ofstream output_file) const {
  std::string line;
  Chain chain = initial_symbol_;
  output_file << chain;

  while (getline(derivations_file, line)) {
    auto parsed_line = split_(line, kDrvDelimiter);
    chain = derive(chain, parsed_line[0], std::stoi(parsed_line[1]));
    output_file << " => " << chain;
  }
}

/**
 * @brief Derivates one step a given chain.
 * @param chain Chain to derivate.
 * @param non_terminal Symbol to replace with it's production.
 * @param offset index of the intended production.
 */
Chain Grammar::derive(Chain chain, Symbol non_terminal, int offset) const {
  if (non_terminal == Chain::kEmpty) return non_terminal;
  productions_.at(non_terminal);
  chain.replace(non_terminal, productions_.at(non_terminal)[offset - 1]);

  return chain;
}

/**
 * @brief Appends a production to the grammar.
 * @param[in] id The non-terminal symbol at the left side of the production.
 * @param[in] right The right side of the production.
 */
void Grammar::insert_production_(Symbol id, Chain right) {
  if (productions_.find(id) == productions_.end()) {
    productions_[id] = std::vector<Chain>();
  }

  productions_[id].push_back(right);
}

/**
 * @brief Splits a given string wherever the separator is found.
 * @param[in] chain String to split.
 * @param[in] separator The delimiter of of the sub-chains.
 * @return Vector with all the sub-chains.
 */
std::vector<std::string> Grammar::split_(const std::string& chain,
                                         std::string seperator) const {
  std::vector<std::string> output;
  size_t prev_pos = 0, pos = 0;

  while ((pos = chain.find(seperator, pos)) != std::string::npos) {
    std::string substring(chain.substr(prev_pos, pos - prev_pos));
    output.push_back(substring);
    pos += seperator.length();
    prev_pos = pos;
  }

  output.push_back(chain.substr(prev_pos, pos - prev_pos));  // Last word

  return output;
}
