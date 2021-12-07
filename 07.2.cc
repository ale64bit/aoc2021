#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<int> x;
  {
    string line;
    getline(cin, line);
    stringstream in(line + ",");
    int xi;
    char sep;
    while (in >> xi >> sep) {
      x.push_back(xi);
    }
  }

  int64_t ans = numeric_limits<int64_t>::max();
  for (int med = *min_element(x.begin(), x.end());
       med <= *max_element(x.begin(), x.end()); ++med) {
    int64_t cost = 0;
    for (int xi : x) {
      int64_t n = abs(xi - med);
      cost += n * (n + 1) / 2;
    }
    ans = min(ans, cost);
  }
  cout << ans << '\n';

  return 0;
}
