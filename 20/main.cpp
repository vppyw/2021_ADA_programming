//discussion: b09902017, b09902034
//reference:
//    https://link.springer.com/content/pdf/10.1007%2F0-387-23529-9_2.pdf

#include <bits/stdc++.h>

long long int T;
int N, M, flag;
std::vector<int> edges[131072];
std::vector<std::vector<int>> sccs;
unsigned long int g_to_scc[131072];
std::vector<int> scc_edges[131072];
bool in[131072], out[131072];
std::vector<std::pair<int, int>> path_pair;
std::vector<int>sink;
std::vector<int>source;
std::vector<std::pair<int, int>> add_edges;

void tarjan();
void scc_func(int, int &, std::stack<int> &, bool [], int [], int []);
void st();
void search(int, int &, bool &, bool []);
void construct();

int main() {
    int u, v;
    scanf("%lld%d", &T, &flag);
    while (T--) {
        scanf("%d%d", &N, &M);
        for (auto scc: sccs) scc.clear();
        sccs.clear();
        path_pair.clear();
        sink.clear();
        source.clear();
        add_edges.clear();
        for (int i = 0; i <= N; i++)
            edges[i].clear(), scc_edges[i].clear(), in[i] = false, out[i] = false;
        for (int i = 0; i < M; i++) {
            scanf("%d%d", &u, &v);
            edges[u].push_back(v);
        }
        tarjan();
        st();
        construct();
        printf("%lu\n", add_edges.size());
        if (flag) for (auto e:add_edges) printf("%d %d\n", e.first, e.second);
    }
    return 0;
}

void tarjan() {
    int idx = 0;
    std::stack<int> s;
    bool in_s[131072] = {0};
    int dfn[131072] = {0};
    int low[131072] = {0};
    for (int i = 1; i <= N; i++) if (dfn[i] == 0) scc_func(i, idx, s, in_s, dfn, low);
    for (int i = 1; i <= N; i++) {
        for (auto nxt:edges[i]) {
            if (g_to_scc[i] != g_to_scc[nxt]) {
                scc_edges[g_to_scc[i]].push_back(g_to_scc[nxt]);
                out[g_to_scc[i]] = true;
                in[g_to_scc[nxt]] = true;
            }
        }
    }
}

void scc_func(int u, int &idx, std::stack<int> &s, bool in_s[], int dfn[], int low[]) {
    int v;
    idx += 1;
    dfn[u] = low[u] = idx;
    s.push(u);
    in_s[u] = true;
    for (auto v:edges[u]) {
        if (dfn[v] == 0) {
            scc_func(v, idx, s, in_s, dfn, low);
            low[u] = std::min(low[u], low[v]);
        }
        else if (in_s[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        sccs.push_back({});
        while (!s.empty()) {
            v = s.top();
            s.pop();
            (*sccs.rbegin()).push_back(v);
            g_to_scc[v] = sccs.size() - 1;
            in_s[v] = false;
            if (u == v) break;
        }
    }
}

void st() {
    int w;
    unsigned long int sz = sccs.size();
    bool n_sink;
    bool mark[131072] = {0};
    for (int i = 0; i < sz; i++) {
        if (!mark[i] && !in[i] && out[i]) {
            w = -1;
            n_sink = true;
            search(i, w, n_sink, mark);
            if (w != -1) path_pair.push_back(std::pair<int, int>{i, w});
        }
    }
}

void search(int idx, int &w, bool &n_sink, bool mark[]) {
    if (!mark[idx]) {
        if (in[idx] && !out[idx]) {
            w = idx;
            n_sink = false;
        }
        mark[idx] = true;
        for (auto nxt:scc_edges[idx]) {
            if (n_sink) search(nxt, w, n_sink, mark);
            else break;
        }
    }
}

void construct() {
    int pre, sta;
    unsigned long int sz = sccs.size(), p_sz, so_sz, si_sz;
    if (sz <= 1) return;
    if (path_pair.empty()) {
        pre = -1;
        for (int i = 0; i < sz; i++) {
            if (!out[i] && !in[i]) {
                if (pre == -1) {
                    sta = i, pre = i;
                    continue;
                }
                add_edges.push_back(std::pair<int, int>{sccs[pre][0], sccs[i][0]});
                in[i] = true, out[i] = true;
                pre = i;
            }
        }
        add_edges.push_back(std::pair<int, int>{sccs[pre][0], sccs[sta][0]});
    }
    else {
        p_sz = path_pair.size();
        for (int i = 1; i < p_sz; i++) {
            add_edges.push_back(std::pair<int, int>{
                sccs[path_pair[i - 1].second][0],
                sccs[path_pair[i].first][0]});
            out[path_pair[i - 1].second] = true;
            in[path_pair[i].first] = true;
        }
        pre = path_pair[p_sz - 1].second;
        for (int i = 0; i < sz; i++) {
            if (!out[i] && !in[i]) {
                add_edges.push_back(std::pair<int, int>{sccs[pre][0], sccs[i][0]});
                in[i] = true, out[pre] = true;
                pre = i;
            }
        }
        add_edges.push_back(std::pair<int, int>{sccs[pre][0], sccs[path_pair[0].first][0]});
        out[pre] = true, in[path_pair[0].first] = true;
        for (auto i = 0; i < sz; i++) {
            if (!out[i]) sink.push_back(i);
            else if (!in[i]) source.push_back(i);
        }
        for (auto si = sink.begin(), so = source.begin(); si != sink.end() && so != source.end(); si++, so++) {
            add_edges.push_back(std::pair<int, int>{sccs[*si][0], sccs[*so][0]});
            out[*si] = true, in[*so] = true;
        }
        si_sz = sink.size(), so_sz = source.size();
        if (si_sz > so_sz) {
            for (int i = so_sz; i < si_sz; i++)
                add_edges.push_back(std::pair<int, int>{sccs[sink[i]][0], sccs[path_pair[0].first][0]});
        }
        else if (si_sz < so_sz) {
            for (int i = si_sz; i < so_sz; i++)
                add_edges.push_back(std::pair<int, int>{sccs[path_pair[0].first][0], sccs[source[i]][0]});
        }
    }
}
