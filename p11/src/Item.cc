#include "Item.h"

Item::Item(float weight, float value, int index) : value_(value), weight_(weight), index_(index) {}

int Item::index() const { return index_; }

float Item::value() const { return value_; }

float Item::weight() const { return weight_; }

bool operator>(const Item& lhs, const Item& rhs) {
  if ((lhs.value() / lhs.weight()) == (rhs.value() / rhs.weight())) {
    return lhs.weight() < rhs.weight();
  }
  return (lhs.value() / lhs.weight()) > (rhs.value() / rhs.weight());
};
