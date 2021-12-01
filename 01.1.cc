#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int ans = 0;
  int prev;
  cin >> prev;
  for (int i; cin >> i; prev = i) {
    ans += prev < i;
  }
  cout << ans << '\n';

  return 0;
}
