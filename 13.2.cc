#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  using pt = pair<int, int>;

  set<pt> xs, ys;

  for (string line; getline(cin, line);) {
    if (line.empty()) {
      break;
    }
    stringstream in(line);
    int xi, yi;
    char sep;
    in >> xi >> sep >> yi;
    xs.emplace(xi, yi);
    ys.emplace(yi, xi);
  }
  for (string line; getline(cin, line);) {
    stringstream in(line);
    string w1, w2;
    if (in >> w1 >> w2) {
      if (w1 == "fold" && w2 == "along") {
        char axis, sep;
        int coord;
        in >> axis >> sep >> coord;
        if (axis == 'x') {
          auto it = xs.lower_bound({coord, 0});
          while (it != xs.end()) {
            const auto [x, y] = *it;
            const auto nx = coord - (x - coord);
            ys.erase({y, x});
            ys.emplace(y, nx);
            it = xs.erase(it);
            xs.emplace(nx, y);
          }
        } else if (axis == 'y') {
          auto it = ys.lower_bound({coord, 0});
          while (it != ys.end()) {
            const auto [y, x] = *it;
            const auto ny = coord - (y - coord);
            xs.erase({x, y});
            xs.emplace(x, ny);
            it = ys.erase(it);
            ys.emplace(ny, x);
          }
        }
      }
    }
  }
  const int X = xs.rbegin()->first;
  const int Y = ys.rbegin()->first;
  vector<string> ans(Y + 1, string(X, '.'));

  for (const auto &[x, y] : xs) {
    ans[y][x] = '#';
  }
  for (string s : ans) {
    cout << s << '\n';
  }

  return 0;
}
