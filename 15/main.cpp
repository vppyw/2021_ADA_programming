//discussion: b09902034, b09902135
#include <bits/stdc++.h>

int N;
int arr_ptr;
long long int arr[100010];
int arr_ptr1;
long long int arr1[100010];
long long int ans[100010];

typedef struct {
    int idx0, idx1;
    long long int val0, val1;
}Pair;

typedef struct {
    bool operator()(const Pair &a, const Pair &b) {
        return (a.val0 + a.val1) > (b.val0 + b.val1);
    }
}Pair_cmp;

void handle_read() {
    long long int cur;
    arr_ptr = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &cur);
        if (cur == 0) continue;
        if (arr_ptr == 0) arr[arr_ptr++] = cur;
        else {
            if (arr[arr_ptr - 1] < 0) {
                if (cur < 0) {
                    if (cur > arr[arr_ptr - 1]) arr[arr_ptr - 1] = cur;
                }
                else arr[arr_ptr++] = cur;
            }
            else {
                if (cur > 0) {
                    if (cur > arr[arr_ptr - 1]) arr[arr_ptr - 1] = cur;
                }
                else arr[arr_ptr++] = cur;
            }
        }
    }
    arr_ptr1 = 0;
    if (arr_ptr > 1) {
        arr_ptr1 = arr_ptr - 1;
        if (arr[0] > arr[arr_ptr - 1])
            for (int i = 0; i < arr_ptr1; i++) arr1[i] = arr[i];
        else
            for (int i = 0; i < arr_ptr1; i++) arr1[i] = arr[i + 1];
    }
}

void fill_up(int ptr, long long int *a) {
    long long int sum = 0;
    Pair p;
    std::set<int> idx_set = {};
    std::priority_queue<Pair, std::vector<Pair>, Pair_cmp> q;
    for (int i = 0; i < ptr; i++) {
        idx_set.insert(i);
        sum += a[i];
        p.idx0 = std::min(i, (i + 1) % ptr);
        p.idx1 = std::max(i, (i + 1) % ptr);
        p.val0 = a[p.idx0];
        p.val1 = a[p.idx1];
        q.push(p);
        idx_set.insert(i);
    }
    ans[ptr] = sum;
    while (ptr > 1) {
        while (!q.empty()) {
            p = q.top();
            q.pop();
            if (idx_set.count(p.idx0) && idx_set.count(p.idx1))
                break;
        }
        sum -= p.val0 + p.val1;
        if (p.idx0 == *idx_set.begin() || p.idx1 == *idx_set.rbegin()) {
            idx_set.erase(p.idx0);
            idx_set.erase(p.idx1);
            if (idx_set.empty()) break;
            p.idx0 = *idx_set.begin();
            p.idx1 = *idx_set.rbegin();
        }
        else {
            idx_set.erase(p.idx0);
            idx_set.erase(p.idx1);
            if (idx_set.empty()) break;
            p.idx0 = *std::prev(idx_set.lower_bound(p.idx0));
            p.idx1 = *idx_set.upper_bound(p.idx1);
        }
        p.val0 = a[p.idx0];
        p.val1 = a[p.idx1];
        q.push(p);
        ptr -= 2;
        ans[ptr] = sum;
    }
}

void func() {
    handle_read();
    fill_up(arr_ptr, arr);
    fill_up(arr_ptr1, arr1);
    for (int i = 1; i <= arr_ptr; i++) printf("%lld ", ans[i]);
    for (int i = arr_ptr + 1; i <= N; i++) printf("0 ");
    putchar('\n');
}

int main() {
    int T, flag;
    scanf("%d%d", &T, &flag);
    while (T--) func();
    return 0;
}
