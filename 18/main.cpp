#include <bits/stdc++.h>

int N, M;
bool vis[100010];
std::vector<int> edge[100010];

void dfs_search(int idx) {
    vis[idx] = true;
    printf("%d ", idx);
    for (auto cld: edge[idx]) if (!vis[cld]) dfs_search(cld);
}

void dfs() {
    for (int i = 1; i <= N; i++) {
        vis[i] = false;
        std::sort(edge[i].begin(), edge[i].end());
    }
    dfs_search(1);
    putchar('\n');
}

void bfs() {
    std::vector<int> q, tmp;
    for (int i = 1; i <= N; i++) {
        vis[i] = false;
        std::sort(edge[i].begin(), edge[i].end());
    }
    q.push_back(1); 
    while (!q.empty()) {
        tmp.clear();
        std::sort(q.begin(), q.end());
        for (auto idx: q) {
            vis[idx] = true;
            printf("%d ", idx);
            for (auto cld: edge[idx]) {
                if (!vis[cld]) {
                    vis[cld] = true;
                    tmp.push_back(cld);
                }
            }
        }
        q.assign(tmp.begin(), tmp.end());
    }
    putchar('\n');
}

int main() {
    int v0, v1;
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d%d", &v0, &v1);
        edge[v0].push_back(v1);
        edge[v1].push_back(v0);
    }
    dfs();
    bfs();
    return 0;
}
