#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<int> x{0};
  for (int i; cin >> i; x.emplace_back(i)) {
  }
  partial_sum(x.begin(), x.end(), x.begin());

  int ans = 0;
  for (size_t i = 4; i < x.size(); ++i) {
    ans += (x[i] - x[i - 3]) > (x[i - 1] - x[i - 4]);
  }
  cout << ans << '\n';

  return 0;
}
