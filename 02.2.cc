#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int64_t pos = 0;
  int64_t aim = 0;
  int64_t depth = 0;

  string cmd;
  int arg;
  while (cin >> cmd >> arg) {
    if (cmd == "forward") {
      pos += arg;
      depth += aim * arg;
    } else if (cmd == "down") {
      aim += arg;
    } else if (cmd == "up") {
      aim -= arg;
    }
  }
  cout << pos * depth << '\n';

  return 0;
}
