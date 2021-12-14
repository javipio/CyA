#include <algorithm>
#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

#include "Item.h"

class KP {
 public:
  KP(float max_weight, std::ifstream& input_file);

  /**
   * @brief Solves the loaded problem in a bounded context.
   * @return A tuple containing the total revenue and weight.
   *         Structure: [revenue, weight]
   */
  std::tuple<float, float> SolveBounded() const;

  /**
   * @brief Solves the loaded problem in a unbounded context.
   * @return A tuple containing the total revenue and weight.
   *         Structure: [revenue, weight]
   */
  std::tuple<float, float> SolveUnBounded() const;

 private:
  template <typename T, typename K>
  using pair_vector = std::vector<std::pair<T, K>>;

  float max_weight_;
  std::vector<Item> items_;

  /**
   *
   */
  std::vector<std::string> Split(const std::string& chain,
                                 std::string seperator) const;

  /**
   *
   */
  void PrintOutput(float revenue, float weight,
                   pair_vector<int, float> steps) const;
};
