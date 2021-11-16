/**
 * @author Javier Padilla Pío
 * @date 29/10/2021
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
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/21198/mod_assign/introattachment/0/CyA_2021_2022_P06_DFA_Simulacion.pdf?forcedownload=1
 * Revision history:
 *                29/10/2021 - Creation (first version) of the code
 */

#include <iostream>
#include <unordered_map>
#include <vector>

#include "Symbol.h"

#ifndef STATE_H_
#define STATE_H_
class State {
 public:
  State();
  State(std::string id, bool final);

  /**
   * @brief Simple getter
   * @return Returns the id of the state.
   */
  std::string id() const;

  /**
   * @brief Simple getter
   * @return Returns if is final.
   */
  bool final() const;

  /**
   * @brief Retrieves all the possible future states given an entry.
   * @param[in] entry Symbol to transit.
   * @return The retrived states.
   */
  std::vector<std::string> next(Symbol entry) const;

  /**
   * @brief Appends a transition to the state.
   * @param[in] entry The entry to transit.
   * @param[in] next_state_id State to which will transit.
   */
  void insert_transition(Symbol entry, std::string next_state_id);

 private:
  std::string id_;
  bool final_;
  std::unordered_map<Symbol, std::vector<std::string>> next_states_;
};

/**
 * @brief Operator to compare if state_1 previous in alphabetic order than
 * state_2.
 */
bool operator<(const State& state_1, const State& state_2);

/**
 * @brief Operator to compare if state_1 previous in alphabetic order than
 * state_2.
 */
bool operator>(const State& state_1, const State& state_2);

/**
 * @brief Operator to compare if state_1 is equal to state_2.
 */
bool operator==(const State& state_1, const State& state_2);

/**
 * @brief Operator to compare if state_1 is not equal to state_2.
 */
bool operator!=(const State& state_1, const State& state_2);

#endif
