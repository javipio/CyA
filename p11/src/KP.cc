#include "KP.h"

KP::KP(float max_weight, std::ifstream& input_file) : max_weight_(max_weight) {
  std::string line;
  getline(input_file, line);
  int i = 1;
  while (getline(input_file, line)) {
    auto splited_line = Split(line, " ");
    items_.push_back(
        Item(std::stoi(splited_line[0]), std::stoi(splited_line[1]), i++));
  }

  auto custom_sort = [](const Item lhs, const Item rhs) { return lhs > rhs; };

  std::sort(items_.begin(), items_.end(), custom_sort);
}

std::tuple<float, float> KP::SolveBounded() const {
  pair_vector<int, float> steps;
  float current_weight = 0;
  float revenue = 0;

  for (int i = 0; i < items_.size() && current_weight < max_weight_; i++) {
    float factor = 1;
    if (current_weight + items_[i].weight() > max_weight_) {
      factor = (float)(max_weight_ - current_weight) / items_[i].weight();
    }
    current_weight += items_[i].weight() * factor;
    revenue += items_[i].value() * factor;
    steps.push_back(std::make_pair(items_[i].index(), factor));
  }

  PrintOutput(revenue, current_weight, steps);

  return std::make_tuple(revenue, current_weight);
};

std::tuple<float, float> KP::SolveUnBounded() const {
  pair_vector<int, float> steps;
  float current_weight = 0;
  float revenue = 0;
  int i = 0;

  while (current_weight < max_weight_ && i < items_.size()) {
    if (items_[i].weight() + current_weight <= max_weight_) {
      current_weight += items_[i].weight();
      revenue += items_[i].value();

      if (steps.size() && steps[steps.size() - 1].first == items_[i].index()) {
        steps[steps.size() - 1].second++;
      } else {
        steps.push_back(std::make_pair(items_[i].index(), 1));
      }
    } else {
      i++;
    }
  }

  PrintOutput(revenue, current_weight, steps);

  return std::make_tuple(revenue, current_weight);
}

std::vector<std::string> KP::Split(const std::string& chain,
                                   std::string seperator) const {
  std::vector<std::string> output;
  size_t prev_pos = 0, pos = 0;

  while ((pos = chain.find(seperator, pos)) != std::string::npos) {
    std::string substring(chain.substr(prev_pos, pos - prev_pos));
    output.push_back(substring);
    pos += seperator.length();
    prev_pos = pos;
  }

  output.push_back(chain.substr(prev_pos, pos - prev_pos));  // Last word

  return output;
}

void KP::PrintOutput(float revenue, float weight,
                     pair_vector<int, float> steps) const {
  std::cout << "Beneficio: " << revenue << std::endl;
  std::cout << "Peso: " << weight << std::endl;
  std::cout << "Solución: ";

  for (int i = 0, size = steps.size(); i < size; i++) {
    std::cout << steps[i].first << ":" << steps[i].second;

    if (i < size - 1) {
      std::cout << ", ";
    }
  }

  std::cout << std::endl;
}
