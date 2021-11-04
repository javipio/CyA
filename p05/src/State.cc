#include "State.h"

State::State() = default;

State::State(std::string id) : id_(id){};

std::string State::id() const { return id_; }

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