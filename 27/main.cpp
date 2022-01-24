#include <bits/stdc++.h>

#define TEST_RATIO 10
#define ABS(a0, a1) (std::abs(a0 - a1))
#define BIN(a0, a1, a2) (a1 * ((a0 & a1) ^ (a1 | a2) ^ (a0 + a2)))

int N, M;
std::vector<long long> ring;
std::vector<bool> vis;

long long dp(int cut_idx) {
    long long dp_arr[2][N][M];
    int i_idx[N];
    int mn;
    for (int i = 0, idx = cut_idx; i < N; i++, idx = (idx + 1) % N)
        i_idx[i] = idx;
    dp_arr[0][0][0] = ring[i_idx[0]];
    dp_arr[0][1][0] = ring[i_idx[0]] + ring[i_idx[1]]
                        - ABS(ring[i_idx[0]], ring[i_idx[1]]);
    dp_arr[1][1][1] = ring[i_idx[0]] + ring[i_idx[1]];
    for (int i = 2; i < N; i++) {
        dp_arr[0][i][0] = dp_arr[0][i - 1][0]
                        + ring[i_idx[i]]
                        - ABS(ring[i_idx[i - 1]], ring[i_idx[i]])
                        + BIN(ring[i_idx[i - 2]], ring[i_idx[i - 1]], ring[i_idx[i]]);
        for (int j = 1; j < M; j++) {
            if (i > j + 1) {
                dp_arr[0][i][j] = std::min(
                    dp_arr[0][i - 1][j]
                        + ring[i_idx[i]]
                        - ABS(ring[i_idx[i - 1]], ring[i_idx[i]])
                        + BIN(ring[i_idx[i - 2]], ring[i_idx[i - 1]], ring[i_idx[i]]),
                    dp_arr[1][i - 1][j]
                        + ring[i_idx[i]]
                        - ABS(ring[i_idx[i - 1]], ring[i_idx[i]])
                );
                if (j > 1) {
                    dp_arr[1][i][j] = std::min(
                        dp_arr[0][i - 1][j - 1]
                            + ring[i_idx[i]],
                        dp_arr[1][i - 1][j - 1]
                            + ring[i_idx[i]]
                    );
                }
                else {
                    dp_arr[1][i][j] = dp_arr[0][i - 1][j - 1] + ring[i_idx[i]];
                }
            }
            else if (i == j + 1) {
                dp_arr[0][i][j] = dp_arr[1][i - 1][j]
                                + ring[i_idx[i]]
                                - ABS(ring[i_idx[i - 1]], ring[i_idx[i]]);
                if (j > 1) {
                    dp_arr[1][i][j] = std::min(
                        dp_arr[0][i - 1][j - 1]
                            + ring[i_idx[i]],
                        dp_arr[1][i - 1][j - 1]
                            + ring[i_idx[i]]
                    );
                }
                else {
                    dp_arr[1][i][j] = dp_arr[0][i - 1][j - 1] + ring[i_idx[i]];
                }
            }
            else if (i == j) {
                dp_arr[1][i][j] = dp_arr[1][i - 1][j - 1] + ring[i_idx[i]];
            }
        }
    }
    if (N > M) return std::min(dp_arr[0][N - 1][M - 1], dp_arr[1][N - 1][M - 1]);
    else return dp_arr[1][N - 1][M - 1];
}

int main() {
    int test_time;
    int get_rand;
    long long get_dp;
    long long ans;
    srand(0x52ac);
    scanf("%d%d", &N, &M);
    ring.resize(N);
    vis.resize(N);
    test_time = TEST_RATIO * N / M;
    for (int i = 0; i < N; i++) {
        scanf("%lld", &(ring[i]));
        vis[i] = false;
    }
    get_rand = random() % N;
    ans = dp(get_rand);
    vis[get_rand] = true;
    for (int i = 0; i < test_time; i++) {
        get_rand = random() % N;
        // while (vis[get_rand]) get_rand = random() % N;
        vis[get_rand] = true;
        get_dp = dp(get_rand);
        if (get_dp < ans) ans = get_dp;
    }
    printf("%lld\n", ans);
    return 0;
}
