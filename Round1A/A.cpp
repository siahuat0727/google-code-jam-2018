#include <cstdio>
#include <cstdlib>
#include <cstring>

#define PB push_back

using namespace std;

#define MAXN 101

int row_choc[MAXN];
int col_choc[MAXN];
int choc_rc[MAXN][MAXN];
int hcut[MAXN];
int vcut[MAXN];

int r, c;
int h, v;
int total_choc;

bool check_possible() {
    if (total_choc % (h+1) != 0)
        return false;
    int each_row_choc = total_choc / (h+1);

    if (total_choc % (v+1) != 0)
        return false;
    int each_col_choc = total_choc / (v+1);

    if (total_choc % ((h+1)*(v+1)) != 0)
        return false;
    int each_box_choc = total_choc / ((h+1)*(v+1));

    int hh = 0, vv = 0;
    int num_cur_total = 0;
    for (int rr = 0; rr < r && hh < h; ++rr) {
        num_cur_total += row_choc[rr];
        if (num_cur_total == each_row_choc) {
            hcut[hh++] = rr;
            num_cur_total = 0;
        } else if (num_cur_total > each_row_choc) {
            return false;
        }
    }
    num_cur_total = 0;
    for (int cc = 0; cc < c && vv < v; ++cc) {
        num_cur_total += col_choc[cc];
        if (num_cur_total == each_col_choc) {
            vcut[vv++] = cc;
            num_cur_total = 0;
        } else if (num_cur_total > each_col_choc) {
            return false;
        }
    }
    int h_prev = 0, v_prev = 0;
    for (int hh = 0; hh < h; ++hh) {
        for (int vv = 0; vv < v; ++vv) {
            int total;
            if (hh == 0) {
                if (vv == 0)
                    total = choc_rc[hcut[hh]][vcut[vv]];
                else
                    total = choc_rc[hcut[hh]][vcut[vv]] - choc_rc[hcut[hh]][vcut[v_prev]];
            } else {
                if (vv == 0)
                    total = choc_rc[hcut[hh]][vcut[vv]] - choc_rc[hcut[h_prev]][vcut[vv]];
                else
                    total = choc_rc[hcut[hh]][vcut[vv]] - choc_rc[hcut[hh]][vcut[v_prev]]
                        - choc_rc[hcut[h_prev]][vcut[vv]] + choc_rc[hcut[h_prev]][vcut[v_prev]];
            }
            v_prev = vv;
            if (total != each_box_choc)
                return false;
        }
        h_prev = hh;
    }
    return true;
}

void solve(){
    memset(row_choc, 0, sizeof(row_choc));
    memset(col_choc, 0, sizeof(col_choc));
    scanf("%d%d%d%d\n", &r, &c, &h, &v);
    total_choc = 0;
    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            if (getchar() == '@'){
                row_choc[i]++;
                col_choc[j]++;
                total_choc++;
            }
            choc_rc[i][j] = row_choc[i] + (i == 0 ? 0 : choc_rc[i-1][j]);
        }
        getchar();
    }
    printf("%sPOSSIBLE\n", check_possible() ? "" : "IM");
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
