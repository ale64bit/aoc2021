#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int64_t pos = 0;
  int64_t depth = 0;

  string cmd;
  int arg;
  while (cin >> cmd >> arg) {
    if (cmd == "forward") {
      pos += arg;
    } else if (cmd == "down") {
      depth += arg;
    } else if (cmd == "up") {
      depth -= arg;
    }
  }
  cout << pos * depth << '\n';

  return 0;
}
