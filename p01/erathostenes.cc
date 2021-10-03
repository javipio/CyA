#include <iostream>
#include "erathostenes.h"

void Erathostenes::Sieve() {
  for (int i = 0; i <= _limit; i++) {
    if (_numbers[i].value == 1) {
      std::cout << _numbers[i].value << " ";
      continue;
    }

    if (_numbers[i].is_prime) {
      remove(i);
      std::cout << _numbers[i].value << " ";
    }
  }
  std::cout << std::endl;
}

void Erathostenes::remove(const int start) {
  if (_numbers[start].value >= _limit) return;
  for (int i = start + 1; i <= _limit; i++) {
    if (_numbers[i].value % _numbers[start].value == 0) {
      _numbers[i].is_prime = false;
    }
  }
}

Erathostenes::Erathostenes(const int limit) : _limit{limit} {
  _numbers.reserve(_limit);
  for (int i = 1; i <= _limit; i++) {
    _numbers.push_back(item{i, true});
  }
}

void Erathostenes::Info() {
  for (const item &element : _numbers) {
    std::cout << element.value << (element.is_prime ? " " : " no ") << "es primo." << std::endl;
  }
}

void Erathostenes::Clean() {
  std::vector<item>::iterator iter = _numbers.begin();
  while (iter != _numbers.end()) {
    if (!(*iter).is_prime) {
      iter = _numbers.erase(iter);
    } else {
      iter++;
    }
  }
}
