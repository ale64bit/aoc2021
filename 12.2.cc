#include <bits/stdc++.h>

using namespace std;

bool IsSmall(string u) {
  return all_of(u.begin(), u.end(), [](unsigned char c) { return islower(c); });
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  map<string, vector<string>> adj;
  for (string line; getline(cin, line);) {
    auto pos = line.find('-');
    string u = line.substr(0, pos);
    string v = line.substr(pos + 1, line.size() - pos);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  map<string, int> used;
  bool twice = false;

  function<int(string)> Dfs = [&](string u) {
    if (u == "end")
      return 1;
    int ret = 0;
    ++used[u];
    for (auto v : adj[u]) {
      if (!IsSmall(v) || used[v] < 1) {
        ret += Dfs(v);
      } else if (!twice && used[v] < 2) {
        twice = true;
        ret += Dfs(v);
        twice = false;
      }
    }
    --used[u];
    return ret;
  };

  used["start"] = 1;
  int ans = Dfs("start");
  cout << ans << '\n';

  return 0;
}
