#include <bits/stdc++.h>

using namespace std;

int64_t expr(int &la, const vector<int> &bits);

int64_t readInt(int &la, const vector<int> &bits, int n) {
  int64_t ret = 0;
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

int64_t op(int &la, const vector<int> &bits, int type) {
  int id = bits[la++];
  vector<int64_t> args;
  if (id == 0) {
    int totalLen = readInt(la, bits, 15);
    int cur = la;
    while (la < cur + totalLen) {
      args.push_back(expr(la, bits));
    }
  } else {
    int numPackets = readInt(la, bits, 11);
    for (int i = 0; i < numPackets; ++i) {
      args.push_back(expr(la, bits));
    }
  }
  if (type == 0) {
    return accumulate(args.begin(), args.end(), 0ll);
  } else if (type == 1) {
    return accumulate(args.begin(), args.end(), 1ll, multiplies<int64_t>());
  } else if (type == 2) {
    return *min_element(args.begin(), args.end());
  } else if (type == 3) {
    return *max_element(args.begin(), args.end());
  } else if (type == 5) {
    return args[0] > args[1];
  } else if (type == 6) {
    return args[0] < args[1];
  } else if (type == 7) {
    return args[0] == args[1];
  }
  return 0;
}

int64_t expr(int &la, const vector<int> &bits) {
  int version = readInt(la, bits, 3);
  int type = readInt(la, bits, 3);
  return type == 4 ? lit(la, bits) : op(la, bits, type);
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
  cout << expr(la, bits) << '\n';

  return 0;
}
