/**
 * @author Javier Padilla Pío
 * @date 16/10/2021
 * University of La Laguna
 * Higher School of Engineering and Technology
 * Computer Ingineering Degree
 * Grade: 2nd
 * Practice 3 - Operaciones con cadenas y lenguajes.
 * Email: alu0101410463@ull.edu.es
 * Symbol.h file: Symbol class is the atomic element of a chain or alphabet.
 *                 This file contains the interface of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/19541/mod_assign/introattachment/0/CyA_2021_2022_P2_Cadenas.pdf?forcedownload=1
 * Revision history:
 *                16/10/2021 - Creation (first version) of the code
 */

#include <fstream>
#include <map>
#include <set>
#include <vector>

#include "Chain.h"
#include "State.h"

#ifndef NFA_H_
#define NFA_H_
const char kComma = ',';
const char kColon = ':';
const char kBreakLine = '\n';

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
  void run(Chain chain);

  /**
   * @brief Returns all the occurences after runing the DFA.
   */
  std::string dump() const;

 private:
  std::map<std::string, State> states_;
  std::map<std::string, std::string> transitions_;
  Alphabet alphabet_;
  State initial_state_;
  std::set<Chain> subsequences_;

  /***/
  const State& transit_state_(State actual_state, Symbol entry) const;

  /***/
  void reset_();
};
#endif
