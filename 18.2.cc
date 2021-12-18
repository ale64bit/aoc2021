#include <bits/stdc++.h>

using namespace std;

struct node {
  int64_t val;
  unique_ptr<node> l, r;

  node(int64_t val) : val(val) {}
  node(unique_ptr<node> l, unique_ptr<node> r) : l(move(l)), r(move(r)) {}

  unique_ptr<node> copy() const {
    if (leaf())
      return make_unique<node>(val);
    else
      return make_unique<node>(l->copy(), r->copy());
  }

  bool leaf() const { return !l && !r; }

  void print() {
    if (leaf()) {
      cout << val;
    } else {
      cout << "[";
      l->print();
      cout << ",";
      r->print();
      cout << "]";
    }
  }

  void explodeOne(int depth, bool &exploded, int64_t *&leftValue,
                  int64_t &carry) {
    if (leaf()) {
      if (!exploded)
        leftValue = &val;
      if (exploded && carry) {
        val += carry;
        carry = 0;
      }
      return;
    }

    if (!exploded && depth == 4) {
      if (leftValue)
        *leftValue += l->val;
      carry = r->val;
      l.reset();
      r.reset();
      val = 0;
      exploded = true;
      return;
    }

    l->explodeOne(depth + 1, exploded, leftValue, carry);
    r->explodeOne(depth + 1, exploded, leftValue, carry);
  }

  bool tryExplode() {
    bool exploded = false;
    int64_t *leftValue = nullptr;
    int64_t carry = 0;
    explodeOne(0, exploded, leftValue, carry);
    return exploded;
  }

  bool trySplit() {
    if (leaf()) {
      if (val >= 10) {
        l = make_unique<node>(val / 2);
        r = make_unique<node>((val + 1) / 2);
        val = 0;
        return true;
      } else {
        return false;
      }
    } else {
      return l->trySplit() || r->trySplit();
    }
  }

  void reduce() {
    while (tryExplode() || trySplit()) {
    }
  }

  int64_t magnitude() {
    if (leaf())
      return val;

    return 3 * l->magnitude() + 2 * r->magnitude();
  }

  static unique_ptr<node> parseOne(const string &s, size_t &i) {
    if (s[i] == '[') {
      ++i;
      auto l = parseOne(s, i);
      ++i;
      auto r = parseOne(s, i);
      ++i;
      return make_unique<node>(move(l), move(r));
    } else {
      int64_t val = 0;
      while ('0' <= s[i] && s[i] <= '9') {
        val = val * 10 + (s[i] - '0');
        ++i;
      }
      return make_unique<node>(val);
    }
  }

  static unique_ptr<node> parse(const string &s) {
    size_t i = 0;
    return parseOne(s, i);
  }
};

unique_ptr<node> operator+(unique_ptr<node> a, unique_ptr<node> b) {
  return make_unique<node>(move(a), move(b));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<unique_ptr<node>> x;
  for (string s; cin >> s;) {
    x.emplace_back(node::parse(s));
  }
  int64_t ans = 0;
  for (const auto &xi : x) {
    for (const auto &xj : x) {
      auto sum = xi->copy() + xj->copy();
      sum->reduce();
      ans = max(ans, sum->magnitude());
    }
  }
  cout << ans << '\n';

  return 0;
}
