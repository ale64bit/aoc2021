#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<vector<int>> cnt(2, vector<int>(9, 0));
  {
    string line;
    getline(cin, line);
    stringstream in(line + ",");
    int x;
    char sep;
    while (in >> x >> sep) {
      ++cnt[0][x];
    }
  }

  constexpr int kDays = 80;

  for (int d = 0; d < kDays; ++d) {
    const int now = d % 2;
    const int next = (d + 1) % 2;
    fill(cnt[next].begin(), cnt[next].end(), 0);
    cnt[next][8] += cnt[now][0];
    cnt[next][6] += cnt[now][0];
    for (int i = 1; i <= 8; ++i) {
      cnt[next][i - 1] += cnt[now][i];
    }
  }

  int ans = accumulate(cnt[kDays % 2].begin(), cnt[kDays % 2].end(), 0);
  cout << ans << '\n';

  return 0;
}
