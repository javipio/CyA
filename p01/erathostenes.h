#include <vector>

struct item {
    int value;
    bool is_prime;
};

class Erathostenes {
 public:
  Erathostenes(const int limit);
  void Sieve();
  void Clean();
  void Info();

 private:
  void remove(const int start);
  std::vector<item> _numbers;
  int _limit;
};
