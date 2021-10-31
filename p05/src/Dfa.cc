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

Dfa::Dfa(std::ifstream& input_file) { read(input_file); };

void Dfa::reset_() {
  states_.clear();
  transitions_.clear();
  subsequences_.clear();
  alphabet_ = Alphabet();
}

void Dfa::read(std::ifstream& input_file) {
  if (states_.size() != 0) reset_();

  std::string line;
  std::set<State> states;
  std::set<std::string> acceptance_states_ids;

  // Load the alphabet.
  while (getline(input_file, line) && line.length()) {
    alphabet_.insert(Symbol(line));
  }

  // Load the initial state
  getline(input_file, line);
  initial_state_ = State(line, false);

  // Skips the line after the initial state definition.
  getline(input_file, line);

  // Reads all the transitions.
  while (getline(input_file, line) && line.length()) {
    acceptance_states_ids.insert(line);
  }

  while (getline(input_file, line)) {
    std::string id;
    std::string future_id;
    std::string entry;

    bool reading_id = true;
    bool reading_entry = false;
    bool reading_future_id = false;

    for (const char& character : line) {
      switch (character) {
        case kComma:
          reading_id = false;
          reading_entry = true;
          continue;
        case kColon:
          reading_entry = false;
          reading_future_id = true;
          continue;
      }

      if (reading_entry) entry += character;
      if (reading_id) id += character;
      if (reading_future_id) future_id += character;
    }

    if (!alphabet_.symbol_exists(Symbol(entry))) {
      throw std::invalid_argument(
          "Se encontró un símbolo que no está contenido en el abecedario.");
    }

    if (future_id.length() && id.length()) {
      bool future_acceptance =
          acceptance_states_ids.find(future_id) != acceptance_states_ids.end();
      bool actual_acceptance =
          acceptance_states_ids.find(id) != acceptance_states_ids.end();

      states.insert(State(future_id, future_acceptance));
      states.insert(State(id, actual_acceptance));
      transitions_.insert(
          std::pair<std::string, std::string>(id + entry, future_id));
    }
  }

  for (const auto& state : states) {
    states_.insert(std::pair<std::string, State>(state.id(), state));
  }
}

void Dfa::run(Chain chain) {
  if (!alphabet_.contains(chain.alphabet())) {
    throw std::invalid_argument(
        "El alfabeto de la cadena a procesar no pertenece al de la definición "
        "del DFA.");
  }

  for (int i = 0; i < chain.length(); i++) {
    State actual_state = initial_state_;
    State prev_state = initial_state_;
    int starting_position;

    int j = i;
    while (j < chain.length()) {
      actual_state = transit_state_(actual_state, chain[j]);

      if (prev_state != actual_state && prev_state == initial_state_) {
        starting_position = j;
      }

      if (actual_state.acceptance()) {
        subsequences_.insert(
            chain.substr(starting_position, j - starting_position + 1));
      }

      j++;
      prev_state = actual_state;
    }
  }
}

const State& Dfa::transit_state_(State actual_state, Symbol entry) const {
  return states_.at(transitions_.at(actual_state.id() + entry.to_string()));
};

std::string Dfa::dump() const {
  std::string output;

  for (const auto chain : subsequences_) {
    output += chain.to_string() + kBreakLine;
  }

  return output;
}
