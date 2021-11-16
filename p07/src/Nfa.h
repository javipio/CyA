#include <fstream>
#include <iostream>
#include <unordered_map>

#include "Alphabet.h"
#include "Chain.h"
#include "State.h"

#ifndef NFA_H_
#define NFA_H_
const char kBreakLine = '\n';
const char kSpace = ' ';
const char kIsFinalIdentifier = '1';
const std::string kInitialAlias = "INITIAL";
class Nfa {
 public:
  Nfa();
  Nfa(std::ifstream& input_file);

  /**
   * @brief Executes the NFA over the given chain.
   * @param[in] chain Sequence of symbols to run de algorithm over.
   * @param[in] actual_state_id State in which to start running the algorithm.
   */
  bool run(Chain chain, std::string actual_state_id = kInitialAlias) const;

 private:
  typedef std::pair<std::string, State> StatePair;

  std::unordered_map<std::string, State> states_;
  Alphabet alphabet_;
  std::string initial_state_id_;
};
#endif
