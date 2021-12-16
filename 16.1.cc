#include <bits/stdc++.h>

using namespace std;

int ans = 0;

void expr(int &la, const vector<int> &bits);

int readInt(int &la, const vector<int> &bits, int n) {
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    ret = ret * 2 + bits[la];
    ++la;
  }
  return ret;
}

int64_t lit(int &la, const vector<int> &bits) {
  int64_t val = 0;
  while (la + 4 < bits.size()) {
    bool last = bits[la] == 0;
    ++la;
    val = (val << 4) | readInt(la, bits, 4);
    if (last) {
      break;
    }
  }
  return val;
}

void op(int &la, const vector<int> &bits) {
  int id = bits[la++];
  if (id == 0) {
    int totalLen = readInt(la, bits, 15);
    int cur = la;
    while (la < cur + totalLen) {
      expr(la, bits);
    }
  } else {
    int numPackets = readInt(la, bits, 11);
    for (int i = 0; i < numPackets; ++i) {
      expr(la, bits);
    }
  }
}

void expr(int &la, const vector<int> &bits) {
  int version = readInt(la, bits, 3);
  int type = readInt(la, bits, 3);
  if (type == 4) {
    auto val = lit(la, bits);
  } else {
    op(la, bits);
  }
  ans += version;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string s;
  cin >> s;

  vector<int> bits;
  for (size_t i = 0; i < s.size(); i += 2) {
    int val;
    stringstream ss(s.substr(i, 2));
    ss >> hex >> val;
    for (int i = 7; i >= 0; --i) {
      bits.push_back((val & (1 << i)) != 0);
    }
  }

  int la = 0;
  expr(la, bits);
  cout << ans << '\n';

  return 0;
}
