//discussion: b09902008, b0990210
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rank;
    long long z, val0, val1;
}Data;

int N;
long long a, b, c, ans = 0;
Data data[2000010];
int buff_num = 0;
int buff[2000000];

int bit[2000010] = {0};
int rank_num; 
long long rank_val[2000010];
int rank[2000010];

int lowbit(int idx) {
    return idx & (-idx);
}

void edit(int idx) {
    for (int i = idx; i <= rank_num; i += lowbit(i)) {
        bit[i] += 1;
    }
}

long long sum(int idx) {
    int ans = 0;
    for (int i = idx; i > 0; i -= lowbit(i)) {
        ans += bit[i];
    }
    return ans;
}

int cmp_val(const void *a, const void *b) {
    Data *da = (Data *)a, *db = (Data *)b;
    return da->val1 > db->val1;
}

int cmp_z(const void *a, const void *b) {
    Data *da = (Data *)a, *db = (Data *)b;
    return da->z > db->z;
}

int b_search(long long val) {
    int l = 1, r = rank_num, mid;
    while (l <= r) {
        mid = (l + r) / 2;
        if (rank_val[mid] < val) l = mid + 1;
        else if (rank_val[mid] > val) r = mid - 1;
        else return mid;
    }
    return r;
}

int main() {
    long long p, pre;
    scanf("%d%lld%lld%lld", &N, &a, &b, &c);
    for (int i = 0; i < N; i++) {
        scanf("%lld%lld", &p, &(data[i].z));
        data[i].val0 = a * p;
        data[i].val1 = b * p + c;
    }
    qsort(data, N, sizeof(Data), cmp_val);
    rank_num = 0;
    for (int i = 0; i < N; i++) {
        if (rank_num == 0 ||
            rank_val[rank_num] != data[i].val1) {
            rank_num += 1;
            rank_val[rank_num] = data[i].val1;
        }
        data[i].rank = rank_num;
    }
    qsort(data, N, sizeof(Data), cmp_z);
    pre = -1;
    for (int i = 0; i < N; i++) {
        if (pre != data[i].z) {
            for (int j = 0; j < buff_num; j++) {
                edit(buff[j]);
            }
            buff_num = 0;
        }
        ans += (long long)sum(b_search(data[i].val0 - 1));
        buff[buff_num++] = data[i].rank;
        pre = data[i].z;
    }
    printf("%lld", ans);
    return 0;
}
