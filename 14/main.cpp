//discussion:b09902010, b09902012, b09902060
#include <bits/stdc++.h>

typedef struct {
    int idx;
    long long int s, e, x, p;
}Task;

struct cmp_e{
    bool operator()(const Task &t0, const Task &t1) {return t0.e > t1.e;}
};

int cmp_p(const Task t0, const Task t1) {return t0.p > t1.p;}

int main() {
    int N, s_idx;
    Task task_tmp;
    Task tasks[3001];
    long long int ans;
    long long int xr[3001];
    long long int p[3001];
    long long int mx_num[3001] = {0};
    long long int cur, tmp;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lld%lld%lld%lld", &(tasks[i].s), &(tasks[i].e), &(tasks[i].x), &(tasks[i].p));
        tasks[i].idx = i;
    }
    std::sort(tasks, tasks + N, cmp_p);
    for (int i = 0; i < N; i++) p[i] = tasks[i].p;
    for (int i = 0; i < N; i++) {
        std::priority_queue<Task, std::vector<Task>, cmp_e> q;
        for (int j = i; j > 0; j--) {
            if (tasks[j - 1].s > tasks[j].s) {
                task_tmp = tasks[j];
                tasks[j] = tasks[j - 1];
                tasks[j - 1] = task_tmp;
            }
        }
        s_idx = 0, cur = tasks[0].s;
        while (1) {
            while (s_idx <= i && cur >= tasks[s_idx].s) {
                xr[tasks[s_idx].idx] = tasks[s_idx].x;
                q.push(tasks[s_idx]);
                s_idx += 1;
            }
            if (s_idx <= i && !q.empty()) {
                if (q.top().e < tasks[s_idx].s) {
                    if (xr[q.top().idx] < q.top().e - cur + 1) {
                        mx_num[i] += xr[q.top().idx];
                        cur += xr[q.top().idx];
                        xr[q.top().idx] -= xr[q.top().idx];
                        q.pop();
                    }
                    else {
                        mx_num[i] += q.top().e - cur + 1;
                        cur += q.top().e - cur + 1;
                        xr[q.top().idx] -= q.top().e - cur + 1;
                        q.pop();
                    }
                }
                else {
                    if (xr[q.top().idx] <= tasks[s_idx].s - cur) {
                        mx_num[i] += xr[q.top().idx];
                        cur += xr[q.top().idx];
                        xr[q.top().idx] = 0;
                        q.pop();
                    }
                    else {
                        mx_num[i] += tasks[s_idx].s - cur;
                        xr[q.top().idx] -= tasks[s_idx].s - cur;
                        cur += tasks[s_idx].s - cur;
                    }
                }
            }
            else if (s_idx <= i) {
                xr[tasks[s_idx].idx] = tasks[s_idx].x;
                q.push(tasks[s_idx]);
                cur = tasks[s_idx].s;
                s_idx += 1;
            }
            else if (!q.empty()) {
                if (xr[q.top().idx] < q.top().e - cur + 1) {
                    mx_num[i] += xr[q.top().idx];
                    cur += xr[q.top().idx];
                    xr[q.top().idx] = 0;
                    q.pop();
                }
                else {
                    mx_num[i] += q.top().e - cur + 1;
                    cur += q.top().e - cur + 1;
                    xr[q.top().idx] -= q.top().e - cur + 1;
                    q.pop();
                }
            }
            else break;
        }
    }
    ans = p[0] * mx_num[0];
    for (int i = 1; i < N; i++) ans += p[i] * (mx_num[i] - mx_num[i - 1]);
    printf("%lld", ans);
    return 0;
}
