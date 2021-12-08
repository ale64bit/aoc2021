#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  array<int, 10> cnt{0};
  for (string line; getline(cin, line);) {
    stringstream in(line);

    array<string, 10> d;
    for (auto &di : d) {
      in >> di;
    }
    char sep;
    in >> sep;

    array<string, 4> out;
    for (auto &outi : out) {
      in >> outi;
      switch (outi.size()) {
      case 2:
        ++cnt[1];
        break;
      case 4:
        ++cnt[4];
        break;
      case 3:
        ++cnt[7];
        break;
      case 7:
        ++cnt[8];
        break;
      }
    }
  }
  int ans = accumulate(cnt.begin(), cnt.end(), 0);
  cout << ans << '\n';

  return 0;
}
