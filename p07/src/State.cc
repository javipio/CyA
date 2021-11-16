#include "State.h"

State::State() = default;

State::State(std::string id, bool final) : id_(id), final_(final){};

std::vector<std::string> State::next(Symbol entry) const {
  if (next_states_.find(entry) != next_states_.end())
    return next_states_.at(entry);

  return {};
}

std::string State::id() const { return id_; }

bool State::final() const { return final_; }

bool operator<(const State& state_1, const State& state_2) {
  return state_1.id() < state_2.id();
}

bool operator>(const State& state_1, const State& state_2) {
  return state_1.id() > state_2.id();
}

bool operator==(const State& state_1, const State& state_2) {
  return state_1.id() == state_2.id();
}

bool operator!=(const State& state_1, const State& state_2) {
  return state_1.id() != state_2.id();
}

void State::insert_transition(Symbol entry, std::string next_state_id) {
  if (next_states_.find(entry) == next_states_.end()) {
    next_states_.insert(std::pair<Symbol, std::vector<std::string>>(
        entry, std::vector<std::string>()));
  }

  next_states_[entry].push_back(next_state_id);
}
