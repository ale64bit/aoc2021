#include <bits/stdc++.h>

using namespace std;

template <typename T, int N> struct Matrix {
  array<array<T, N>, N> m;

  Matrix() {}

  Matrix(T t) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        m[i][j] = t;
      }
    }
  }

  static Matrix unit() {
    Matrix res(0);
    for (int i = 0; i < N; ++i) {
      res(i, i) = 1;
    }
    return res;
  }

  Matrix(const Matrix &) = default;

  bool operator==(const Matrix &b) const {
    for (int i = 0; i < N; ++i) {
      if (m[i] != b.m[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Matrix &b) const { return !(*this == b); }

  Matrix &operator=(const Matrix &b) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        m[i][j] = b.m[i][j];
      }
    }
  }

  Matrix operator+(const Matrix &b) const {
    Matrix res;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        res.m[i][j] = m[i][j] + b.m[i][j];
      }
    }
    return res;
  }

  Matrix operator-(const Matrix &b) const {
    Matrix res;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        res.m[i][j] = m[i][j] - b.m[i][j];
      }
    }
    return res;
  }

  Matrix operator*(const Matrix &b) const {
    Matrix res;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        res.m[i][j] = 0;
        for (int k = 0; k < N; ++k) {
          res.m[i][j] += m[i][k] * b.m[k][j];
        }
      }
    }
    return res;
  }

  T &operator()(int i, int j) { return m[i][j]; }
  const T &operator()(int i, int j) const { return m[i][j]; }
};

using mat4 = Matrix<int, 4>;
using pt = array<int, 3>;

pt operator*(const mat4 &m, const pt &p) {
  pt ret;
  for (int i = 0; i < 3; ++i) {
    ret[i] = m(i, 3);
    for (int j = 0; j < 3; ++j) {
      ret[i] += m(i, j) * p[j];
    }
  }
  return ret;
}

mat4 Build(int mask, const array<int, 3> &p, const pt &p0, const pt &p1) {
  mat4 ret(0);
  for (int i = 0; i < 3; ++i) {
    const int sgn = (mask & (1 << i)) ? -1 : 1;
    ret(i, p[i]) = sgn;
    ret(i, 3) = p1[i] - sgn * p0[p[i]];
  }
  ret(3, 3) = 1;
  return ret;
}

mat4 HInv(mat4 m) {
  mat4 ret(0);
  for (int i = 0; i < 3; ++i) {
    ret(i, 3) = 0;
    for (int j = 0; j < 3; ++j) {
      ret(i, j) = m(j, i);
      ret(i, 3) += -m(j, i) * m(j, 3);
    }
  }
  ret(3, 3) = 1;
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  vector<vector<pt>> scanners;
  for (string hdr; getline(cin, hdr);) {
    if (hdr.substr(4, 7) == "scanner") {
      vector<pt> beacons;
      for (string line; getline(cin, line);) {
        if (line.empty())
          break;
        stringstream in(line);
        int x, y, z;
        char sep;
        if (in >> x >> sep >> y >> sep >> z) {
          beacons.push_back({x, y, z});
        }
      }
      scanners.emplace_back(move(beacons));
    }
  }

  const int n = scanners.size();
  vector<vector<pair<int, mat4>>> adj(n);
  for (int i = 0; i < (int)scanners.size(); ++i) {
    for (int j = i + 1; j < (int)scanners.size(); ++j) {
      for (int ii = 0; ii < (int)scanners[i].size(); ++ii) {
        for (int jj = 0; jj < (int)scanners[j].size(); ++jj) {
          for (int mask = 0; mask < (1 << 3); ++mask) {
            pt p{0, 1, 2};
            do {
              auto tr = Build(mask, p, scanners[i][ii], scanners[j][jj]);
              int match = 0;
              for (const pt &bj : scanners[j]) {
                for (const pt &bi : scanners[i]) {
                  if (tr * bi == bj) {
                    ++match;
                    break;
                  }
                }
              }
              if (match >= 12) {
                adj[i].push_back({j, HInv(tr)});
                adj[j].push_back({i, tr});
                break;
              }
            } while (next_permutation(p.begin(), p.end()));
          }
        }
      }
    }
  }

  int ans = 0;
  vector<bool> seen(n, false);

  function<void(int, mat4)> Dfs = [&](int u, mat4 cur) {
    ans = max(ans, abs(cur(0, 3)) + abs(cur(1, 3)) + abs(cur(2, 3)));
    seen[u] = true;
    for (const auto &[v, itr] : adj[u]) {
      if (!seen[v]) {
        Dfs(v, cur * itr);
      }
    }
  };

  for (int i = 0; i < n; ++i) {
    Dfs(i, mat4::unit());
    fill(seen.begin(), seen.end(), false);
  }

  cout << ans << '\n';

  return 0;
}
