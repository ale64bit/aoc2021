#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  constexpr int steps = 2;
  constexpr int pad = 2 * steps;

  string src;
  cin >> src;

  vector<string> x;
  for (int i = 0; i < pad; ++i) {
    x.push_back("");
  }
  for (string s; cin >> s;) {
    x.push_back(string(pad, '.') + s + string(pad, '.'));
  }
  const int n = x.size() - pad;
  const int m = x.back().size() - 2 * pad;
  for (int i = 0; i < pad; ++i) {
    x[i].resize(m + 2 * pad);
    fill(x[i].begin(), x[i].end(), '.');
    x.push_back(string(m + 2 * pad, '.'));
  }

  vector<string> y(x.size(), string(x[0].size(), '.'));

  for (int step = 0; step < steps; ++step) {
    for (int i = 0; i < x.size(); ++i) {
      for (int j = 0; j < x[i].size(); ++j) {
        int val = 0;
        for (int di = -1; di <= 1; ++di) {
          for (int dj = -1; dj <= 1; ++dj) {
            val *= 2;
            if (0 <= i + di && i + di < x.size() && 0 <= j + dj &&
                j + dj < x[i + di].size()) {
              val += (x[i + di][j + dj] == '#');
            } else {
              val += step % 2;
            }
          }
        }
        y[i][j] = src[val];
      }
    }
    swap(x, y);
  }

  int ans = 0;
  for (const auto &s : x) {
    ans += count(s.begin(), s.end(), '#');
  }
  cout << ans << '\n';

  return 0;
}
