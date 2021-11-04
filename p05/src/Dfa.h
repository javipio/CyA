/**
 * @author Javier Padilla Pío
 * @date 29/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Dfa.cc file: Dfa class contains all the logic to execute a DFA given a formal
 *              definition file and a chain.
 *              This file contains the interface of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/20878/mod_assign/introattachment/0/CyA_2021_2022_P05_DFAsPatrones.pdf?forcedownload=1
 * Revision history:
 *                29/10/2021 - Creation (first version) of the code
 */

#include <fstream>
#include <set>
#include <unordered_map>
#include <vector>

#include "Chain.h"
#include "State.h"

#ifndef NFA_H_
#define NFA_H_
const char kComma = ',';
const char kColon = ':';
const char kBreakLine = '\n';
const Chain kAccepted(": Accepted");
const Chain kDenied(": Denied");

class Dfa {
 public:
  Dfa();
  Dfa(std::ifstream& input_file);

  /**
   * @brief Reads formal definition froma stream.
   */
  void read(std::ifstream& input_file);

  /**
   * @brief Runs the DFA and stores the output on subsequences_.
   */
  void subsequences(Chain chain);

  /**
   * @brief Returns all the occurences after runing the DFA.
   */
  std::string dump() const;

 private:
  Alphabet alphabet_;
  State initial_state_;
  std::unordered_map<std::string, State> states_;
  std::set<std::string> final_states_;
  std::unordered_map<std::string, std::string> transitions_;
  std::set<Chain> subsequences_;

  /**
   * @brief Given a state and an entry, it will return it's next state.
   * @param[in] actual_state Current state which will transit.
   * @param[in] entry Current symbol of the chain.
   */
  const State& transit_state_(State actual_state, Symbol entry) const;

  /**
   * @brief Cleans all data structures inside the DFA.
   */
  void reset_();
};
#endif
