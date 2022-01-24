// discussion: b09902008, b09902061, b09902100
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x, y;
}Point;

int cmp_x(const void *a, const void *b);
long long func(int len, Point *p);
int search(long long y, int len, Point *p);

int main(int argc, char *argv[]) {
    int N;
    Point p[200000];
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lld%lld", &(p[i].x), &(p[i].y));
    }
    qsort(p, N, sizeof(Point), cmp_x);
    printf("%lld", func(N, p));
    return 0;
}

int cmp_x(const void *a, const void *b) {
    Point *pa = (Point *)a, *pb = (Point *)b;
    return pa->x > pb->x;
}

int search(long long y, int len, Point *p) {
    int l = 0, r = len - 1, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (y < p[mid].y) l = mid + 1;
        else r = mid - 1;
    }
    return r;
}

long long func(int len, Point *p) {
    int mid = len / 2;
    long long ret = 0;
    int l, r, tmp_ptr = 0;
    Point *tmp = (Point *)malloc((len + 1) * sizeof(Point));
    int lh_ptr, rh_ptr;
    Point *lh = (Point *)malloc((len + 1) * sizeof(Point));
    Point *rh = (Point *)malloc((len + 1) * sizeof(Point));

    if (len <= 1) return 0;
    ret += func(len / 2, p);
    ret += func(len - len / 2, &(p[mid]));
    
    r = len - 1, lh_ptr = 0, rh_ptr = 0;
    for (int i = mid - 1; i >= 0; i--) {
        while (lh_ptr > 0 && lh[lh_ptr - 1].x < p[i].x) {
            lh_ptr -= 1;
        }
        while (r >= mid && p[i].y < p[r].y) {
            while (rh_ptr > 0 && rh[rh_ptr - 1].x > p[r].x) {
                rh_ptr -= 1;
            }
            rh[rh_ptr++] = p[r];
            r -= 1;
        }
        if (lh_ptr > 0) {
            ret += rh_ptr - search(lh[lh_ptr - 1].y, rh_ptr, rh) - 1;
        }
        else {
            ret += rh_ptr;
        }
        lh[lh_ptr++] = p[i];
    }
    l = mid - 1, lh_ptr = 0, rh_ptr = 0;
    for (int i = len - 1; i >= mid; i--) {
        while (rh_ptr > 0 && rh[rh_ptr - 1].x > p[i].x) {
            rh_ptr -= 1;
        }
        while (l >= 0 && p[i].y < p[l].y) {
            while (lh_ptr > 0 && lh[lh_ptr - 1].x < p[l].x) {
                lh_ptr -= 1;
            }
            lh[lh_ptr++] = p[l];
            l -= 1;
        }
        if (rh_ptr > 0) {
            ret += lh_ptr - search(rh[rh_ptr - 1].y, lh_ptr, lh) - 1;
        }
        else {
            ret += lh_ptr;
        }
        rh[rh_ptr++] = p[i];
    }

    l = 0;
    r = mid;
    while (l < mid && r < len) {
        if (p[l].y < p[r].y) {
            tmp[tmp_ptr++] = p[l];
            l += 1;
        }
        else {
            tmp[tmp_ptr++] = p[r];
            r += 1;
        }
    }
    while (l < mid) {
        tmp[tmp_ptr++] = p[l];
        l += 1;
    }
    while (r < len) {
        tmp[tmp_ptr++] = p[r];
        r += 1;
    }
    for (int i = 0; i < tmp_ptr; i++) p[i] = tmp[i];
    return ret;
}
