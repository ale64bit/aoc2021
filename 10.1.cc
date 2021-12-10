#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  const map<char, char> kBracket = {
      {'(', ')'},
      {'[', ']'},
      {'{', '}'},
      {'<', '>'},
  };
  const map<char, int> kScore = {
      {')', 3},
      {']', 57},
      {'}', 1197},
      {'>', 25137},
  };

  int ans = 0;
  for (string s; cin >> s;) {
    stack<char> stk;
    bool corrupted = false;
    for (char c : s) {
      if (kBracket.count(c)) {
        stk.push(c);
      } else {
        if (kBracket.at(stk.top()) != c) {
          corrupted = true;
          ans += kScore.at(c);
          break;
        }
        stk.pop();
      }
    }
  }
  cout << ans << '\n';

  return 0;
}
