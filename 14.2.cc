#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string p;
  cin >> p;
  map<pair<char, char>, char> subs;
  for (string line; getline(cin, line);) {
    if (!line.empty()) {
      stringstream in(line);
      char c0, c1, c2;
      string sep;
      in >> c0 >> c1 >> sep >> c2;
      subs[make_pair(c0, c1)] = c2;
    }
  }

  map<tuple<char, char, int>, array<int64_t, 26>> dp;
  function<array<int64_t, 26>(char, char, int)> Count = [&](char l, char r,
                                                            int depth) {
    auto it = dp.find(make_tuple(l, r, depth));
    if (it != dp.end()) {
      return it->second;
    }

    array<int64_t, 26> res{};
    if (depth == 0 || !subs.count(make_pair(l, r))) {
      return res;
    }

    char mid = subs.at(make_pair(l, r));
    ++res[mid - 'A'];
    auto ll = Count(l, mid, depth - 1);
    auto rr = Count(mid, r, depth - 1);
    for (int i = 0; i < 26; ++i) {
      res[i] += ll[i];
      res[i] += rr[i];
    }

    dp[make_tuple(l, r, depth)] = res;
    return res;
  };

  constexpr int kSteps = 40;
  array<int64_t, 26> res{};
  ++res[p[0] - 'A'];
  for (size_t i = 1; i < p.size(); ++i) {
    ++res[p[i] - 'A'];
    auto tmp = Count(p[i - 1], p[i], kSteps);
    for (int i = 0; i < 26; ++i) {
      res[i] += tmp[i];
    }
  }
  int64_t mn = numeric_limits<int64_t>::max();
  for (int i = 0; i < 26; ++i) {
    if (res[i] > 0) {
      mn = min(mn, res[i]);
    }
  }
  int64_t ans = *max_element(res.begin(), res.end()) - mn;
  cout << ans << '\n';

  return 0;
}
