//discussion: b09902010, b09902017, b09902060, b09902061, b09902135
#include <bits/stdc++.h>

int N;
std::vector<int> edges[200010];
int vis[200010] = {0};
int par[200010] = {0};
int par_l[200010] = {0};
int depth[200010][2] = {{0}};
int cld[200010][2] = {{0}};
std::vector<int> dm_q;
int l_di[200010];
int r_di[200010];

void find_mx_cld(int idx) {
    vis[idx] = 1;
    for (auto nxt:edges[idx]) {
        if (vis[nxt]) continue;
        par[nxt] = idx;
        find_mx_cld(nxt);
        if (depth[idx][0] <= depth[nxt][0] + 1) {
            depth[idx][1] = depth[idx][0];
            depth[idx][0] = depth[nxt][0] + 1;
            cld[idx][1] = cld[idx][0];
            cld[idx][0] = nxt;
        }
        else if (depth[idx][1] < depth[nxt][0] + 1) {
            depth[idx][1] = depth[nxt][0] + 1;
            cld[idx][1] = nxt;
        }
    }
}

void find_par_l(int idx) {
    vis[idx] = 1;
    if (idx != 1) {
        par_l[idx] = par_l[par[idx]] + 1;
        if (idx != cld[par[idx]][0] && par_l[idx] < depth[par[idx]][0] + 1)
            par_l[idx] = depth[par[idx]][0] + 1;
        if (idx != cld[par[idx]][1] && par_l[idx] < depth[par[idx]][1] + 1)
            par_l[idx] = depth[par[idx]][1] + 1;
    }
    else par_l[idx] = 0;
    for (auto nxt:edges[idx]) {
        if (vis[nxt]) continue;
        find_par_l(nxt);
    }
}

void d_tra_l(int idx) {
    if (depth[idx][0] != 0) d_tra_l(cld[idx][0]);
    dm_q.push_back(idx);
}

void d_tra_r(int idx) {
    dm_q.push_back(idx);
    if (depth[idx][0] != 0) d_tra_r(cld[idx][0]);
}

int dfs_d(int idx) {
    int mx = 0, tmp;
    vis[idx] = 1;
    for (auto nxt: edges[idx]) {
        if (vis[nxt]) continue;
        tmp = dfs_d(nxt);
        if (mx < tmp + 1) mx = tmp + 1;
    }
    return mx;
}

void find_diameter() {
    int mx = -1, mn = INT_MAX, root = 0, sz, tmp;
    for (int i = 1; i <= N; i++)
        if (depth[i][0] + depth[i][1] > mx)
            mx = depth[i][0] + depth[i][1], root = i;
    if (depth[root][0] != 0) d_tra_l(cld[root][0]);
    dm_q.push_back(root);
    if (depth[root][1] != 0) d_tra_r(cld[root][1]);
    sz = dm_q.size();
    for (int i = 1; i <= N; i++) vis[i] = 0;
    for (int i = 1; i < sz - 1; i++) {
        vis[dm_q[i]] = 0, vis[dm_q[i - 1]] = 1, vis[dm_q[i + 1]] = 1;
        tmp = dfs_d(dm_q[i]);
        l_di[i] = l_di[i - 1];
        if (i + tmp > l_di[i])
            l_di[i] = i + tmp;
    }
    for (int i = 1; i <= N; i++) vis[i] = 0;
    for (int i = sz - 2; i > 0; i--) {
        vis[dm_q[i]] = 0, vis[dm_q[i - 1]] = 1, vis[dm_q[i + 1]] = 1;
        tmp = dfs_d(dm_q[i]);
        r_di[i] = r_di[i + 1];
        if (r_di[i] < sz - i - 1 + tmp)
            r_di[i] = sz - i  - 1 + tmp;
    }
    r_di[0] = sz - 1, l_di[sz - 1] = sz - 1;
    for (int i = 1; i < sz; i++) {
        mx = std::max((l_di[i - 1] + 1) / 2 + (r_di[i] + 1 ) / 2 + 1,
                     std::max(l_di[i - 1], r_di[i]));
        if (mx < mn) mn = mx;
    }
    printf("%d", mn);
}

int main() {
    int v, u;
    scanf("%d", &N);
    for (int i = 1; i < N; i++) {
        scanf("%d%d", &u, &v);
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    find_mx_cld(1);
    for (int i = 1; i <= N; i++) vis[i] = 0;
    find_par_l(1);
    find_diameter();
    return 0;
}
