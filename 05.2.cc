#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n = 0;
  vector<pair<int, int>> from, to;
  {
    int x1, y1, x2, y2;
    char sep;
    while (cin >> x1 >> sep >> y1 >> sep >> sep >> x2 >> sep >> y2) {
      n = max({n, x1, y1, x2, y2});
      from.emplace_back(x1, y1);
      to.emplace_back(x2, y2);
    }
  }

  vector<vector<int>> cnt(n + 1, vector<int>(n + 1, 0));
  for (size_t i = 0; i < from.size(); ++i) {
    auto [x1, y1] = from[i];
    auto [x2, y2] = to[i];
    if (x1 == x2) {
      for (int y = min(y1, y2); y <= max(y1, y2); ++y) {
        ++cnt[y][x1];
      }
    } else if (y1 == y2) {
      for (int x = min(x1, x2); x <= max(x1, x2); ++x) {
        ++cnt[y1][x];
      }
    } else {
      assert(abs(x1 - x2) == abs(y1 - y2));
      const int dx = x2 > x1 ? 1 : -1;
      const int dy = y2 > y1 ? 1 : -1;
      for (int i = 0, x = x1, y = y1; i <= abs(x1 - x2);
           ++i, x += dx, y += dy) {
        ++cnt[y][x];
      }
    }
  }

  int ans = 0;
  for (int x = 0; x <= n; ++x) {
    for (int y = 0; y <= n; ++y) {
      ans += cnt[x][y] > 1;
    }
  }

  cout << ans << '\n';

  return 0;
}
