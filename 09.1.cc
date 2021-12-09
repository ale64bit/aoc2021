#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<string> t;
  for (string s; cin >> s; t.push_back(s)) {
  }

  int ans = 0;
  const int R = t.size();
  const int C = t[0].size();
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      int cnt = 0;
      int adj = 0;
      for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
          if ((di == 0) == (dj == 0))
            continue;
          const int ii = i + di;
          const int jj = j + dj;
          if (0 <= ii && ii < R && 0 <= jj && jj < C) {
            cnt += t[i][j] < t[ii][jj];
            ++adj;
          }
        }
      }
      if (cnt == adj) {
        ans += 1 + t[i][j] - '0';
      }
    }
  }
  cout << ans << '\n';

  return 0;
}
