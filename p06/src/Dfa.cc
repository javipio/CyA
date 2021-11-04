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
 *              This file contains the implementation of the class.
 * References:
 *                Practice statement:
 *                https://campusingenieriaytecnologia2122.ull.es/pluginfile.php/20878/mod_assign/introattachment/0/CyA_2021_2022_P05_DFAsPatrones.pdf?forcedownload=1
 * Revision history:
 *                29/10/2021 - Creation (first version) of the code
 */

#include "Dfa.h"

Dfa::Dfa() = default;

Dfa::Dfa(std::istream& input_file) { read(input_file); };

void Dfa::reset_() {
  states_.clear();
  transitions_.clear();
  alphabet_ = Alphabet();
}

void Dfa::read(std::istream& input_file) {
  std::string line;
  getline(input_file, line);
  int cardinality = std::stoi(line);

  getline(input_file, line);
  initial_state_id_ = line;

  int i = 0;
  while (getline(input_file, line) && i < cardinality) {
    std::string id;
    std::string raw_entry;
    std::string future_id;

    int transitions = 0;
    bool reading_entry = true;
    bool reading_id = true;
    bool reading_transitions_n = false;
    bool reading_transitions = false;
    int j = 0;

    for (const char character : line) {
      if (reading_id) {
        if (character == kSpace) {
          states_.insert(StatePair(id, State(id)));
          reading_id = false;
          reading_transitions_n = false;
        } else {
          id += character;
        }
      } else if (!reading_id && !reading_transitions_n &&
                 !reading_transitions) {
        if (character == kSpace) {
          reading_transitions_n = true;
        }

        if (character == '1') {
          final_states_.insert(id);
        }
      } else if (reading_transitions_n) {
        if (character == kSpace) {
          reading_transitions_n = false;
          reading_transitions = true;
        } else {
          transitions += character - '0';
        }
      } else {
        if (character != kSpace) {
          if (reading_entry) {
            raw_entry += character;
          } else {
            future_id += character;
          }
        }

        if (character == kSpace || j == line.length() - 1) {
          if (!reading_entry) {
            // std::cout << id + raw_entry << " -> " << future_id << std::endl;
            transitions_.insert(TransitionPair(id + raw_entry, future_id));
            states_.insert(StatePair(future_id, State(future_id)));
            alphabet_.insert(raw_entry);

            raw_entry = "";
            future_id = "";
            transitions--;
          }
          reading_entry = !reading_entry;
        }
      }
      j++;
    }

    i++;
  }

  if (getline(input_file, line) || i + 1 < cardinality) {
    std::cout << line << std::endl;
    throw std::invalid_argument(
        "Parsing error, the sintax of the .dfa file is not correct.");
  }
}

bool Dfa::run(Chain chain) {
  if (!alphabet_.contains(chain.alphabet())) {
    throw std::invalid_argument(
        "El alfabeto de la cadena a procesar no pertenece al de la definición "
        "del DFA.");
  }

  State actual_state = states_[initial_state_id_];
  State prev_state = states_[initial_state_id_];
  int starting_position;

  int j = 0;
  while (j < chain.length()) {
    actual_state = transit_state_(actual_state, chain[j]);

    if (prev_state != actual_state && prev_state == initial_state_id_) {
      starting_position = j;
    }

    if (final_states_.find(actual_state.id()) != final_states_.end()) {
      return true;
    }

    j++;
    prev_state = actual_state;
  }

  return false;
}

const State& Dfa::transit_state_(State actual_state, Symbol entry) const {
  return states_.at(transitions_.at(actual_state.id() + entry.to_string()));
};
