#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    long long ans = 0, a, b, c;
    long long p[200000], z[200000], val0[200000], val1[200000];
    scanf("%d%lld%lld%lld", &N, &a, &b, &c);
    for (int i = 0; i < N; i++) {
        scanf("%lld%lld", &(p[i]), &(z[i]));
        val0[i] = a * p[i], val1[i] = b * p[i] + c;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (z[i] > z[j] && val0[i] > val1[j] && i != j)
                ans += 1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
