#include <stdio.h>
#include <stdlib.h>
#define max(x, y) ((x > y)?x:y)
#define min(x, y) ((x < y)?x:y)
typedef struct {
    long long x, y;
}Point;

int main(int argc, char *argv[]) {
    int N, flag;
    long long ans = 0;
    Point p[200000];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lld%lld", &(p[i].x), &(p[i].y));
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            flag = 1;
            for (int k = 0; k < N; k++) {
                if (k == i || k == j) continue;
                if (max(p[i].x, p[j].x) > p[k].x &&
                    min(p[i].x, p[j].x) < p[k].x &&
                    max(p[i].y, p[j].y) > p[k].y &&
                    min(p[i].y, p[j].y) < p[k].y) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                ans += 1;
            }
        }
    }
    printf("\n%lld\n", ans / 2);
    return 0;
}
