// duscussion: b09902012
#include <stdio.h>


int main() {
    long long N, x, y, z, tmp0, tmp1;
    long long a[200000];
    long long cur, res;
    scanf("%lld%lld%lld%lld", &N, &x, &y, &z);
    for (int i = 0; i < N; i++) scanf("%lld", &(a[i]));
    cur = x * a[0] + z * a[1], res = x * a[0] + z * a[1];
    for (int i = 2; i < N; i++) {
        tmp0 = cur - z * a[i - 1] + y * a[i - 1] + z * a[i];
        tmp1 = x * a[i - 1] + z * a[i];
        if (tmp0 > tmp1) {
            cur = tmp0;
        }
        else {
            cur = tmp1;
        }
        if (cur > res) res = cur;
    }
    printf("%lld", res);
    return 0;
}
