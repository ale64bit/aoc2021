#include <bits/stdc++.h>

using namespace std;

struct board {
  array<array<int, 5>, 5> t{0};
  array<int, 5> row{0};
  array<int, 5> col{0};

  bool draw(int x) {
    bool win = false;
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        if (t[i][j] == x) {
          t[i][j] = -1;
          row[i]++;
          col[j]++;
          win |= row[i] == 5 || col[j] == 5;
        }
      }
    }
    return win;
  }

  int score() const {
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 5; ++j) {
        if (t[i][j] != -1) {
          sum += t[i][j];
        }
      }
    }
    return sum;
  }
};

istream &operator>>(istream &in, board &b) {
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      in >> b.t[i][j];
    }
  }
  return in;
}

vector<int> parseDrawNumbers(string line) {
  stringstream in(line + ",");
  int x;
  char sep;
  vector<int> ret;
  while (in >> x >> sep) {
    ret.push_back(x);
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string line;
  getline(cin, line);
  auto drawNumbers = parseDrawNumbers(line);

  vector<board> boards;
  for (board b; cin >> b; boards.push_back(b)) {
  }

  for (int x : drawNumbers) {
    for (board &b : boards) {
      if (b.draw(x)) {
        cout << b.score() * x << '\n';
        return 0;
      }
    }
  }
  assert(false);

  return 0;
}
