#include <bits/stdc++.h>

using namespace std;

string filter(vector<string> x, function<bool(int, int)> cmp) {
  const int n = x[0].size();
  for (int i = 0; i < n; ++i) {
    array<int, 2> count{0, 0};
    for (const auto &s : x) {
      ++count[s[i] - '0'];
    }
    auto keep = '0' + cmp(count[0], count[1]);
    for (size_t j = 0; j < x.size();) {
      if (x[j][i] != keep) {
        swap(x[j], x.back());
        x.pop_back();
        if (x.size() == 1)
          return x[0];
      } else {
        ++j;
      }
    }
  }
  assert(false);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<string> x;
  for (string s; cin >> s; x.push_back(s)) {
  }

  const string a = filter(x, [](int a, int b) { return b >= a; });
  const string b = filter(x, [](int a, int b) { return b < a; });
  cout << stoll(a, nullptr, 2) * stoll(b, nullptr, 2) << '\n';

  return 0;
}
