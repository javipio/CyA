/**
 * @author Javier Padilla Pío
 * @date 29/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 5 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Dfa.cc file: Dfa class contains all the logic to execute a DFA given a formal
 *              definition file and a chain.
 *              This file contains the interface of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/21198/mod_assign/introattachment/0/CyA_2021_2022_P06_DFA_Simulacion.pdf?forcedownload=1
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
const char kBreakLine = '\n';
const char kSpace = ' ';
const char kIsFinalIdentifier = '1';
const Chain kAccepted(": Accepted");
const Chain kDenied(": Denied");

class Dfa {
 public:
  Dfa();
  Dfa(std::istream& input_file);

  /**
   * @brief Runs the DFA on a given chain.
   */
  bool run(Chain chain);

 private:
  typedef std::pair<std::string, std::string> TransitionPair;
  typedef std::pair<std::string, State> StatePair;

  Alphabet alphabet_;
  std::string initial_state_id_;
  std::unordered_map<std::string, State> states_;
  std::set<std::string> final_states_;
  std::unordered_map<std::string, std::string> transitions_;

  /**
   * @brief Given a state and an entry, it will return it's next state.
   * @param[in] actual_state Current state which will transit.
   * @param[in] entry Current symbol of the chain.
   */
  const State& transit_state_(State actual_state, Symbol entry) const;
};
#endif
