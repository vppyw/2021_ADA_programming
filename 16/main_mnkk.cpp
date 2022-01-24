//discussion: b09902010
#include <bits/stdc++.h>

typedef struct {
    int i, j;
}Pos;

long long int *cell[1000000];
Pos *pre_pos[1000000];

int main(int arg_c, char *arg_v[]) {
    int T;
    int n, m, k;
    char buff[32];
    int mx_r, mx_c;
    long long int mx;
    Pos pos, tmp_pos;
    std::stack<Pos> pos_s;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < n; i++) {
            cell[i] = (long long int *)malloc(m * sizeof(long long int));
            pre_pos[i] = (Pos *)malloc(m * sizeof(Pos));
            for (int j = 0; j < m; j++) {
                scanf("%s", buff);
                if (!strcmp("X", buff)) {
                    cell[i][j] = LLONG_MIN;
                } 
                else{
                    mx = LLONG_MIN, cell[i][j] = LLONG_MIN;
                    for (int row = std::max(0, i - k); row <= i; row++) {
                        for (int col = std::max(0, j - row + i - k); col <= j; col++) {
                            if (cell[row][col] > mx) {
                                mx_r = row;
                                mx_c = col;
                                mx = cell[row][col];
                            }
                        }
                    }
                    if (i == 0 && j == 0) {
                        pre_pos[i][j].i = 0, pre_pos[i][j].j = 0;
                        cell[i][j] = 0;
                    }
                    else if (mx == LLONG_MIN) {
                        pre_pos[i][j].i = i, pre_pos[i][j].j = j;
                        cell[i][j] = LLONG_MIN;
                    }
                    else {
                        pre_pos[i][j].i = mx_r, pre_pos[i][j].j = mx_c;
                        cell[i][j] = mx + std::stoll(buff);
                    }
                }
            }
        }
        if (cell[n - 1][m - 1] == LLONG_MIN) printf("Impassable\n");
        else {
            printf("Passable\n");
            printf("%lld\n", cell[n - 1][m - 1]);
            pos.i = n - 1, pos.j = m - 1;
            while (1) {
                pos_s.push(pos);
                tmp_pos = pre_pos[pos.i][pos.j];
                if (tmp_pos.i == pos.i && tmp_pos.j == pos.j) break;
                pos = tmp_pos;
            }
            printf("%ld\n", pos_s.size());
            while (!pos_s.empty()) {
                printf("%d %d\n", pos_s.top().i + 1, pos_s.top().j + 1);
                pos_s.pop();
            }
        }
        for (int i = 0; i < n; i++) {
            free(cell[i]);
            free(pre_pos[i]);
        }
    }
    return 0;
}
