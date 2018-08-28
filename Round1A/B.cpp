#include <cstdio>
#include <algorithm>

#define MAXN 1001
typedef long long ll;

using namespace std;

int M[MAXN];
int S[MAXN];
int P[MAXN];
int C[MAXN];

int r, c, b;

bool cmp(int a, int b)
{
    return a > b;
}

bool f(ll T)
{
    for (int i = 0; i < c; ++i) {
        C[i] = (int)max(0LL, min((ll)M[i], (T-P[i]) / S[i]));
    }
    nth_element(C, C+r, C+c, cmp);
    ll total = 0;
    for (int i = 0; i < r; ++i) {
        total += C[i];
    }
    return total >= b;
}

void solve(){
    scanf("%d %d %d", &r, &b, &c);
    for (int i = 0; i < c; ++i) {
        scanf("%d %d %d", &M[i], &S[i], &P[i]);
    }
    ll left = 0, right = (ll) *max_element(S, S+c) * b + *max_element(P, P+c);
    while (left < right) {
        ll mid = (left + right) / 2;
        if (f(mid)) {
            right = mid;
        } else {
            left = mid+1;
        }
    }
    printf("%lld\n", left);
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
