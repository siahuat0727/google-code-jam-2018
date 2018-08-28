#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>

#define MAXWH 251
#define MAXN 101

using namespace std;

int w[MAXN];
int h[MAXN];
int Min[MAXN];
double Max[MAXN];
double dp[MAXN * 2 * MAXWH + 1];

// knapsack
void solve(){
    int n, p;
    scanf("%d%d", &n, &p);
    int target = p;
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &w[i], &h[i]);
        Min[i] = 2*min(w[i], h[i]);
        Max[i] = 2*sqrt(w[i]*w[i] + h[i]*h[i]);
        target -= 2*(w[i] + h[i]);
    }
    memset(dp, 0, sizeof(dp));
    int maxd = min(target, n*2*MAXWH);
    for (int i = 0; i < n; ++i)
        for (int d = maxd; d > 0; --d)
            if (d - Min[i] >= 0)
                dp[d] = max(dp[d-Min[i]] + Max[i], dp[d]);
    double max_ = 0;
    for (int d = 1; d <= maxd; ++d)
        max_ = max(dp[d], max_);
    printf("%.6f\n", max_ > target ? (double)p : p-target+max_);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        printf("Case #%d: ", i);
        solve();
    }
    return 0;
}
