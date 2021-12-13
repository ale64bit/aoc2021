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
          set<pt> nxs;
          auto it = xs.lower_bound({coord, 0});
          while (it != xs.end()) {
            const auto [x, y] = *it;
            const auto nx = coord - (x - coord);
            nxs.emplace(nx, y);
            ys.erase({y, x});
            ys.emplace(y, nx);
            it = xs.erase(it);
          }
          xs.merge(nxs);
        } else if (axis == 'y') {
          set<pt> nys;
          auto it = ys.lower_bound({coord, 0});
          while (it != ys.end()) {
            const auto [y, x] = *it;
            const auto ny = coord - (y - coord);
            nys.emplace(ny, x);
            xs.erase({x, y});
            xs.emplace(x, ny);
            it = ys.erase(it);
          }
          ys.merge(nys);
        }
        break;
      }
    }
  }
  assert(xs.size() == ys.size());
  cout << xs.size() << '\n';

  return 0;
}
