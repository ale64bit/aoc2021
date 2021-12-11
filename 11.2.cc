#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<string> e;
  for (string s; cin >> s; e.push_back(s)) {
  }
  const int R = e.size();
  const int C = e[0].size();

  vector<vector<int>> lastFlash(R, vector<int>(C, -1));
  int ans = 0;
  for (int step = 0;; ++step) {
    vector<pair<int, int>> q;
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        if (e[i][j] == '9') {
          q.emplace_back(i, j);
          lastFlash[i][j] = step;
        } else {
          ++e[i][j];
        }
      }
    }
    while (!q.empty()) {
      const auto [i, j] = q.back();
      q.pop_back();
      for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
          if (di || dj) {
            const int ni = i + di;
            const int nj = j + dj;
            if (0 <= ni && ni < R && 0 <= nj && nj < C) {
              if (e[ni][nj] == '9') {
                if (lastFlash[ni][nj] < step) {
                  lastFlash[ni][nj] = step;
                  q.emplace_back(ni, nj);
                }
              } else {
                ++e[ni][nj];
              }
            }
          }
        }
      }
    }
    int total = 0;
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        if (lastFlash[i][j] == step) {
          e[i][j] = '0';
          ++total;
        }
      }
    }
    if (total == R * C) {
      ans = step + 1;
      break;
    }
  }
  cout << ans << '\n';

  return 0;
}
