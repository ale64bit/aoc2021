#include <bits/stdc++.h>

using namespace std;

const map<string, int> kMapping = {
    {"abcefg", 0}, {"cf", 1},     {"acdeg", 2}, {"acdfg", 3},   {"bcdf", 4},
    {"abdfg", 5},  {"abdefg", 6}, {"acf", 7},   {"abcdefg", 8}, {"abcdfg", 9},
};

pair<bool, map<string, int>> valid(const array<string, 10> &x,
                                   const array<int, 7> &p) {
  map<string, int> ret;
  for (const auto &[mask, d] : kMapping) {
    string s = mask;
    for (char &c : s) {
      c = p[c - 'a'] + 'a';
    }
    for (const auto &xi : x) {
      if (set(xi.begin(), xi.end()) == set(s.begin(), s.end())) {
        string si = xi;
        sort(si.begin(), si.end());
        ret[si] = d;
        break;
      }
    }
  }
  return {ret.size() == 10, ret};
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int ans = 0;
  for (string line; getline(cin, line);) {
    stringstream in(line);

    array<string, 10> d;
    for (auto &di : d) {
      in >> di;
    }
    char sep;
    in >> sep;

    map<string, int> mapping;
    array<int, 7> p;
    iota(p.begin(), p.end(), 0);
    do {
      if (auto [ok, m] = valid(d, p); ok) {
        mapping = m;
        break;
      }
    } while (next_permutation(p.begin(), p.end()));

    assert(!mapping.empty());

    int x = 0;
    array<string, 4> out;
    for (auto &outi : out) {
      in >> outi;
      sort(outi.begin(), outi.end());
      assert(mapping.count(outi));
      x = x * 10 + mapping[outi];
    }
    ans += x;
  }
  cout << ans << '\n';

  return 0;
}
