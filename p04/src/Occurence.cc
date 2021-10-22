#include "Occurence.h"

Occurence::Occurence() = default;

Occurence::Occurence(int start_line, int end_line)
    : starting_line_(start_line), ending_line_(end_line) {}

Occurence::Occurence(int starting_line, int ending_line, Occurence::Type type,
                     std::string info)
    : starting_line_(starting_line),
      ending_line_(ending_line),
      type_(type),
      info_(info) {}

Occurence::Type Occurence::type() const { return type_; }

std::string Occurence::info() const { return info_; }

int Occurence::ending_line() const { return ending_line_; }

std::string Occurence::dump() const {
  std::string output = "[Line " + std::to_string(starting_line_);

  if (starting_line_ != ending_line_) {
    output += "-" + std::to_string(ending_line_);
  }

  output += "] " + info_;
  return output;
}

void Occurence::set_type(Occurence::Type type) { type_ = type; }

void Occurence::set_info(std::string info) { info_ = info; }
