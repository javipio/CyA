#include "State.h"

State::State() = default;

State::State(std::string id, bool acceptance)
    : id_(id), acceptance_(acceptance){};

bool State::acceptance() const { return acceptance_; }

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