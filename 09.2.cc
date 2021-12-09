#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<string> t;
  for (string s; cin >> s; t.push_back(s)) {
  }
  const int R = t.size();
  const int C = t[0].size();

  vector<vector<bool>> low(R, vector<bool>(C, false));
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
      low[i][j] = cnt == adj;
    }
  }

  vector<vector<bool>> seen(R, vector<bool>(C, false));

  function<int(int, int)> Dfs = [&](int i, int j) {
    int ret = 1;
    seen[i][j] = true;
    for (int di = -1; di <= 1; ++di) {
      for (int dj = -1; dj <= 1; ++dj) {
        if ((di == 0) == (dj == 0))
          continue;
        const int ii = i + di;
        const int jj = j + dj;
        if (0 <= ii && ii < R && 0 <= jj && jj < C && !seen[ii][jj] &&
            t[i][j] < t[ii][jj] && t[ii][jj] != '9') {
          ret += Dfs(ii, jj);
        }
      }
    }
    return ret;
  };

  priority_queue<int> pq;
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (low[i][j] && !seen[i][j]) {
        int size = Dfs(i, j);
        pq.push(size);
      }
    }
  }
  int64_t ans = 1;
  for (int i = 0; i < 3; ++i) {
    ans *= pq.top();
    pq.pop();
  }
  cout << ans << '\n';

  return 0;
}
