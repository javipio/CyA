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
   * @brief Divides a string by a given character.
   * @param[in] chain String to split.
   * @param[in] separator Delimiter of the substrings.
   * @return A vector containing all subsequences.
   */
  std::vector<std::string> Split(const std::string& chain, std::string seperator) const;

  /**
   * @brief Prints some information after the execution of the algorithm.
   * @param[in] revenue The accumulated revenue.
   * @param[in] weight The accumulated weight.
   * @param[in] steps All the steps the algorithm procesed.
   */
  void PrintOutput(float revenue, float weight, pair_vector<int, float> steps) const;
};
