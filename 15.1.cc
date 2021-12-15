#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  /*
   * Funnily enough, I misread the statement and thought you can only move
   * right and down. Fortunately, the answer coincided in that case for the
   * first subtask but unfortunately it made me waste quite a bit of time
   * before realizing what was wrong during the second subtask.
   */

  vector<string> ss;
  for (string s; cin >> s; ss.push_back(s)) {
  }

  const int n = ss.size();
  const int m = ss[0].size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, numeric_limits<int>::max()));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      dp[i][j] = ss[i - 1][j - 1] - '0';
    }
  }

  dp[0][1] = dp[1][0] = dp[1][1] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      dp[i][j] += min(dp[i - 1][j], dp[i][j - 1]);
    }
  }

  cout << dp[n][m] << '\n';

  return 0;
}
