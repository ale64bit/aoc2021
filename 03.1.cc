#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<string> x;
  for (string s; cin >> s; x.push_back(s)) {
  }

  const int n = x[0].size();
  string gamma(n, '0');
  string epsilon(n, '0');
  for (int i = 0; i < x[0].size(); ++i) {
    array<int, 2> count{0, 0};
    for (const auto &s : x) {
      ++count[s[i] - '0'];
    }
    gamma[i] = count[0] > count[1] ? '0' : '1';
    epsilon[i] = count[0] < count[1] ? '0' : '1';
  }

  cout << stoll(gamma, nullptr, 2) * stoll(epsilon, nullptr, 2) << '\n';

  return 0;
}
