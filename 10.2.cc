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
      {'(', 1},
      {'[', 2},
      {'{', 3},
      {'<', 4},
  };

  vector<int64_t> scores;
  for (string s; cin >> s;) {
    stack<char> stk;
    bool corrupted = false;
    for (char c : s) {
      if (kBracket.count(c)) {
        stk.push(c);
      } else {
        if (kBracket.at(stk.top()) != c) {
          corrupted = true;
          break;
        }
        stk.pop();
      }
    }
    if (!corrupted) {
      int64_t score = 0;
      while (!stk.empty()) {
        score = score * 5 + kScore.at(stk.top());
        stk.pop();
      }
      scores.push_back(score);
    }
  }
  sort(scores.begin(), scores.end());
  cout << scores[scores.size() / 2] << '\n';

  return 0;
}
