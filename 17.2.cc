#include <bits/stdc++.h>

using namespace std;

bool within(int x, int y, int x1, int y1, int x2, int y2) {
  return x1 <= x && x <= x2 && y1 <= y && y <= y2;
}

int main() {
  int xl, xh;
  int yl, yh;
  scanf("target area: x=%d..%d, y=%d..%d", &xl, &xh, &yl, &yh);

  const int steps = 4 * max(xh, abs(yl)) + 1;

  int ans = 0;
  for (int vx0 = 1; vx0 <= ub; ++vx0) {
    for (int vy0 = -ub; vy0 <= ub; ++vy0) {
      int x = 0, y = 0;
      int vx = vx0, vy = vy0;
      bool ok = false;
      int maxy = 0;
      for (int step = 0; x <= xh && y >= yl; ++step) {
        x += vx;
        if (vx > 0) {
          --vx;
        } else if (vx < 0) {
          ++vx;
        }
        y += vy;
        --vy;

        maxy = max(maxy, y);
        if (within(x, y, xl, yl, xh, yh)) {
          ok = true;
        }
      }
      if (ok) {
        ++ans;
      }
    }
  }
  cout << ans << '\n';

  return 0;
}
