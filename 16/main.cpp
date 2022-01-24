//discusion: b09902010, b09902100, b09902116, b09902135

#include <bits/stdc++.h>

typedef struct {
    int i, j;
}Pos;

const int pow_table[32] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432};

int n, m, k;
int tri_idx, rec_idx;

long long int **tri_mx[1000010];
Pos **tri_pos[1000010];
long long int **rec_mx[1000010];
Pos **rec_pos[1000010];
Pos *pre[1000010];

void init_bridge() {
    for (int i = 0; i < n; i++) {
        tri_mx[i] = (long long int **)malloc(m * sizeof(long long int *));
        tri_pos[i] = (Pos **)malloc(m * sizeof(Pos *));
        rec_mx[i] = (long long int **)malloc(m * sizeof(long long int *));
        rec_pos[i] = (Pos **)malloc(m * sizeof(Pos *));
        pre[i] = (Pos *)malloc(m * sizeof(Pos));
    }
    tri_idx = 0;
    for (int i = 0; i < 26; i++)
        if (pow_table[i] <= k) tri_idx =  i;
    rec_idx = 0;
    for (int i = 0; i < 26; i++)
        if (pow_table[i] <= k - pow_table[tri_idx]) rec_idx = i;
}

void free_bridge() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            free(tri_mx[i][j]);
            free(tri_pos[i][j]);
            free(rec_mx[i][j]);
            free(rec_pos[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        free(tri_mx[i]); 
        free(tri_pos[i]);
        free(rec_mx[i]);
        free(rec_pos[i]);
        free(pre[i]);
    }
}

void init_cell(int row, int col) {
    tri_mx[row][col] = (long long int *)malloc(26 * sizeof(long long int));
    tri_pos[row][col] = (Pos *)malloc(26 * sizeof(Pos));
    rec_mx[row][col] = (long long int *)malloc(26 * sizeof(long long int));
    rec_pos[row][col] = (Pos *)malloc(26 * sizeof(Pos));
    for (int i = 0; i < 26; i++) {
        tri_mx[row][col][i] = LLONG_MIN;
        tri_pos[row][col][i] = Pos{row, col};
        rec_mx[row][col][i] = LLONG_MIN;
        rec_pos[row][col][i] = Pos{row, col};
    }
    pre[row][col] = Pos{row, col};
}

long long int get_rec(int row, int col, int idx) {
    if (row < 0 || col < 0) return LLONG_MIN;
    return rec_mx[row][col][idx];
}

long long int get_tri(int row, int col, int idx) {
    if (row < 0 || col < 0) return LLONG_MIN;
    return tri_mx[row][col][idx];
}

void update_rec(int row, int col, int idx) {
    if (row < 0 || col < 0 || idx == 0) return;
    update_rec(row, col, idx - 1);
    if (rec_mx[row][col][idx] < get_rec(row, col, idx - 1)) {
        rec_mx[row][col][idx] = get_rec(row, col, idx - 1);
        rec_pos[row][col][idx] = rec_pos[row][col][idx - 1];
    }
    if (rec_mx[row][col][idx] < get_rec(row - pow_table[idx - 1], col, idx - 1)) {
        rec_mx[row][col][idx] = get_rec(row - pow_table[idx - 1], col, idx - 1);
        rec_pos[row][col][idx] = rec_pos[row - pow_table[idx - 1]][col][idx - 1];
    }
    if (rec_mx[row][col][idx] < get_rec(row, col - pow_table[idx - 1], idx - 1)) {
        rec_mx[row][col][idx] = get_rec(row, col - pow_table[idx - 1], idx - 1);
        rec_pos[row][col][idx] = rec_pos[row][col - pow_table[idx - 1]][idx - 1];
    }
    if (rec_mx[row][col][idx] < get_rec(row - pow_table[idx - 1], col - pow_table[idx - 1], idx - 1)) {
        rec_mx[row][col][idx] = get_rec(row - pow_table[idx - 1], col - pow_table[idx - 1], idx - 1);
        rec_pos[row][col][idx] = rec_pos[row - pow_table[idx - 1]][col - pow_table[idx - 1]][idx - 1];
    }
}

