class Item {
 public:
  Item(float weight, float value, int index);

  int index() const;
  float value() const;
  float weight() const;

 private:
  int index_;
  float value_;
  float weight_;
};

bool operator>(const Item& lhs, const Item& rhs);
