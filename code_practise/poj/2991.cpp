#include <vector>
#include <iostream>
#include <cmath>

const double PI = acos(-1.0);

using namespace std;

vector<int> L;
vector<double> xs, ys;
vector<double> nodeAng, prevAng;

void init(int k, int l, int r)
{
    if (r - l == 1) {
        ys[k] = L[l];
    } else {
        init(2 * k + 1, l, (l + r) / 2);
        init(2 * k + 2, (l + r) / 2, r);
        ys[k] = ys[2 * k + 1] + ys[2 * k + 2];
    }
}

void update(int sIdx, int l, int r, double theta, int k) {
    if (sIdx < l) {
        return;
    } else if (sIdx + 1 < r) {
        int lch = 2 * k + 1; int rch = 2 * k + 2;
        int m = (l + r) / 2;
        update(sIdx, l, m, theta, lch);
        update(sIdx, m, r, theta, rch);
        if (sIdx < m) { // if sIdx is m, then nodeAng is not bent
            nodeAng[k] += theta;
        }
        double s = sin(nodeAng[k]);
        double c = cos(nodeAng[k]);
        xs[k] = xs[lch] + c * xs[rch] - s * ys[rch];
        ys[k] = ys[lch] + s * xs[rch] + c * ys[rch];
    }
}

int main() {
    int n, c;
    while(scanf("%d %d\n", &n, &c) == 2) {
        L.clear();
        prevAng.clear();
        nodeAng.clear(); nodeAng.resize(1 << 15, 0);
        xs.clear(); xs.resize(1 << 15, 0);
        ys.clear(); ys.resize(1 << 15, 0);

        for (int i = 0; i < n; ++i) {
            int ss; cin >> ss;
            L.push_back(ss);
            prevAng.push_back(PI);
        }

        init(0, 0, n);

        for (int i = 0; i < c; ++i) {
            int idx; cin >> idx; idx--; // 0th idx
            double theta; cin >> theta; theta = theta / 180.0 * PI;
            double deltaTheta = theta - prevAng[idx];
            update(idx, 0, n, deltaTheta, 0);
            prevAng[idx] = theta;
            printf("%.2f %.2f\n", xs[0], ys[0]);
        }
    }
    return 0;
}