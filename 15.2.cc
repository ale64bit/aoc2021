#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int inf = numeric_limits<int>::max() >> 2;

  vector<string> ss;
  for (string s; cin >> s; ss.push_back(s)) {
  }

  const int n = ss.size();
  const int m = ss[0].size();
  vector<vector<int>> cost(n + 1, vector<int>(m + 1, inf));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      cost[i][j] = ss[i - 1][j - 1] - '0';
    }
  }

  auto Cost = [&](int i, int j) {
    if (i == 1 && j == 1)
      return 0;
    int ret =
        cost[(i - 1) % n + 1][(j - 1) % m + 1] + (i - 1) / n + (j - 1) / m;
    if (ret > 9)
      ret -= 9;
    return ret;
  };

  const int nn = 5 * n;
  const int mm = 5 * m;

  vector<vector<int>> dist(nn + 1, vector<int>(mm + 1, inf));
  priority_queue<pair<int, pair<int, int>>> pq;
  pq.push({0, {1, 1}});
  dist[1][1] = 0;
  while (!pq.empty()) {
    const auto [d, coord] = pq.top();
    pq.pop();
    const auto [i, j] = coord;
    if (-d != dist[i][j])
      continue;

    for (int di = -1; di <= 1; ++di) {
      for (int dj = -1; dj <= 1; ++dj) {
        if ((di == 0) != (dj == 0)) {
          int ni = i + di;
          int nj = j + dj;
          if (1 <= ni && ni <= nn && 1 <= nj && nj <= mm) {
            if (dist[ni][nj] > dist[i][j] + Cost(ni, nj)) {
              dist[ni][nj] = dist[i][j] + Cost(ni, nj);
              pq.push({-dist[ni][nj], {ni, nj}});
            }
          }
        }
      }
    }
  }
  cout << dist[nn][mm] << '\n';

  return 0;
}
