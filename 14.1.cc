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

  constexpr int kSteps = 10;
  for (int step = 0; step < kSteps; ++step) {
    string s;
    s += p[0];
    for (size_t i = 1; i < p.size(); ++i) {
      s += subs[make_pair(p[i - 1], p[i])];
      s += p[i];
    }
    p = s;
  }
  map<char, int> cnt;
  for (char c : p) {
    ++cnt[c];
  }
  int mx = 0;
  int mn = p.size();
  for (auto [k, v] : cnt) {
    mx = max(mx, v);
    mn = min(mn, v);
  }
  int ans = mx - mn;
  cout << ans << '\n';

  return 0;
}