void update_tri(int row, int col, int idx) {
    if (row < 0 || col < 0 || idx == 0) return;
    update_tri(row, col, idx - 1);
    if (tri_mx[row][col][idx] < get_tri(row - pow_table[idx - 1], col, idx - 1)) {
        tri_mx[row][col][idx] = get_tri(row - pow_table[idx - 1], col, idx - 1);
        tri_pos[row][col][idx] = tri_pos[row - pow_table[idx - 1]][col][idx - 1];
    }
    if (tri_mx[row][col][idx] < get_tri(row, col - pow_table[idx - 1], idx - 1)) {
        tri_mx[row][col][idx] = get_tri(row, col - pow_table[idx - 1], idx - 1);
        tri_pos[row][col][idx] = tri_pos[row][col - pow_table[idx - 1]][idx - 1];
    }
    if (tri_mx[row][col][idx] < get_rec(row, col, idx - 1)) {
        tri_mx[row][col][idx] = get_rec(row, col, idx - 1);
        tri_pos[row][col][idx] = rec_pos[row][col][idx - 1];
    }
}

void path() {
    Pos p, tmp;
    std::stack<Pos> s;
    if (rec_mx[n - 1][m - 1][0] == LLONG_MIN) printf("Impassable\n");
    else {
        printf("Passable\n");
        printf("%lld\n", rec_mx[n - 1][m - 1][0]);
        p = Pos{n - 1, m - 1};
        s.push(p);
        tmp = pre[p.i][p.j];
        while (p.i != tmp.i || p.j != tmp.j) {
            s.push(tmp);
            p = tmp;
            tmp = pre[p.i][p.j];
        }
        printf("%ld\n", s.size());
        while (!s.empty()) {
            printf("%d %d\n", s.top().i + 1, s.top().j + 1);
            s.pop();
        }
    }
}

void func() {
    int tmp_i, tmp_j;
    char buff[32];
    init_bridge();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%s", buff);
            init_cell(i, j);
            if (strcmp("X", buff)) {
                update_rec(i, j, tri_idx);
                update_tri(i, j, tri_idx);
                tmp_i = i;
                tmp_j = j;
                if (rec_mx[i][j][0] < get_rec(tmp_i, tmp_j, rec_idx)) {
                    rec_mx[i][j][0] = get_rec(tmp_i, tmp_j, rec_idx);
                    pre[i][j] = rec_pos[tmp_i][tmp_j][rec_idx];
                }
                tmp_i = i - k + pow_table[tri_idx] + pow_table[rec_idx] - 1;
                tmp_j = j;
                if (rec_mx[i][j][0] < get_rec(tmp_i, tmp_j, rec_idx)) {
                    rec_mx[i][j][0] = get_rec(tmp_i, tmp_j, rec_idx);
                    pre[i][j] = rec_pos[tmp_i][tmp_j][rec_idx];
                }
                tmp_i = i;
                tmp_j = j - k + pow_table[tri_idx] + pow_table[rec_idx] - 1;
                if (rec_mx[i][j][0] < get_rec(tmp_i, tmp_j, rec_idx)) {
                    rec_mx[i][j][0] = get_rec(tmp_i, tmp_j, rec_idx);
                    pre[i][j] = rec_pos[tmp_i][tmp_j][rec_idx];
                }
                tmp_i = i - k + pow_table[tri_idx] + pow_table[rec_idx] - 1;
                tmp_j = j - k + pow_table[tri_idx] + pow_table[rec_idx] - 1;
                if (rec_mx[i][j][0] < get_rec(tmp_i, tmp_j, rec_idx)) {
                    rec_mx[i][j][0] = get_rec(tmp_i, tmp_j, rec_idx);
                    pre[i][j] = rec_pos[tmp_i][tmp_j][rec_idx];
                }
                tmp_i = i - k + pow_table[tri_idx] - 1;
                tmp_j = j;
                if (rec_mx[i][j][0] < get_tri(tmp_i, tmp_j, tri_idx)) {
                    rec_mx[i][j][0] = get_tri(tmp_i, tmp_j, tri_idx);
                    pre[i][j] = tri_pos[tmp_i][tmp_j][tri_idx];
                }
                tmp_i = i;
                tmp_j = j - k + pow_table[tri_idx] - 1;
                if (rec_mx[i][j][0] < get_tri(tmp_i, tmp_j, tri_idx)) {
                    rec_mx[i][j][0] = get_tri(tmp_i, tmp_j, tri_idx);
                    pre[i][j] = tri_pos[tmp_i][tmp_j][tri_idx];
                }
                if (rec_mx[i][j][0] != LLONG_MIN) {
                    rec_mx[i][j][0] += std::stoll(buff);
                    tri_mx[i][j][0] = rec_mx[i][j][0];
                    tri_pos[i][j][0] = rec_pos[i][j][0];
                }
                else if (i == 0 && j == 0) {
                    rec_mx[i][j][0] = std::stoll(buff);
                    tri_mx[i][j][0] = std::stoll(buff);
                }
            }
            update_rec(i, j, tri_idx);
            update_tri(i, j, tri_idx);
        }
    }
    path();
    free_bridge();
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        func();
    }
    return 0;
}
