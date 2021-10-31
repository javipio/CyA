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

#include "Symbol.h"

#ifndef STATE_H_
#define STATE_H_
class State {
 public:
  State();
  State(std::string id, bool acceptance);

  /**
   * @brief Simple getter
   * @return Returns the acceptance of the state.
   */
  bool acceptance() const;

  /**
   * @brief Simple getter
   * @return Returns the id of the state.
   */
  std::string id() const;

 private:
  bool acceptance_;
  std::string id_;
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
