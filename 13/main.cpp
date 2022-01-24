#include <bits/stdc++.h>

unsigned long long arr[512];
unsigned long long dp[512][512] = {{0}};
unsigned long long gcd[512][512];
int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%llu", &(arr[i]));
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            gcd[i][j] = std::__gcd(arr[i], arr[j]);
        }
    }
    for (int len = 2; len <= N; len++) {
        for (int i = 0, j = len - 1; j < N; i++, j++) {
            if (len > 3) {
                if (dp[i + 1][j - 1]) {
                    if (gcd[i][j] > 1 &&
                        dp[i][j] < gcd[i][j] + dp[i + 1][j - 1]) {
                        dp[i][j] = gcd[i][j] + dp[i + 1][j - 1];
                    }
                }
                for (int k = i + 1; k < j - 1; k++) {
                    if (dp[i][k] && dp[k + 1][j]) {
                        if (dp[i][j] < dp[i][k] + dp[k + 1][j]) {
                            dp[i][j] = dp[i][k] + dp[k + 1][j];
                        }
                    }
                }
                if (gcd[i][i + 1] > 1 &&
                    gcd[i + 1][j] > 1 &&
                    gcd[i][j] > 1 &&
                    dp[i + 2][j - 1]) {
                    if (dp[i][j] < gcd[i][i + 1] + gcd[i + 1][j] + dp[i + 2][j - 1])
                        dp[i][j] = gcd[i][i + 1] + gcd[i + 1][j] + dp[i + 2][j - 1];
                }
                if (gcd[i][j - 1] > 1 &&
                    gcd[j - 1][j] > 1 &&
                    gcd[i][j] > 1 &&
                    dp[i + 1][j - 2]) {
                    if (dp[i][j] < gcd[i][j - 1] + gcd[j - 1][j] + dp[i + 1][j - 2])
                        dp[i][j] = gcd[i][j - 1] + gcd[j - 1][j] + dp[i + 1][j - 2];
                }
                if (len >= 7) {
                    for (int k = i + 3; k < j - 2; k++) {
                        if (gcd[i][k] > 1 &&
                            gcd[k][j] > 1 &&
                            gcd[i][j] > 1 &&
                            dp[i + 1][k - 1] &&
                            dp[k + 1][j - 1]) {
                            if (dp[i][j] < gcd[i][k] + gcd[k][j] + dp[i + 1][k - 1] + dp[k + 1][j - 1])
                                dp[i][j] = gcd[i][k] + gcd[k][j] + dp[i + 1][k - 1] + dp[k + 1][j - 1];
                        }
                    }
                }
            }
            else if (len == 2) {
                if (gcd[i][j] > 1) {
                    dp[i][j] = gcd[i][j];
                }
            }
            else if (len == 3) {
                if (gcd[i][i + 1] > 1 && gcd[i + 1][j] > 1 && gcd[i][j] > 1) {
                    dp[i][j] = gcd[i][i + 1] + gcd[i + 1][j];
                }
            }
        }
    }
    if (dp[0][N - 1] == 0) printf("-1");
    else printf("%llu", dp[0][N - 1]);
    return 0;
}
