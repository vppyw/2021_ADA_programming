//discussion: b09902010, b09902017, b09902135

#include <bits/stdc++.h>

typedef struct {
    long long int idx, nxt, w, dis;
}Edge;

typedef struct {
    bool operator()(const Edge &a, const Edge &b) {
        return a.dis > b.dis;
    }
}Edge_dis;

typedef struct {
    bool operator()(const Edge &a, const Edge &b) {
        if (a.w == b.w) return a.dis > b.dis;
        return a.w > b.w;
    }
}Edge_w;

int N, M;
std::vector<Edge> edges[100010];
bool vis[100010];
long long int dij_dis[100010];
long long int prim_dis[100010];
std::vector<long long int> sel;

void dijkstra() {
    Edge u;
    std::priority_queue<Edge, std::vector<Edge>, Edge_dis> q;
    for (int i = 1; i <= N; i++) vis[i] = false, dij_dis[i] = LLONG_MAX;
    dij_dis[1] = 0;
    q.push(Edge{0, 1, 0, 0});
    while (!q.empty()) {
        u = q.top();
        q.pop();
        if (vis[u.nxt]) continue;
        vis[u.nxt] = true;
        for (auto v: edges[u.nxt]) {
            if (vis[v.nxt]) continue;
            if (dij_dis[v.nxt] > dij_dis[u.nxt] + v.w) {
                dij_dis[v.nxt] = dij_dis[u.nxt] + v.w;
                v.dis = dij_dis[v.nxt];
                q.push(v);
            }
        }
    }
}

void prim() {
    Edge u;
    std::priority_queue<Edge, std::vector<Edge>, Edge_w> q;
    for (int i = 1; i <= N; i++) vis[i] = false, prim_dis[i] = LLONG_MAX;
    prim_dis[1] = 0;
    q.push(Edge{0, 1, 0, 0});
    while (!q.empty()) {
        u = q.top();
        q.pop();
        if (vis[u.nxt]) continue;
        vis[u.nxt] = true;
        prim_dis[u.nxt] = u.dis;
        sel.push_back(u.idx);
        for (auto v: edges[u.nxt]) {
            if (vis[v.nxt]) continue;
            if (prim_dis[v.nxt] > prim_dis[u.nxt] + v.w) {
                v.dis = prim_dis[u.nxt] + v.w;
            }
            q.push(v);
        }
    }
}

void check() {
    int sz = sel.size();
    for (int i = 1; i <= N; i++) {
        if (dij_dis[i] != prim_dis[i]) {
            printf("No\n");
            return;
        }
    }
    printf("Yes\n");
    for (int i = 1; i < sz; i++) printf("%lld ", sel[i]);
}

int main() {
    long long int a, b, c;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        scanf("%lld%lld%lld", &a, &b, &c);
        edges[a].push_back(Edge{i, b, c, LLONG_MAX});
        edges[b].push_back(Edge{i, a, c, LLONG_MAX});
    }
    dijkstra();
    prim();
    check();
    return 0;
}
