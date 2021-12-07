#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<int64_t> x;
  {
    string line;
    getline(cin, line);
    stringstream in(line + ",");
    int64_t xi;
    char sep;
    while (in >> xi >> sep) {
      x.push_back(xi);
    }
  }

  sort(x.begin(), x.end());
  int64_t med = x[x.size() / 2];
  int64_t ans = 0;
  for (int64_t xi : x) {
    ans += abs(xi - med);
  }
  cout << ans << '\n';

  return 0;
}
