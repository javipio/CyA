#include "Nfa.h"

Nfa::Nfa() = default;

Nfa::Nfa(std::ifstream& input_file) {
  std::string line;
  getline(input_file, line);
  int cardinality = stoi(line);

  getline(input_file, line);
  initial_state_id_ = line;

  int i = 0;
  while (getline(input_file, line) && i < cardinality) {
    std::string id;
    std::string raw_entry;
    std::string future_id;
    bool is_final = false;
    State current_state;

    bool reading_id = true;
    bool reading_entry = true;
    bool reading_transitions_n = false;
    bool reading_transitions = false;
    int j = 0;

    for (const char character : line) {
      if (reading_id) {
        if (character == kSpace) {
          reading_id = false;
          reading_transitions_n = false;
        } else {
          id += character;
        }
      } else if (!reading_id && !reading_transitions_n &&
                 !reading_transitions) {
        if (character == kSpace) {
          reading_transitions_n = true;
          current_state = State(id, is_final);
        }

        if (character == kIsFinalIdentifier) {
          is_final = true;
        }

      } else if (reading_transitions_n) {
        if (character == kSpace) {
          reading_transitions_n = false;
          reading_transitions = true;
        }

        if (character == '0') {
          states_.insert(std::pair<std::string, State>(id, current_state));
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
            current_state.insert_transition(Symbol(raw_entry), future_id);
            alphabet_.insert(Symbol(raw_entry));

            raw_entry = "";
            future_id = "";
          }

          if (j == line.length() - 1) {
            states_.insert(std::pair<std::string, State>(id, current_state));
          }

          reading_entry = !reading_entry;
        }
      }

      j++;
    }

    i++;
  }

  if (getline(input_file, line) || i + 1 < cardinality) {
    throw std::invalid_argument(
        "Parsing error, the sintax of the .nfa file is not correct.");
  }

  if (states_.find(initial_state_id_) == states_.end()) {
    throw std::invalid_argument(
        "Parsing error, the definition of the starting node is missing.");
  }
}

bool Nfa::run(Chain chain, std::string actual_state_id) const {
  State actual_state = actual_state_id == kInitialAlias
                           ? states_.at(initial_state_id_)
                           : states_.at(actual_state_id);

  if (!chain.length()) return states_.at(actual_state.id()).final();

  for (const auto next_state : actual_state.next(chain[0])) {
    if (run(chain.substr(1, chain.length() - 1), next_state)) {
      return true;
    }
  }

  return false;
}
